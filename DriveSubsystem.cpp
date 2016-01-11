#include "DriveSubsystem.h"
#include "Constants.h"
#include "cmath"
#include "thread"

DriveSubsystem::DriveSubsystem() {

	m_leftJoystick = Joystick::GetStickForPort(c_joystickLeftPort);
	m_rightJoystick = Joystick::GetStickForPort(c_joystickRightPort);
	m_leftDriveMotor1 = new Talon(c_leftDriveMotorPort1);
	m_rightDriveMotor1 = new Talon(c_rightDriveMotorPort1);
	m_leftDriveMotor2 = new Talon(c_leftDriveMotorPort2);
	m_rightDriveMotor2 = new Talon(c_rightDriveMotorPort2);
	m_leftEncoder = new Encoder(c_leftDriveEncoderPortA, c_leftDriveEncoderPortB);
	m_rightEncoder = new Encoder(c_rightDriveEncoderPortB, c_rightDriveEncoderPortA);
	m_driveSlowButton = new OperatorButton(c_joystickLeftPort,1);
	m_driveDistanceButton = new OperatorButton(0,2);
	m_leftEncoder->SetDistancePerPulse(1);
	m_rightEncoder->SetDistancePerPulse(1);
	// Robot Drive Function documentation is wrong. left rear, left front, right front, right rear is correct order.

}
DriveSubsystem::~DriveSubsystem() {

}

void DriveSubsystem::DoRobotInit(void) {

}

void DriveSubsystem::DoTeleopInit(void) {

	a = 0;
	b = 0;
	accelA = 0;
	accelB = 0;
	m_driveState = false;
	m_leftEncoder->Reset();
	m_rightEncoder->Reset();

}

void DriveSubsystem::DoDisabledInit(void) {

}

void DriveSubsystem::DoTeleopPeriodic(void) {

	//Accel(m_leftJoystick);
	//ArcadeDrive(accelA,accelB);  //Uncomment for Arcade Drive, Comment for Tank Drive
	Accel2(m_rightJoystick, m_leftJoystick);
	TankDrive(accelA,accelB);  //Uncomment for Tank Drive, Comment for Arcade Drive

	SmartDashboard::PutNumber("JSY", m_leftJoystick->GetY());
	SmartDashboard::PutNumber("JSX", m_leftJoystick->GetX());
	SmartDashboard::PutNumber("A", a);
	SmartDashboard::PutNumber("B", b);
	SmartDashboard::PutNumber("leftDrive", m_leftEncoder->GetDistance());
	SmartDashboard::PutNumber("rightDrive", m_rightEncoder->GetDistance());

}

void DriveSubsystem::DoDisabledPeriodic(void) {

}

void DriveSubsystem::DoAutonomousPeriodic(void) {

	SmartDashboard::PutNumber("leftDrive auto", m_leftEncoder->GetDistance());
	SmartDashboard::PutNumber("rightDrive auto", m_rightEncoder->GetDistance());
}

void DriveSubsystem::DoAutonomousInit(void) {

}

void DriveSubsystem::TankDrive(double ljy, double rjy) {
	double leftSide, rightSide; //  values being passed to motor
	double lj, rj; // value


	lj = ljy;
	rj = rjy;

// Deadzone

// Tank Drive Logic
	leftSide = lj;
	rightSide = rj;
// Apply Logic to Motors
	if(m_driveSlowButton->Get() == OperatorButton::kReleased)
	{
		m_leftDriveMotor1->Set(-leftSide * .5);
		m_rightDriveMotor1->Set(rightSide * .5);
		m_leftDriveMotor2->Set(-leftSide * .5);
		m_rightDriveMotor2->Set(rightSide * .5);
	}
	if(m_driveSlowButton->Get() == OperatorButton::kPressed)
	{
		m_leftDriveMotor1->Set(-leftSide * .25);
		m_rightDriveMotor1->Set(rightSide * .25);
		m_leftDriveMotor2->Set(-leftSide * .25);
		m_rightDriveMotor2->Set(rightSide * .25);
	}

}

