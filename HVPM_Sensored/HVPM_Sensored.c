/* ==============================================================================
System Name:  	HVPM_Sensored

File Name:	  	HVPM_Sensored.C

Description:	Primary system file for the Real Implementation of Sensored  
          		Field Orientation Control for Three Phase Permanent-Magnet
          		Synchronous Motor (PMSM) 

Originator:		Digital control systems Group - Texas Instruments

Note: In this software, the default inverter is supposed to be HVDMC board. 
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 10-9-2010	Version 1.1: Supports F2803x 
=================================================================================  */

// Include header files used in the main function

#include "PeripheralHeaderIncludes.h"
#include "IQmathLib.h"
#include "HVPM_Sensored.h"
#include "HVPM_Sensored-Settings.h"
#include <math.h>

#ifdef FLASH
#pragma CODE_SECTION(MainISR,"ramfuncs");
#endif

// Prototype statements for functions found within this file.
interrupt void MainISR(void);
void DeviceInit();
void MemCopy();
void InitFlash();
void HVDMC_Protection(void);

// State Machine function prototypes
//------------------------------------
// Alpha states
void A0(void);	//state A0
void B0(void);	//state B0
void C0(void);	//state C0

// A branch states
void A1(void);	//state A1
void A2(void);	//state A2
void A3(void);	//state A3

// B branch states
void B1(void);	//state B1
void B2(void);	//state B2
void B3(void);	//state B3

// C branch states
void C1(void);	//state C1
void C2(void);	//state C2
void C3(void);	//state C3

// Variable declarations
void (*Alpha_State_Ptr)(void);	// Base States pointer
void (*A_Task_Ptr)(void);		// State pointer A branch
void (*B_Task_Ptr)(void);		// State pointer B branch
void (*C_Task_Ptr)(void);		// State pointer C branch

// Used for running BackGround in flash, and ISR in RAM
extern Uint16 *RamfuncsLoadStart, *RamfuncsLoadEnd, *RamfuncsRunStart;


int16	VTimer0[4];			// Virtual Timers slaved off CPU Timer 0 (A events)
int16	VTimer1[4]; 		// Virtual Timers slaved off CPU Timer 1 (B events)
int16	VTimer2[4]; 		// Virtual Timers slaved off CPU Timer 2 (C events)
int16	SerialCommsTimer;

// Global variables used in this system

_iq VdTesting = _IQ(0.0);			// Vd reference (pu) 
_iq VqTesting = _IQ(0.15);			// Vq reference (pu)
_iq IdRef = _IQ(0.0);				// Id reference (pu) 
_iq IqRef = _IQ(0.05);				// Iq reference (pu) 

#if (BUILDLEVEL<LEVEL3)             // Speed reference (pu)
_iq  SpeedRef = _IQ(0.15);          // For Open Loop tests
#else
_iq  SpeedRef = _IQ(0.3);           // For Closed Loop tests
#endif



float32 T = 0.001/ISR_FREQUENCY;    // Samping period (sec), see parameter.h 

Uint32 IsrTicker = 0;
Uint16 BackTicker = 0;
Uint16 lsw=0;
Uint16 Init_IFlag=0;
Uint16 TripFlagDMC=0;				//PWM trip status 


int16 PwmDacCh1=0;
int16 PwmDacCh2=0;
int16 PwmDacCh3=0;
int16 PwmDacCh4=0;

int16 DlogCh1 = 0;
int16 DlogCh2 = 0;
int16 DlogCh3 = 0;
int16 DlogCh4 = 0; 


volatile Uint16 EnableFlag = FALSE;
Uint16 LockRotorFlag = FALSE;

Uint16 SpeedLoopPrescaler = 10;      // Speed loop prescaler
Uint16 SpeedLoopCount = 1;           // Speed loop counter


// Instance a few transform objects
CLARKE clarke1 = CLARKE_DEFAULTS;
PARK park1 = PARK_DEFAULTS;
IPARK ipark1 = IPARK_DEFAULTS;

// Instance PID regulators to regulate the d and q  axis currents, and speed
PIDREG3 pid1_id = PIDREG3_DEFAULTS;
PIDREG3 pid1_iq = PIDREG3_DEFAULTS;
PIDREG3 pid1_spd = PIDREG3_DEFAULTS;

// Instance a PWM driver instance
PWMGEN pwm1 = PWMGEN_DEFAULTS;

// Instance a PWM DAC driver instance
PWMDAC pwmdac1 = PWMDAC_DEFAULTS;

// Instance a Space Vector PWM modulator. This modulator generates a, b and c
// phases based on the d and q stationery reference frame inputs
SVGENDQ svgen_dq1 = SVGENDQ_DEFAULTS;

// Instance a ramp controller to smoothly ramp the frequency
RMPCNTL rc1 = RMPCNTL_DEFAULTS;

//	Instance a ramp generator to simulate an Anglele
RAMPGEN rg1 = RAMPGEN_DEFAULTS;

