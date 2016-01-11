#ifndef CONSTANTS
#define CONSTANTS

#include "WPILib.h"

//Joysticks  ----------------------------------------------------------------------------------------------------------------------------------------
const uint32_t c_joystickLeftPort           		= 0;
const uint32_t c_joystickRightPort          		= 1;
const uint32_t c_operatorJoystickPort				= 2;


//Digital Ports -------------------------------------------------------------------------------------------------------------------------------------
const uint32_t c_flipperEncoderPortA				= 3;
const uint32_t c_flipperEncoderPortB				= 2;
const uint32_t c_elevatorEncoderPortA				= 4;
const uint32_t c_elevatorEncoderPortB				= 5;
const uint32_t c_forebarEncoderPortA				= 0;
const uint32_t c_forebarEncoderPortB				= 1;
const uint32_t c_leftDriveEncoderPortA				= 8;
const uint32_t c_leftDriveEncoderPortB				= 9;
const uint32_t c_rightDriveEncoderPortA				= 6;
const uint32_t c_rightDriveEncoderPortB				= 7;

//Analog Ports --------------------------------------------------------------------------------------------------------------------------------------
const uint32_t c_elevatorResetLimitSwitchPort		= 1;
const uint32_t c_elevatorStopLimitSwitchPort		= 0;
const uint32_t c_fourbarLimitSwitchPort				= 2; //@TODO: Change this to correct value
//const uint32_t c_armLeftLimitSwitchPort			= 2;
//const uint32_t c_armRightLimitSwitchPort			= 3;


//Solenoids -----------------------------------------------------------------------------------------------------------------------------------------
const uint32_t c_LEDLight1Port						= 1;
const uint32_t c_LEDLight2Port						= 0;

//PWM ports------------------------------------------------------------------------------------------------------------------------------------------
const uint32_t c_leftDriveMotorPort1				= 0;
const uint32_t c_rightDriveMotorPort1				= 2;
const uint32_t c_leftDriveMotorPort2				= 1;
const uint32_t c_rightDriveMotorPort2				= 3;
const uint32_t c_flipperMotorPort					= 6;
const uint32_t c_forebarMotorPort					= 5;
const uint32_t c_elevatorMotorPort					= 4;
const uint32_t c_hooksMotorPort						= 7;
const uint32_t c_intakeLeftMotorPort				= 9;
const uint32_t c_intakeRightMotorPort				= 7;
const uint32_t c_armLeftMotorPort				    = 8;
const uint32_t c_armRightMotorPort					= 6;

//Operator Button Port  -----------------------------------------------------------------------------------------------------------------------------

//const uint32_t c_driveSwitchButtonPort 			= 4;
const uint32_t c_fourbarOverrideButtonPort			= 2;

const uint32_t c_elevatorDeIndexButtonPort			= 2;
const uint32_t c_elevatorIndexButtonPort			= 1;
const uint32_t c_elevatorDisengageButtonPort 		= 2;

const uint32_t c_elevatorResetButtonPort			= 4;

const uint32_t c_forebarButtonPort					= 7;

const uint32_t c_masterFaultResetStickPort			=2;
const uint32_t c_masterFaultResetButtonPort			=8;

//Distances  ----------------------------------------------------------------------------------------------------------------------------------------

const double c_operatorControlLimit1				= 8; // vertical - up
const double c_operatorControlLimit2				= 110; //middle
const double c_flipperEncoderDownLimit				= 600; //ground
const double c_flipperEncoderUpLimit				= 30;
// const double c_indexDistance                      	= 0;
// const double c_elevatorOffset						= 0;
// const double c_elevatorDisengageDistance			= 0;
// const double c_elevatorHighBound					= 0;
// const double c_elevatorLowBound 					= 0;
const double c_forebarRestingDistance				= -63; //DUMMY
const double c_forebarLiftingDistance				= 1500.75; //DUMMY
const double c_forebarClearingDistance				= 1815.75; //DUMMY
// const double c_elevatorDisengageHigherBound 			= 0;
// const double c_elevatorDisengageLowerBound 			= 0;
// const double c_finalIndex							= 0;
const double c_elevatorWindow						= 15;
const double c_pos0Dist								= 0;
const double c_pos1Dist								= 200.75;
const double c_pos2Dist								= 386.5;
const double c_pos3Dist								= 572.5;  //572.5
const double c_pos4Dist								= 757; //757
const double c_pos5Dist								= 944; //944
const double c_pos6Dist								= 949.5; //DUMMY
const double c_disengageDistance					= 82.7; //DUMMY // useb  105.7 for normal ground

// SPEEDS -------------------------------------------------------------------------------------------------------------------------------------------
const double c_autoDriveSpeed						= .25;
const double c_liftSpeed							= .45;

const double c_elevatorP							= .045;

const double c_correction							= 1;



//FAULT STUFF ---------------------------------------------------------------------------------------------------------------------------------------

const double c_processorSpeedPerSecond = 100;
const double c_processorClock1 = 0;
const double c_processorClock2 = 70;
const double c_flipperEncoderFaultBound = 35;
const double c_forebarEncoderFaultBound = 0;
const double c_elevatorEncoderFaultBound = 3;
const double c_processorCheck   = 75;





#endif