void DriveSubsystem::ArcadeDrive(double jx, double jy) {

double lmotor, rmotor;
double ldead, rdead;
	// deadzone


	//Applied WPILib Arcade DriveLogic
	if (jy > 0.0) {
		if (jx > 0.0) {
			lmotor = jy - jx;
			rmotor = std::max(jy, jx);
		}

		else {
			lmotor = std::max(jy, -jx);
			rmotor = jy + jx;
		}
	} else {
		if (jx > 0.0) {
			lmotor = -std::max(-jy, jx);
			rmotor = jy + jx;
		} else {
			lmotor = jy - jx;
			rmotor = -std::max(-jy, -jx);
		}
	}


	//Set Value to Motor Controllers
	if(m_driveSlowButton->Get() == OperatorButton::kReleased)
	{
		m_leftDriveMotor1->Set(-lmotor);
		m_rightDriveMotor1->Set(rmotor);
		m_leftDriveMotor2->Set(-lmotor);
		m_rightDriveMotor2->Set(rmotor);
	}

	if(m_driveSlowButton->Get() == OperatorButton::kPressed)
		{
			m_leftDriveMotor1->Set(-lmotor * .35);
			m_rightDriveMotor1->Set(rmotor * .35);
			m_leftDriveMotor2->Set(-lmotor * .35);
			m_rightDriveMotor2->Set(rmotor * .35);
		}
	SmartDashboard::PutNumber("RM", rdead);
	SmartDashboard::PutNumber("LM", ldead);

	SmartDashboard::PutBoolean("driveSlow", m_driveSlowButton->GetBool());
}

double DriveSubsystem::ApplyDeadzone(double input, double deadzone) {
	double value;

	if (fabs(input) < deadzone) {
		value = 0.0;
	} else if (input < 0.0) {
		value = (input + deadzone) / (1.0 - deadzone);
	} else {
		value = (input - deadzone) / (1.0 - deadzone);
	}
	return value;
}

 void DriveSubsystem::Accel(Joystick *js)
 {

	 if (a <  js->GetX() + .1)
	 {
		 a = a +.05;
	 }

	 if (a > js->GetX() - .1)
	 {
		 a = a - .05;
	 }

	 if (b < js->GetY() + .1)
	 {
		 b = b +.05;
	 }

	 if (b > js->GetY() - .1)
	 {
		 b = b - .05;
	 }

	 if(js->GetX() > -.1 && js->GetX() < .1)
	 {
		 a = 0;
	 }

	 if(js->GetY() > -.15 && js->GetY() < .15)
	  {
	 	 b = 0;
	  }
	 if (a > .1)
	 {
		 accelA = a -.1;
	 }
	 if (a < -.15)
	 {
		 accelA = a + .1;
	 }

	 if(a > -.1 && a < .1)
	 {
		 accelA = 0;
	 }

	 if(b > .15)
	 {
		 accelB = b - .15;
	 }
	 if(b < -.15)
	 {
		 accelB = b + .15;
	 }
	 if(b > -.15 && b < .15)
		 {
			 accelB = 0;
		 }



}

 void DriveSubsystem::Accel2(Joystick *js_right, Joystick *js_left)
 {
//  a and b are arbitrary variables used to track where the joystick was last update cycle
// accelA  and accelB are joystick values after being truncaded by deadzone
	 if (a <  js_left->GetY() + .1)
	 {
		 a = a + .05;
	 }

	 if (a > js_left->GetY() - .1)
	 {
		 a = a - .05;
	 }

	 if (b < js_right->GetY() + .1)
	 {
		 b = b +.05;
	 }

	 if (b > js_right->GetY() - .1)
	 {
		 b = b - .05;
	 }

	 if(js_left->GetY() > -.1 && js_left->GetY() < .1)
	 {
		 a = 0;
	 }

	 if(js_right->GetY() > -.15 && js_right->GetY() < .15)
	  {
	 	 b = 0;
	  }
	 if (a > .1)
	 {
		 accelA = a -.1;
	 }
	 if (a < -.15)
	 {
		 accelA = a + .1;
	 }

	 if(a > -.1 && a < .1)
	 {
		 accelA = 0;
	 }

	 if(b > .15)
	 {
		 accelB = b - .15;
	 }
	 if(b < -.15)
	 {
		 accelB = b + .15;
	 }
	 if(b > -.15 && b < .15)
		 {
			 accelB = 0;
		 }



}

