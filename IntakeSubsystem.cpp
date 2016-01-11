#include "IntakeSubsystem.h"
#include "Constants.h"


IntakeSubsystem::IntakeSubsystem()
{
	m_xbox = new Joystick(2);
	m_intakeLeftMotor = new VictorSP(c_intakeLeftMotorPort);
	m_intakeRightMotor = new VictorSP(c_intakeRightMotorPort);
	m_armLeftMotor = new VictorSP(c_armLeftMotorPort);
	m_armRightMotor = new VictorSP(c_armRightMotorPort);
	//m_armLeftLimitSwitch = new DigitalInput(c_armLeftLimitSwitchPort);
	//m_armRightLimitSwitch = new DigitalInput(c_armRightLimitSwitchPort);
}

void IntakeSubsystem::DoRobotInit()
{

}

void IntakeSubsystem::DoTeleopInit()
{

}

void IntakeSubsystem::DoTeleopPeriodic()
{
	if (!m_xbox->GetRawButton(4) && !m_xbox->GetRawButton(6))
	{
		m_armLeftMotor->Set(0);
		m_armRightMotor->Set(0);
	}

	if (m_xbox->GetRawButton(4) == true)
	{
		m_armLeftMotor->Set(-.55);
		m_armRightMotor->Set(-.55);
	}

	if(m_xbox->GetRawButton(6) == true)
	{
		m_armLeftMotor->Set(.55);
		m_armRightMotor->Set(.55);
	}


	if (m_xbox->GetRawButton(9) == true)
	{
		if (m_xbox->GetRawAxis(4) < .1 && m_xbox->GetRawAxis(4) > -.1)
			{
				m_intakeLeftMotor->Set(0);
				m_intakeRightMotor->Set(0);
			}

		if (m_xbox->GetRawAxis(4) > .1 || m_xbox->GetRawAxis(4) < -.1)
			{
					m_intakeLeftMotor->Set(m_xbox->GetRawAxis(4));
					m_intakeRightMotor->Set(m_xbox->GetRawAxis(4));
			}
	}

	if (m_xbox->GetRawButton(9) == false)
	{
		if (m_xbox->GetRawAxis(5) < .1 && m_xbox->GetRawAxis(5) > -.1)
		{
			m_intakeLeftMotor->Set(0);
			m_intakeRightMotor->Set(0);
		}

		if (m_xbox->GetRawAxis(5) > .1 || m_xbox->GetRawAxis(5) < -.1)
		{
				m_intakeLeftMotor->Set(m_xbox->GetRawAxis(5));
				m_intakeRightMotor->Set(-m_xbox->GetRawAxis(5));
		}
	}
}


void IntakeSubsystem::DoAutonomousInit()
{

}

void IntakeSubsystem::DoAutonomousPeriodic()
{

}

