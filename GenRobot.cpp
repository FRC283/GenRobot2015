#include "GenRobot.h"

GenRobot::GenRobot(void)
{


}

void GenRobot::RobotInit()
{
	m_driveSubsystem = new DriveSubsystem();
	m_forebarSubsystem = new ForebarSubsystem();
	m_elevatorSubsystem = new ElevatorSubsystem();
	m_intakeSubsystem = new IntakeSubsystem();
	m_xbox = new Joystick(2);
	m_autoTimer  = new Timer();


	m_driveSubsystem->DoRobotInit();
	m_elevatorSubsystem->DoRobotInit();


	SmartDashboard::init();

}

void GenRobot::AutonomousInit()
{
	m_autoState = kForebar;
	m_autoTimer->Reset();
	autostate = 0;
	m_autoSelect = 0;
}

void GenRobot::TeleopInit()
{

	m_driveSubsystem->DoTeleopInit();
	m_forebarSubsystem->DoTeleopInit();
	m_elevatorSubsystem->DoTeleopInit();


}

void GenRobot::DisabledInit()
{

}

void GenRobot::AutonomousPeriodic()
{
	if (m_autoSelect == 1)
	{

		switch (m_autoState)
		{
		case kForebar:
			autostate = 0;
			m_driveSubsystem->SetTargetDistanceInInches(0, 0);
			m_forebarSubsystem->GoToLifting();
			if (m_forebarSubsystem->IsLifting() == true)
			{

				m_autoState = kForward;
			}
			break;
		case kForward:
			autostate = 1;
			m_forebarSubsystem->GoToLifting();
			m_driveSubsystem->SetTargetDistanceInInches(342, 342);
			m_driveSubsystem->DriveByDistanceLeft(.15);
			m_driveSubsystem->DriveByDistanceRight(.15);
			if (m_driveSubsystem->GetIsAutoDriveFinishedRight()
					&& m_driveSubsystem->GetIsAutoDriveFinishedLeft())
			{
				m_autoState = kTote;
				m_autoTimer->Start();
			}
			break;
		case kTote: // Forward Slow and aquire Tote
			autostate = 3;
			m_forebarSubsystem->GoToLifting();
			m_driveSubsystem->SetTargetDistanceInInches(385, 385);
			m_driveSubsystem->DriveByDistanceLeft(.15);
			m_driveSubsystem->DriveByDistanceRight(.15);
			m_elevatorSubsystem->m_elevatorState = 555;

			if (m_driveSubsystem->GetIsAutoDriveFinishedLeft() == true
					&& m_driveSubsystem->GetIsAutoDriveFinishedRight() == true
					&& m_elevatorSubsystem->m_elevatorIsRunning == false
					&& m_autoTimer->Get() > 2)
			{
				//m_elevatorSubsystem->m_elevatorState = 1;
				m_autoState = kTurn;
			}
			break;
		case kTurn:
			m_forebarSubsystem->GoToLifting();
			m_driveSubsystem->SetTargetDistanceInInches(645, 125);
			m_driveSubsystem->DriveByDistanceLeft(.25);
			m_driveSubsystem->DriveByDistanceRightBack(.25);
			if (m_driveSubsystem->GetIsAutoDriveFinishedLeft() == true
					&& m_driveSubsystem->GetIsAutoDriveFinishedRightBack()
							== true)
			{
				m_autoState = kBackward;
			}
			break;
		case kBackward:
			m_forebarSubsystem->GoToLifting();
			m_driveSubsystem->SetTargetDistanceInInches(-661, -1187);
			m_driveSubsystem->DriveByDistanceLeftBack(.16);
			m_driveSubsystem->DriveByDistanceRightBack(.16);
			if (m_driveSubsystem->GetIsAutoDriveFinishedLeftBack() == true
					&& m_driveSubsystem->GetIsAutoDriveFinishedRightBack()
							== true)
			{
				m_autoState = kStop;
			}
			break;
		case kStop:
			autostate = 999;
			m_elevatorSubsystem->m_elevatorState = 0;
			m_driveSubsystem->DriveByDistanceLeft(0);
			m_driveSubsystem->DriveByDistanceLeft(0);
			m_forebarSubsystem->GoToLifting();
			//stop
			break;
		}

	}

	m_driveSubsystem->DoAutonomousPeriodic();
	m_elevatorSubsystem->DoAutonomousPeriodic();

	SmartDashboard::PutNumber("auto timer", m_autoTimer->Get());
	SmartDashboard::PutNumber("auto state", autostate);

}

void GenRobot::TeleopPeriodic()
{


	m_driveSubsystem->DoTeleopPeriodic();
	m_elevatorSubsystem->DoTeleopPeriodic();
	m_forebarSubsystem->DoTeleopPeriodic();
	m_intakeSubsystem->DoTeleopPeriodic();



}

void GenRobot::DisabledPeriodic()
{


}

START_ROBOT_CLASS(GenRobot);