// ---------------------------------------------------------------------------------------------------------------

 void DriveSubsystem::SetTargetDistanceInInches(double leftTargetValue, double rightTargetValue)
 {
 	m_leftEncoderTarget = leftTargetValue;
 	m_rightEncoderTarget = rightTargetValue;
 }

 void DriveSubsystem::DriveByDistanceLeft(double drivespeed)
 {
 	if (m_leftEncoder->GetDistance() < m_leftEncoderTarget )
 	{
 		m_leftDriveMotor1->Set(drivespeed);
 		m_leftDriveMotor2->Set(drivespeed);
 	}

 	else
 	{
 		m_leftDriveMotor1->Set(0);
 		m_leftDriveMotor2->Set(0);

 	}

 }

void DriveSubsystem::DriveByDistanceRight(double drivespeed)
 {
	if (m_rightEncoder->GetDistance() < m_rightEncoderTarget)
	 	{
	 		m_rightDriveMotor1->Set(-drivespeed);
	 		m_rightDriveMotor2->Set(-drivespeed);
	 	}
	 	else
	 	{
	 		m_rightDriveMotor1->Set(0);
	 		m_rightDriveMotor2->Set(0);
	 	}
 }

void DriveSubsystem::DriveByDistanceRightBack(double drivespeed)
 {
	if (m_rightEncoder->GetDistance() > m_rightEncoderTarget)
	 	{
	 		m_rightDriveMotor1->Set(drivespeed);
	 		m_rightDriveMotor2->Set(drivespeed);
	 	}
	 	else
	 	{
	 		m_rightDriveMotor1->Set(0);
	 		m_rightDriveMotor2->Set(0);
	 	}
 }
void DriveSubsystem::DriveByDistanceLeftBack(double drivespeed)
{
	if (m_leftEncoder->GetDistance() > m_leftEncoderTarget )
	{
		m_leftDriveMotor1->Set(-drivespeed);
		m_leftDriveMotor2->Set(-drivespeed);
	}

	else
	{
		m_leftDriveMotor1->Set(0);
		m_leftDriveMotor2->Set(0);

	}

}
 bool DriveSubsystem::GetIsAutoDriveStarted()
 {
 	if ((m_leftEncoder->GetDistance() >= (m_leftEncoderTarget / 4)) && (m_rightEncoder->GetDistance() >= (m_rightEncoderTarget / 4)))
 	{
 		return true;
 	}
 	else
 	{
 		return false;
 	}
 }

 bool DriveSubsystem::GetIsAutoDriveFinishedLeft()
 {
 	if ((m_leftEncoder->GetDistance() >= m_leftEncoderTarget))
 	{
 		return true;
 	}
 	else
 	{
 		return false;
 	}
 }

 bool DriveSubsystem::GetIsAutoDriveFinishedRight(){

	 if(m_rightEncoder->GetDistance() >= m_rightEncoderTarget)
	 {
		 return true;
	 }
	 else
	 {
		 return false;
	 }

 }
 bool DriveSubsystem::GetIsAutoDriveFinishedRightBack(){

	 if(m_rightEncoder->GetDistance() <= m_rightEncoderTarget)
	 {
		 return true;
	 }
	 else
	 {
		 return false;
	 }

 }

 bool DriveSubsystem::GetIsAutoDriveFinishedLeftBack(){

	 if(m_leftEncoder->GetDistance() <= m_leftEncoderTarget)
	 {
		 return true;
	 }
	 else
	 {
		 return false;
	 }

 }



