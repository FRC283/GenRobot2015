#ifndef INTAKE_SUBSYSTEM
#define INTAKE_SUBSYSTEM

#include "RobotSubsystem.h"
#include "WPILib.h"
#include "OperatorButton.h"

class IntakeSubsystem : public RobotSubsystem
{
public:
	IntakeSubsystem();
	virtual void DoRobotInit();
	virtual void DoTeleopInit();
	virtual void DoTeleopPeriodic();
	virtual void DoAutonomousInit();
	virtual void DoAutonomousPeriodic();


private:

	Joystick *m_xbox;
	VictorSP *m_intakeLeftMotor;
	VictorSP *m_intakeRightMotor;
	VictorSP *m_armLeftMotor;
	VictorSP *m_armRightMotor;

	DigitalInput *m_armRightLimitSwitch;
	DigitalInput *m_armLeftLimitSwitch;


};

#endif
