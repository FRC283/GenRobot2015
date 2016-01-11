#ifndef FOREBAR_SUBSYSTEM
#define FOREBAR_SUBSYSTEM

#include "RobotSubsystem.h"
#include "WPILib.h"
#include "OperatorButton.h"

class ForebarSubsystem : public RobotSubsystem
{
public:
	ForebarSubsystem();
	virtual void DoRobotInit();
	virtual void DoTeleopInit();
	virtual void DoTeleopPeriodic();
	virtual void DoAutonomousInit();
	virtual void DoAutonomousPeriodic();
	bool IsLifting();
	void GoToResting();
	void GoToLifting();
	void GoToClearing();
	enum ForebarState{
		kRested, //This is the state it is in when it is completely down
		kLifted, // This is the middle state, when  it is holding the trashcan
		kCleared, // This is when the forebar is fully up and about to place the trashcan
		kWisconsin
	};
	bool m_isLifting;


private:
	//VictorSP
	VictorSP *m_forebarMotor;

	//Encoder
	Encoder *m_forebarEncoder;

	//OperatorButton
	OperatorButton *m_forebarHomeButton;
	OperatorButton *m_forebarLiftingButton;
	Joystick *m_xbox;
	OperatorButton *m_masterFaultReset;
	ForebarState m_forebarState;
	int m_loopCount;
	double m_forebarFault1;
	double m_forebarFault2;
	bool m_forebarFaultOccured;
	double error1;
	double error2;
	double error3;
	bool m_isClearing;

	bool m_isResting;

};

#endif