// Instance a speed calculator based on QEP
SPEED_MEAS_QEP speed1 = SPEED_MEAS_QEP_DEFAULTS;

// Instance a QEP interface driver 
QEP qep1 = QEP_DEFAULTS; 

// Create an instance of DATALOG Module
DLOG_4CH dlog = DLOG_4CH_DEFAULTS;      




void main(void)
{
	
	DeviceInit();	// Device Life support & GPIO		

// Only used if running from FLASH
// Note that the variable FLASH is defined by the compiler

#ifdef FLASH
// Copy time critical code and Flash setup code to RAM
// The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
// symbols are created by the linker. Refer to the linker files. 
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);

// Call Flash Initialization to setup flash waitstates
// This function must reside in RAM
	InitFlash();	// Call the flash wrapper init function
#endif //(FLASH)

   // Waiting for enable flag set
   while (EnableFlag==FALSE) 
    { 
      BackTicker++;
    }

// Timing sync for background loops 
// Timer period definitions found in device specific PeripheralHeaderIncludes.h
	CpuTimer0Regs.PRD.all =  mSec1;		// A tasks
	CpuTimer1Regs.PRD.all =  mSec5;		// B tasks
	CpuTimer2Regs.PRD.all =  mSec50;	// C tasks

// Tasks State-machine init
	Alpha_State_Ptr = &A0;
	A_Task_Ptr = &A1;
	B_Task_Ptr = &B1;
	C_Task_Ptr = &C1;

// Initialize PWM module
    pwm1.PeriodMax = SYSTEM_FREQUENCY*1000000*T/2;  // Prescaler X1 (T1), ISR period = T x 1 
	PWM_INIT_MACRO(pwm1)  

// Initialize PWMDAC module
	pwmdac1.PeriodMax = 500;   // @60Mhz: 1500->20kHz, 1000-> 30kHz, 500->60kHz
    pwmdac1.PwmDacInPointer0 = &PwmDacCh1;
    pwmdac1.PwmDacInPointer1 = &PwmDacCh2;
    pwmdac1.PwmDacInPointer2 = &PwmDacCh3;
    pwmdac1.PwmDacInPointer3 = &PwmDacCh4;
	PWMDAC_INIT_MACRO(pwmdac1)

// Initialize DATALOG module
    dlog.iptr1 = &DlogCh1;
    dlog.iptr2 = &DlogCh2;
	dlog.iptr3 = &DlogCh3;
    dlog.iptr4 = &DlogCh4;
    dlog.trig_value = 0x1;
    dlog.size = 0x0c8;
    dlog.prescalar = 5;
    dlog.init(&dlog);

// Initialize ADC module
    ADC_MACRO_INIT()

// Initialize QEP module
    qep1.LineEncoder = 2500;
    qep1.MechScaler = _IQ30(0.25/qep1.LineEncoder);
    qep1.PolePairs = POLES/2;
    qep1.CalibratedAngle = 0;
    QEP_INIT_MACRO(qep1)

// Initialize the Speed module for QEP based speed calculation
    speed1.K1 = _IQ21(1/(BASE_FREQ*T));
    speed1.K2 = _IQ(1/(1+T*2*PI*5));  // Low-pass cut-off frequency
    speed1.K3 = _IQ(1)-speed1.K2;
    speed1.BaseRpm = 120*(BASE_FREQ/POLES);

// Initialize the RAMPGEN module
    rg1.StepAngleMax = _IQ(BASE_FREQ*T); 
    
// Initialize the PID_REG3 module for Id
	pid1_id.Kp = _IQ(1.0);  
	pid1_id.Ki = _IQ(T/0.04);	
	pid1_id.Kd = _IQ(0/T); 						
	pid1_id.Kc = _IQ(0.2);
    pid1_id.OutMax = _IQ(0.30);
    pid1_id.OutMin = _IQ(-0.30);    
 
// Initialize the PID_REG3 module for Iq
	pid1_iq.Kp = _IQ(1.0);
	pid1_iq.Ki = _IQ(T/0.04);			
	pid1_iq.Kd = _IQ(0/T); 				
	pid1_iq.Kc = _IQ(0.2);
    pid1_iq.OutMax = _IQ(0.8);
    pid1_iq.OutMin = _IQ(-0.8);    

// Initialize the PID_REG3 module for speed
    pid1_spd.Kp = _IQ(1.0);                  
	pid1_spd.Ki = _IQ(T*SpeedLoopPrescaler/0.2);			
	pid1_spd.Kd = _IQ(0/(T*SpeedLoopPrescaler));					
 	pid1_spd.Kc = _IQ(0.2);
    pid1_spd.OutMax = _IQ(1);
    pid1_spd.OutMin = _IQ(-1);  

//Call HVDMC Protection function
	HVDMC_Protection();	

// Reassign ISRs. 

	EALLOW;	// This is needed to write to EALLOW protected registers
	PieVectTable.EPWM1_INT = &MainISR;
	EDIS;

