#ifndef DRIVE_SUBSYSTEM_H
#define DRIVE_SUBSYSTEM_H

#include "WPILib.h"
#include "RobotSubsystem.h"
#include "OperatorButton.h"

class DriveSubsystem : public RobotSubsystem
{
public:
	DriveSubsystem();
	virtual ~DriveSubsystem();
	virtual void DoRobotInit(void);
	virtual void DoTeleopInit(void);
	virtual void DoDisabledInit(void);
	virtual void DoTeleopPeriodic(void);
	virtual void DoDisabledPeriodic(void);
	virtual void DoAutonomousPeriodic(void);
	virtual void DoAutonomousInit(void);

	void SetTargetDistanceInInches(double leftTargetValue, double rightTargetValue);
	void DriveByDistanceLeft(double drivespeed);
	void DriveByDistanceRight(double drivespeed);
	void DriveByDistanceRightBack(double drivespeed);
	void DriveByDistanceLeftBack(double drivespeed);
	bool GetIsAutoDriveStarted();
	bool GetIsAutoDriveFinishedLeft();
	bool GetIsAutoDriveFinishedLeftBack();
	bool GetIsAutoDriveFinishedRight();
	bool GetIsAutoDriveFinishedRightBack();



private:
	void Accel(Joystick *js);
	void Accel2(Joystick *js_left, Joystick *js_right);
	//void AccelCheck();
	void TankDrive(double ljy, double rjy);
	void ArcadeDrive(double jx, double jy);
	double ApplyDeadzone(double input, double deadzone);

	//Joysticks
	Joystick *m_leftJoystick;
	Joystick *m_rightJoystick;

	//Motor Controlers
	Talon *m_leftDriveMotor1;
	Talon *m_rightDriveMotor1;
	Talon *m_leftDriveMotor2;
	Talon *m_rightDriveMotor2;

	//Sensors
	Encoder *m_leftEncoder;
	Encoder *m_rightEncoder;
	OperatorButton *m_driveSlowButton;
	OperatorButton *m_driveDistanceButton;
	OperatorButton *m_encoderResetButton;
	double m_leftEncoderTarget;
	double m_rightEncoderTarget;

	bool m_driveState;

	double a,b;
	double accelA, accelB;


};

#endif
