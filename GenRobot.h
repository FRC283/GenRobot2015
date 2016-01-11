#ifndef GEN_ROBOT_H
#define GEN_ROBOT_H

#include "WPILib.h"
#include "RobotSubsystem.h"
#include "DriveSubsystem.h"
#include "ForebarSubsystem.h"
#include "ElevatorSubsystem.h"
#include "IntakeSubsystem.h"

class GenRobot : public IterativeRobot
{


public:
	GenRobot();

	virtual void RobotInit();
	virtual void AutonomousInit();
	virtual void TeleopInit();
	virtual void DisabledInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopPeriodic();
	virtual void DisabledPeriodic();

private:
	DriveSubsystem *m_driveSubsystem;
	ForebarSubsystem *m_forebarSubsystem;
	ElevatorSubsystem *m_elevatorSubsystem;
	IntakeSubsystem *m_intakeSubsystem;
	enum AutonomousState{
		kForebar, //Lift the trashcan
		kForward, //Move forward
		kTote, //Pick up the tote
		kTurn, //Turn back towards step
		kBackward, // Drive towards step
		kStop //Self-explanatory


	};
	AutonomousState m_autoState;

	Timer *m_autoTimer; //Delay timer for getting the tote

	int autostate;
	int m_autoSelect;


	Joystick *m_xbox;
};

#endif