// Enable PIE group 3 interrupt 1 for EPWM1_INT
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;

// Enable CNT_zero interrupt using EPWM1 Time-base
    EPwm1Regs.ETSEL.bit.INTEN = 1;   // Enable EPWM1INT generation 
    EPwm1Regs.ETSEL.bit.INTSEL = 1;  // Enable interrupt CNT_zero event
    EPwm1Regs.ETPS.bit.INTPRD = 1;   // Generate interrupt on the 1st event
	EPwm1Regs.ETCLR.bit.INT = 1;     // Enable more interrupts

// Enable CPU INT3 for EPWM1_INT:
	IER |= M_INT3;
// Enable global Interrupts and higher priority real-time debug events:
	EINT;   // Enable Global interrupt INTM
	ERTM;	// Enable Global realtime interrupt DBGM

// IDLE loop. Just sit and loop forever:	
	for(;;)  //infinite loop
	{
		// State machine entry & exit point
		//===========================================================
		(*Alpha_State_Ptr)();	// jump to an Alpha state (A0,B0,...)
		//===========================================================

	}
} //END MAIN CODE



//=================================================================================
//	STATE-MACHINE SEQUENCING AND SYNCRONIZATION FOR SLOW BACKGROUND TASKS
//=================================================================================

//--------------------------------- FRAMEWORK -------------------------------------
void A0(void)
{
	// loop rate synchronizer for A-tasks
	if(CpuTimer0Regs.TCR.bit.TIF == 1)
	{
		CpuTimer0Regs.TCR.bit.TIF = 1;	// clear flag

		//-----------------------------------------------------------
		(*A_Task_Ptr)();		// jump to an A Task (A1,A2,A3,...)
		//-----------------------------------------------------------

		VTimer0[0]++;			// virtual timer 0, instance 0 (spare)
		SerialCommsTimer++;
	}

	Alpha_State_Ptr = &B0;		// Comment out to allow only A tasks
}

void B0(void)
{
	// loop rate synchronizer for B-tasks
	if(CpuTimer1Regs.TCR.bit.TIF == 1)
	{
		CpuTimer1Regs.TCR.bit.TIF = 1;				// clear flag

		//-----------------------------------------------------------
		(*B_Task_Ptr)();		// jump to a B Task (B1,B2,B3,...)
		//-----------------------------------------------------------
		VTimer1[0]++;			// virtual timer 1, instance 0 (spare)
	}

	Alpha_State_Ptr = &C0;		// Allow C state tasks
}

void C0(void)
{
	// loop rate synchronizer for C-tasks
	if(CpuTimer2Regs.TCR.bit.TIF == 1)
	{
		CpuTimer2Regs.TCR.bit.TIF = 1;				// clear flag

		//-----------------------------------------------------------
		(*C_Task_Ptr)();		// jump to a C Task (C1,C2,C3,...)
		//-----------------------------------------------------------
		VTimer2[0]++;			//virtual timer 2, instance 0 (spare)
	}

	Alpha_State_Ptr = &A0;	// Back to State A0
}


//=================================================================================
//	A - TASKS (executed in every 1 msec)
//=================================================================================
//--------------------------------------------------------
void A1(void) // SPARE (not used)
//--------------------------------------------------------
{
		if(EPwm1Regs.TZFLG.bit.OST==0x1)
	    TripFlagDMC=1;      // Trip on DMC (halt and IPM fault trip )
	
	//-------------------
	//the next time CpuTimer0 'counter' reaches Period value go to A2
	A_Task_Ptr = &A2;
	//-------------------
}

//-----------------------------------------------------------------
void A2(void) // SPARE (not used)
//-----------------------------------------------------------------
{	

	//-------------------
	//the next time CpuTimer0 'counter' reaches Period value go to A3
	A_Task_Ptr = &A3;
	//-------------------
}

//-----------------------------------------
void A3(void) // SPARE (not used)
//-----------------------------------------
{

	//-----------------
	//the next time CpuTimer0 'counter' reaches Period value go to A1
	A_Task_Ptr = &A1;
	//-----------------
}



//=================================================================================
//	B - TASKS (executed in every 5 msec)
//=================================================================================

//----------------------------------- USER ----------------------------------------

//----------------------------------------
void B1(void) // Toggle GPIO-00
//----------------------------------------
{

	//-----------------
	//the next time CpuTimer1 'counter' reaches Period value go to B2
	B_Task_Ptr = &B2;	
	//-----------------
}

//----------------------------------------
void B2(void) //  SPARE
//----------------------------------------
{

	//-----------------
	//the next time CpuTimer1 'counter' reaches Period value go to B3
	B_Task_Ptr = &B3;
	//-----------------
}

//----------------------------------------
void B3(void) //  SPARE
//----------------------------------------
{

	//-----------------
	//the next time CpuTimer1 'counter' reaches Period value go to B1
	B_Task_Ptr = &B1;	
	//-----------------
}


