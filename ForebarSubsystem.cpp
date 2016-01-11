
#include "ForebarSubsystem.h"
#include "Constants.h"



ForebarSubsystem::ForebarSubsystem()
{
	m_forebarMotor = new VictorSP(c_forebarMotorPort);
	m_forebarEncoder = new Encoder(c_forebarEncoderPortA, c_forebarEncoderPortB);
	m_forebarHomeButton = new OperatorButton(c_operatorJoystickPort,2);
	//m_forebarButton2 = new OperatorButton(c_operatorJoystickPort,4);
	m_forebarLiftingButton = new OperatorButton(c_operatorJoystickPort,1);
	m_xbox = new Joystick(2);
	m_forebarEncoder->SetDistancePerPulse(1);
	m_masterFaultReset = new OperatorButton(c_masterFaultResetStickPort, c_masterFaultResetButtonPort);


}

void ForebarSubsystem::DoRobotInit()
{

}

void ForebarSubsystem::DoTeleopInit()
{
	m_forebarState = kLifted;
	m_isClearing = false;
	m_isLifting =  true;
	m_isResting = false;
	m_forebarFault1 = 0;
	m_forebarFault2 = 0;
	m_forebarFaultOccured = false;

}

void ForebarSubsystem::DoTeleopPeriodic()
{
	if(m_xbox->GetRawButton(5) == false)
	{
		if (m_forebarHomeButton->Get() == OperatorButton::kJustPressed
				&& m_forebarLiftingButton->Get() == OperatorButton::kReleased)
		{
				m_isResting = false;
				m_isLifting =  true;
				m_isClearing = false;
		}

		if (m_forebarLiftingButton->Get() == OperatorButton::kJustPressed
				&& m_forebarHomeButton->Get() == OperatorButton::kReleased)
		{
			m_isResting = true;
			m_isLifting =  false;
			m_isClearing = false;
		}

		if(m_forebarLiftingButton->Get() == OperatorButton::kReleased
				&& m_forebarHomeButton->Get() == OperatorButton::kReleased)
		{
			m_forebarMotor->Set(0);
			m_loopCount = 0;
			m_forebarFaultOccured = false;
		}

		if(m_isResting == true)
		{
			GoToResting();
		}

		if(m_isLifting == true)
		{
				GoToLifting();
		}

		if(m_isClearing == true)
		{
				GoToClearing();
		}

	}
	if(m_xbox->GetRawButton(5) == true)
	{
		m_forebarMotor->Set(- m_xbox->GetRawAxis(1) * .60);
		if(m_masterFaultReset->Get() == OperatorButton::kJustPressed)
			{
				m_forebarFaultOccured = false;
				m_forebarEncoder->Reset();
			}
	}


	SmartDashboard::PutNumber("fourbarencoder", m_forebarEncoder->GetDistance());
	SmartDashboard::PutBoolean("Fourbar Fault", m_forebarFaultOccured);



}


void ForebarSubsystem::DoAutonomousInit()
{

}

void ForebarSubsystem::DoAutonomousPeriodic()
{

}

void ForebarSubsystem::GoToResting()
{
	double distance1;

	if(m_forebarFaultOccured == false)
	{
	distance1 = m_forebarEncoder->GetDistance();
	error1 = c_forebarRestingDistance - distance1;
	m_forebarMotor->Set(.0017355*error1);
	}


}

void ForebarSubsystem::GoToLifting()
{

	double distance2;

	if(m_forebarFaultOccured == false)
	{
		distance2 = m_forebarEncoder->GetDistance();
		error2= c_forebarLiftingDistance - distance2;
		m_forebarMotor->Set(.02*error2);
	}


}

void ForebarSubsystem::GoToClearing()
{
	double distance3;


	if(m_forebarFaultOccured == false)
	{
	distance3 = m_forebarEncoder->GetDistance();
	error3 = c_forebarClearingDistance - distance3;
	m_forebarMotor->Set(.02*error3);
	}

}


bool ForebarSubsystem::IsLifting()
{
	if(m_forebarEncoder->GetDistance() > 1240 &&  m_forebarEncoder->GetDistance() < 1270)
	{
		m_isLifting = true;
	}
	else
	{
		m_isLifting = false;
	}

	return m_isLifting;
}