//=================================================================================
//	C - TASKS (executed in every 50 msec)
//=================================================================================

//--------------------------------- USER ------------------------------------------

//----------------------------------------
void C1(void) 	// Toggle GPIO-34 
//----------------------------------------
{

	GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
	//-----------------
	//the next time CpuTimer2 'counter' reaches Period value go to C2
	C_Task_Ptr = &C2;	
	//-----------------

}

//----------------------------------------
void C2(void) //  SPARE
//----------------------------------------
{

	//-----------------
	//the next time CpuTimer2 'counter' reaches Period value go to C3
	C_Task_Ptr = &C3;	
	//-----------------
}


//-----------------------------------------
void C3(void) //  SPARE
//-----------------------------------------
{

	//-----------------
	//the next time CpuTimer2 'counter' reaches Period value go to C1
	C_Task_Ptr = &C1;	
	//-----------------
}




// MainISR 
interrupt void MainISR(void)
{

// Verifying the ISR
    IsrTicker++;

// =============================== LEVEL 1 ======================================
//	  Checks target independent modules, duty cycle waveforms and PWM update
//	  Keep the motors disconnected at this level	
// ============================================================================== 

#if (BUILDLEVEL==LEVEL1)	 

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
    rc1.TargetValue = SpeedRef;		
	RC_MACRO(rc1)

// ------------------------------------------------------------------------------
//  Connect inputs of the RAMP GEN module and call the ramp generator macro
// ------------------------------------------------------------------------------
    rg1.Freq = rc1.SetpointValue;
	RG_MACRO(rg1)

// ------------------------------------------------------------------------------
//  Connect inputs of the INV_PARK module and call the inverse park trans. macro
// ------------------------------------------------------------------------------
    ipark1.Ds = VdTesting;
    ipark1.Qs = VqTesting;

	ipark1.Sine=_IQsinPU(rg1.Out);
    ipark1.Cosine=_IQcosPU(rg1.Out);
	IPARK_MACRO(ipark1)

// ------------------------------------------------------------------------------
//  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
// ------------------------------------------------------------------------------
  	svgen_dq1.Ualpha = ipark1.Alpha;
 	svgen_dq1.Ubeta = ipark1.Beta;	
	SVGEN_MACRO(svgen_dq1)

// ------------------------------------------------------------------------------
//  Connect inputs of the PWM_DRV module and call the PWM signal generation macro
// ------------------------------------------------------------------------------
    pwm1.MfuncC1 = (int16)_IQtoIQ15(svgen_dq1.Ta); // MfuncC1 is in Q15
    pwm1.MfuncC2 = (int16)_IQtoIQ15(svgen_dq1.Tb); // MfuncC2 is in Q15  
    pwm1.MfuncC3 = (int16)_IQtoIQ15(svgen_dq1.Tc); // MfuncC3 is in Q15
	PWM_MACRO(pwm1)							   	   // Calculate the new PWM compare values	

	EPwm1Regs.CMPA.half.CMPA=pwm1.PWM1out;	// PWM 1A - PhaseA 
	EPwm2Regs.CMPA.half.CMPA=pwm1.PWM2out;	// PWM 2A - PhaseB
	EPwm3Regs.CMPA.half.CMPA=pwm1.PWM3out;	// PWM 3A - PhaseC  

// ------------------------------------------------------------------------------
//    Connect inputs of the PWMDAC module 
// ------------------------------------------------------------------------------	
    PwmDacCh1 = (int16)_IQtoIQ15(svgen_dq1.Ta);
    PwmDacCh2 = (int16)_IQtoIQ15(svgen_dq1.Tb);
    PwmDacCh3 = (int16)_IQtoIQ15(svgen_dq1.Tc);
    PwmDacCh4 = (int16)_IQtoIQ15(svgen_dq1.Tb-svgen_dq1.Tc);    

// ------------------------------------------------------------------------------
//    Connect inputs of the DATALOG module 
// ------------------------------------------------------------------------------
    DlogCh1 = (int16)_IQtoIQ15(svgen_dq1.Ta);
    DlogCh2 = (int16)_IQtoIQ15(svgen_dq1.Tb);
    DlogCh3 = (int16)_IQtoIQ15(svgen_dq1.Tc);
    DlogCh4 = (int16)_IQtoIQ15(svgen_dq1.Tb-svgen_dq1.Tc);

#endif // (BUILDLEVEL==LEVEL1)

// =============================== LEVEL 2 ======================================
//	  Level 2 verifies the analog-to-digital conversion, offset compensation, 
//    clarke/park transformations (CLARKE/PARK), phase voltage calculations 
// ============================================================================== 

#if (BUILDLEVEL==LEVEL2) 

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
    rc1.TargetValue = SpeedRef;		
	RC_MACRO(rc1)

// ------------------------------------------------------------------------------
//  Connect inputs of the RAMP GEN module and call the ramp generator macro
// ------------------------------------------------------------------------------
    rg1.Freq = rc1.SetpointValue;
	RG_MACRO(rg1) 

// ------------------------------------------------------------------------------
//  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1). 
//	Connect inputs of the CLARKE module and call the clarke transformation macro
// ------------------------------------------------------------------------------
	clarke1.As=_IQ15toIQ((AdcResult.ADCRESULT1<<3)-_IQ15(0.4970))<<1;  // Phase A curr.
	clarke1.Bs=_IQ15toIQ((AdcResult.ADCRESULT2<<3)-_IQ15(0.4995))<<1;  // Phase B curr.	
	CLARKE_MACRO(clarke1) 

// ------------------------------------------------------------------------------
//  Connect inputs of the PARK module and call the park trans. macro
// ------------------------------------------------------------------------------
	park1.Alpha = clarke1.Alpha;
	park1.Beta = clarke1.Beta;
	park1.Angle = rg1.Out;
	park1.Sine = _IQsinPU(park1.Angle);
	park1.Cosine = _IQcosPU(park1.Angle);
	PARK_MACRO(park1) 
 
// ------------------------------------------------------------------------------
//	Connect inputs of the INV_PARK module and call the inverse park trans. macro
// ------------------------------------------------------------------------------
    ipark1.Ds = VdTesting;
    ipark1.Qs = VqTesting;
	ipark1.Sine=park1.Sine;
    ipark1.Cosine=park1.Cosine;
	IPARK_MACRO(ipark1)        

// ------------------------------------------------------------------------------
//  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
// ------------------------------------------------------------------------------
  	svgen_dq1.Ualpha = ipark1.Alpha;
 	svgen_dq1.Ubeta = ipark1.Beta;
  	SVGEN_MACRO(svgen_dq1)	

// ------------------------------------------------------------------------------
//  Connect inputs of the PWM_DRV module and call the PWM signal generation macro
// ------------------------------------------------------------------------------
    pwm1.MfuncC1 = (int16)_IQtoIQ15(svgen_dq1.Ta); // MfuncC1 is in Q15
    pwm1.MfuncC2 = (int16)_IQtoIQ15(svgen_dq1.Tb); // MfuncC2 is in Q15  
    pwm1.MfuncC3 = (int16)_IQtoIQ15(svgen_dq1.Tc); // MfuncC3 is in Q15
	PWM_MACRO(pwm1)							   	   // Calculate the new PWM compare values	

	EPwm1Regs.CMPA.half.CMPA=pwm1.PWM1out;	// PWM 1A - PhaseA 
	EPwm2Regs.CMPA.half.CMPA=pwm1.PWM2out;	// PWM 2A - PhaseB
	EPwm3Regs.CMPA.half.CMPA=pwm1.PWM3out;	// PWM 3A - PhaseC  

// ------------------------------------------------------------------------------
//  Connect inputs of the PWMDAC module 
// ------------------------------------------------------------------------------	
    PwmDacCh1 = (int16)_IQtoIQ15(clarke1.As);
    PwmDacCh2 = (int16)_IQtoIQ15(clarke1.Bs); 
    PwmDacCh3 = (int16)_IQtoIQ15(rg1.Out);
    PwmDacCh4 = (int16)_IQtoIQ15(svgen_dq1.Ta);    

// ------------------------------------------------------------------------------
//  Connect inputs of the DATALOG module 
// ------------------------------------------------------------------------------
    DlogCh1 = (int16)_IQtoIQ15(svgen_dq1.Ta);
    DlogCh2 = (int16)_IQtoIQ15(rg1.Out);
    DlogCh3 = (int16)_IQtoIQ15(clarke1.As);
    DlogCh4 = (int16)_IQtoIQ15(clarke1.Bs);  


#endif // (BUILDLEVEL==LEVEL2)

// =============================== LEVEL 3 ======================================
//	Level 3 verifies the dq-axis current regulation performed by PID and speed 
//	measurement modules. 
// ==============================================================================  
//	  lsw=0: lock the rotor of the motor, 
//	  lsw=1: close the current loop,  

#if (BUILDLEVEL==LEVEL3)

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------ 
    if(lsw==0)rc1.TargetValue = 0;
    else rc1.TargetValue = SpeedRef;		
	RC_MACRO(rc1)

// ------------------------------------------------------------------------------
//  Connect inputs of the RAMP GEN module and call the ramp generator macro
// ------------------------------------------------------------------------------
    rg1.Freq = rc1.SetpointValue;
	RG_MACRO(rg1)  

// ------------------------------------------------------------------------------
//  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1). 
//	Connect inputs of the CLARKE module and call the clarke transformation macro
// ------------------------------------------------------------------------------
	clarke1.As=_IQ15toIQ((AdcResult.ADCRESULT1<<3)-_IQ15(0.4970))<<1;  // Phase A curr.
	clarke1.Bs=_IQ15toIQ((AdcResult.ADCRESULT2<<3)-_IQ15(0.4995))<<1;  // Phase B curr.	
	CLARKE_MACRO(clarke1) 

// ------------------------------------------------------------------------------
//  Connect inputs of the PARK module and call the park trans. macro
// ------------------------------------------------------------------------------ 
	park1.Alpha = clarke1.Alpha;
	park1.Beta = clarke1.Beta;
	if(lsw==0) park1.Angle = 0;
	else if(lsw==1) park1.Angle = rg1.Out;
	
	park1.Sine = _IQsinPU(park1.Angle);
	park1.Cosine = _IQcosPU(park1.Angle);
	
	PARK_MACRO(park1) 
 
// ------------------------------------------------------------------------------
//  Connect inputs of the PID_REG3 module and call the PID IQ controller macro
// ------------------------------------------------------------------------------  
    if (lsw==0) pid1_iq.Ref = 0;
	else pid1_iq.Ref = IqRef;
	pid1_iq.Fdb = park1.Qs;
	PID_MACRO(pid1_iq)

// ------------------------------------------------------------------------------
//  Connect inputs of the PID_REG3 module and call the PID ID controller macro
// ------------------------------------------------------------------------------   
    if (lsw==0) pid1_id.Ref = _IQ(0.05);	// Lock the rotor
	else pid1_id.Ref = IdRef;
	pid1_id.Fdb = park1.Ds;
	PID_MACRO(pid1_id) 

// ------------------------------------------------------------------------------
//	Connect inputs of the INV_PARK module and call the inverse park trans. macro
// ------------------------------------------------------------------------------
    ipark1.Ds = pid1_id.Out;
    ipark1.Qs = pid1_iq.Out ;
	ipark1.Sine   = park1.Sine;
    ipark1.Cosine = park1.Cosine;
	IPARK_MACRO(ipark1) 

// ------------------------------------------------------------------------------
//    Detect calibration angle and call the QEP module
// ------------------------------------------------------------------------------
	if (lsw==0) {EQep1Regs.QPOSCNT=0; EQep1Regs.QCLR.bit.IEL = 1;} // Reset position cnt.

	if ((EQep1Regs.QFLG.bit.IEL==1) && Init_IFlag==0)	 // Check the index occurrence  
	   {qep1.CalibratedAngle= EQep1Regs.QPOSILAT; Init_IFlag++;} // Keep the latched pos. at the first index

    if (lsw!=0) QEP_MACRO(qep1);

// ------------------------------------------------------------------------------
//    Connect inputs of the SPEED_FR module and call the speed calculation macro 
// ------------------------------------------------------------------------------ 
    speed1.ElecTheta = _IQ24toIQ((int32)qep1.ElecTheta);
    speed1.DirectionQep = (int32)(qep1.DirectionQep);
    SPEED_FR_MACRO(speed1)      

// ------------------------------------------------------------------------------
//  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
// ------------------------------------------------------------------------------
  	svgen_dq1.Ualpha = ipark1.Alpha;
 	svgen_dq1.Ubeta = ipark1.Beta;
  	SVGEN_MACRO(svgen_dq1)        

// ------------------------------------------------------------------------------
//  Connect inputs of the PWM_DRV module and call the PWM signal generation macro
// ------------------------------------------------------------------------------
    pwm1.MfuncC1 = (int16)_IQtoIQ15(svgen_dq1.Ta); // MfuncC1 is in Q15
    pwm1.MfuncC2 = (int16)_IQtoIQ15(svgen_dq1.Tb); // MfuncC2 is in Q15  
    pwm1.MfuncC3 = (int16)_IQtoIQ15(svgen_dq1.Tc); // MfuncC3 is in Q15
	PWM_MACRO(pwm1)							   	   // Calculate the new PWM compare values	

	EPwm1Regs.CMPA.half.CMPA=pwm1.PWM1out;	// PWM 1A - PhaseA 
	EPwm2Regs.CMPA.half.CMPA=pwm1.PWM2out;	// PWM 2A - PhaseB
	EPwm3Regs.CMPA.half.CMPA=pwm1.PWM3out;	// PWM 3A - PhaseC  

// ------------------------------------------------------------------------------
//    Connect inputs of the PWMDAC module 
// ------------------------------------------------------------------------------	
    PwmDacCh1 = (int16)_IQtoIQ15(clarke1.As);
    PwmDacCh2 = (int16)_IQtoIQ15(qep1.ElecTheta); 
    PwmDacCh3 = (int16)_IQtoIQ15(clarke1.Bs);
    PwmDacCh4 = (int16)_IQtoIQ15(rg1.Out);    

// ------------------------------------------------------------------------------
//    Connect inputs of the DATALOG module 
// ------------------------------------------------------------------------------
    DlogCh1 = (int16)_IQtoIQ15(qep1.ElecTheta);
    DlogCh2 = (int16)_IQtoIQ15(rg1.Out);
    DlogCh3 = (int16)_IQtoIQ15(clarke1.As);
    DlogCh4 = (int16)_IQtoIQ15(clarke1.Bs);  

#endif // (BUILDLEVEL==LEVEL3)


// =============================== LEVEL 4 ======================================
//	  Level 4 verifies the speed regulator performed by PID_REG3 module. 
//	  The system speed loop is closed by using the measured speed as a feedback.
// ==============================================================================  
//	  lsw=0: lock the rotor of the motor, 
//	  lsw=1: close the current loop, 
//	  lsw=2: close the speed loop (sensored FOC).


#if (BUILDLEVEL==LEVEL4)

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------ 
    if(lsw==0)rc1.TargetValue = 0;
    else rc1.TargetValue = SpeedRef;		
	RC_MACRO(rc1)

// ------------------------------------------------------------------------------
//  Connect inputs of the RAMP GEN module and call the ramp generator macro
// ------------------------------------------------------------------------------
    rg1.Freq = rc1.SetpointValue;
	RG_MACRO(rg1)  

// ------------------------------------------------------------------------------
//  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1). 
//	Connect inputs of the CLARKE module and call the clarke transformation macro
// ------------------------------------------------------------------------------
	clarke1.As=_IQ15toIQ((AdcResult.ADCRESULT1<<3)-_IQ15(0.4970))<<1;  // Phase A curr.
	clarke1.Bs=_IQ15toIQ((AdcResult.ADCRESULT2<<3)-_IQ15(0.4995))<<1;  // Phase B curr.	
	CLARKE_MACRO(clarke1)  

// ------------------------------------------------------------------------------
//  Connect inputs of the PARK module and call the park trans. macro
// ------------------------------------------------------------------------------  
	park1.Alpha = clarke1.Alpha;
	park1.Beta = clarke1.Beta;
	
	if(lsw==0) park1.Angle = 0;
	else if(lsw==1) park1.Angle = rg1.Out;
	else park1.Angle = qep1.ElecTheta;
	
	park1.Sine = _IQsinPU(park1.Angle);
	park1.Cosine = _IQcosPU(park1.Angle);
	
	PARK_MACRO(park1) 

// ------------------------------------------------------------------------------
//    Connect inputs of the PID_REG3 module and call the PID speed controller macro
// ------------------------------------------------------------------------------  
   if (SpeedLoopCount==SpeedLoopPrescaler)
     {
      pid1_spd.Ref = rc1.SetpointValue;
      pid1_spd.Fdb = speed1.Speed;
	  PID_MACRO(pid1_spd);
      SpeedLoopCount=1;
     }
	else SpeedLoopCount++;   

	if(lsw!=2)	pid1_spd.Ui=0;

// ------------------------------------------------------------------------------
//    Connect inputs of the PID_REG3 module and call the PID IQ controller macro
// ------------------------------------------------------------------------------  
	if(lsw==0) pid1_iq.Ref = 0;
    else if(lsw==1) pid1_iq.Ref = IqRef;
    else pid1_iq.Ref =  pid1_spd.Out; 
	pid1_iq.Fdb = park1.Qs;
	PID_MACRO(pid1_iq) 

// ------------------------------------------------------------------------------
//    Connect inputs of the PID_REG3 module and call the PID ID controller macro
// ------------------------------------------------------------------------------  
	if(lsw==0) pid1_id.Ref = _IQ(0.05);
    else pid1_id.Ref = IdRef; 
	pid1_id.Fdb = park1.Ds;
	PID_MACRO(pid1_id) 

// ------------------------------------------------------------------------------
//  Connect inputs of the INV_PARK module and call the inverse park trans. macro
// ------------------------------------------------------------------------------   
    ipark1.Ds = pid1_id.Out;
    ipark1.Qs = pid1_iq.Out;
	ipark1.Sine=park1.Sine;
    ipark1.Cosine=park1.Cosine;
	IPARK_MACRO(ipark1) 

// ------------------------------------------------------------------------------
//    Detect calibration angle (optional) and call the QEP module 
// ------------------------------------------------------------------------------
	if (lsw==0) {EQep1Regs.QPOSCNT=0; EQep1Regs.QCLR.bit.IEL = 1;} // Reset position cnt.

	if ((EQep1Regs.QFLG.bit.IEL==1) && Init_IFlag==0)	 // Check the first index occurrence  
	   {qep1.CalibratedAngle= EQep1Regs.QPOSILAT; Init_IFlag++;} // Keep the latched position 

    if (lsw!=0) QEP_MACRO(qep1); 

// ------------------------------------------------------------------------------
//    Connect inputs of the SPEED_FR module and call the speed calculation macro 
// ------------------------------------------------------------------------------
    speed1.ElecTheta = _IQ24toIQ((int32)qep1.ElecTheta);
    speed1.DirectionQep = (int32)(qep1.DirectionQep);
    SPEED_FR_MACRO(speed1)

// ------------------------------------------------------------------------------
//  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
// ------------------------------------------------------------------------------
  	svgen_dq1.Ualpha = ipark1.Alpha;
 	svgen_dq1.Ubeta = ipark1.Beta;
  	SVGEN_MACRO(svgen_dq1)        

// ------------------------------------------------------------------------------
//  Connect inputs of the PWM_DRV module and call the PWM signal generation macro
// ------------------------------------------------------------------------------
    pwm1.MfuncC1 = (int16)_IQtoIQ15(svgen_dq1.Ta); // MfuncC1 is in Q15
    pwm1.MfuncC2 = (int16)_IQtoIQ15(svgen_dq1.Tb); // MfuncC2 is in Q15  
    pwm1.MfuncC3 = (int16)_IQtoIQ15(svgen_dq1.Tc); // MfuncC3 is in Q15
	PWM_MACRO(pwm1)							   	   // Calculate the new PWM compare values	

	EPwm1Regs.CMPA.half.CMPA=pwm1.PWM1out;	// PWM 1A - PhaseA 
	EPwm2Regs.CMPA.half.CMPA=pwm1.PWM2out;	// PWM 2A - PhaseB
	EPwm3Regs.CMPA.half.CMPA=pwm1.PWM3out;	// PWM 3A - PhaseC  

// ------------------------------------------------------------------------------
//    Connect inputs of the PWMDAC module 
// ------------------------------------------------------------------------------	
    PwmDacCh1 = (int16)_IQtoIQ15(clarke1.As);
    PwmDacCh2 = (int16)_IQtoIQ15(qep1.ElecTheta); 
    PwmDacCh3 = (int16)_IQtoIQ15(clarke1.Bs);
    PwmDacCh4 = (int16)_IQtoIQ15(rg1.Out);    

// ------------------------------------------------------------------------------
//    Connect inputs of the DATALOG module 
// ------------------------------------------------------------------------------
    DlogCh1 = (int16)_IQtoIQ15(qep1.ElecTheta);
    DlogCh2 = (int16)_IQtoIQ15(rg1.Out);
    DlogCh3 = (int16)_IQtoIQ15(clarke1.As);
    DlogCh4 = (int16)_IQtoIQ15(clarke1.Bs); 

#endif // (BUILDLEVEL==LEVEL4) 

// ------------------------------------------------------------------------------
//    Call the PWMDAC update macro.
// ------------------------------------------------------------------------------
	PWMDAC_MACRO(pwmdac1)

// ------------------------------------------------------------------------------
//    Call the DATALOG update function.
// ------------------------------------------------------------------------------
    dlog.update(&dlog);


#if (DSP2803x_DEVICE_H==1)||(DSP280x_DEVICE_H==1)
// Enable more interrupts from this timer
	EPwm1Regs.ETCLR.bit.INT = 1;

// Acknowledge interrupt to recieve more interrupts from PIE group 3
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
#endif

}// ISR Ends Here

/**********************************************************/
/***************Protection Configuration*******************/  
/**********************************************************/

void HVDMC_Protection(void)
{

// Configure Trip Mechanism for the Motor control software
// -Cycle by cycle trip on CPU halt
// -One shot IPM trip zone trip 
// These trips need to be repeated for EPWM1 ,2 & 3

//===========================================================================
//Motor Control Trip Config, EPwm1,2,3
//===========================================================================
      EALLOW;
// CPU Halt Trip  
      EPwm1Regs.TZSEL.bit.CBC6=0x1;
      EPwm2Regs.TZSEL.bit.CBC6=0x1;
      EPwm3Regs.TZSEL.bit.CBC6=0x1;
      
      
      EPwm1Regs.TZSEL.bit.OSHT1   = 1;  //enable TZ1 for OSHT  
      EPwm2Regs.TZSEL.bit.OSHT1   = 1;  //enable TZ1 for OSHT      
      EPwm3Regs.TZSEL.bit.OSHT1   = 1;  //enable TZ1 for OSHT

// What do we want the OST/CBC events to do?
// TZA events can force EPWMxA
// TZB events can force EPWMxB

      EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO; // EPWMxA will go low 
      EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO; // EPWMxB will go low
      
      EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_LO; // EPWMxA will go low 
      EPwm2Regs.TZCTL.bit.TZB = TZ_FORCE_LO; // EPWMxB will go low
      
      EPwm3Regs.TZCTL.bit.TZA = TZ_FORCE_LO; // EPWMxA will go low 
      EPwm3Regs.TZCTL.bit.TZB = TZ_FORCE_LO; // EPWMxB will go low
      
      
      EDIS;

     // Clear any spurious OV trip
      EPwm1Regs.TZCLR.bit.OST = 1;
      EPwm2Regs.TZCLR.bit.OST = 1;
      EPwm3Regs.TZCLR.bit.OST = 1;  
      
//************************** End of Prot. Conf. ***************************//
}

//===========================================================================
// No more.
//===========================================================================
