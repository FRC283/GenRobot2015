#include "ElevatorSubsystem.h"
#include "Constants.h"

ElevatorSubsystem::ElevatorSubsystem()
{
	m_elevatorEncoder = new Encoder(c_elevatorEncoderPortA, c_elevatorEncoderPortB);
	m_elevatorMotor = new VictorSP(c_elevatorMotorPort);
	m_elevatorIndexButton = new OperatorButton(1, c_elevatorIndexButtonPort);
	m_elevatorDisengageButton = new OperatorButton(1, c_elevatorDisengageButtonPort);
	m_elevatorResetButton = new OperatorButton(1,c_elevatorResetButtonPort );
	m_elevatorDeIndexButton = new OperatorButton(2,7);
	m_operatorJoystick = Joystick::GetStickForPort(c_joystickRightPort);
	m_xbox = new Joystick(c_operatorJoystickPort);
	m_masterFaultReset = new OperatorButton(c_masterFaultResetStickPort, c_masterFaultResetButtonPort);
	m_timer = new Timer();
	m_solenoidTimer = new Timer();
	m_elevatorEncoder->SetDistancePerPulse(1);
	m_elevatorResetLimitSwitch = new AnalogInput(c_elevatorResetLimitSwitchPort);
	m_elevatorStopLimitSwitch = new AnalogInput(c_elevatorStopLimitSwitchPort);
	m_deindexTimer = new Timer();
	bool m_elevatorIsRunning; // Variable for the while loop which just states whether or not the elevator is currently running/in motion
	m_LEDLight1 = new Solenoid(1);
	m_LEDLight2 = new Solenoid(0);
	m_fourbarLimitSwitch = new AnalogInput(c_fourbarLimitSwitchPort);
	m_fourbarLockOverrideButton = new OperatorButton(0, c_fourbarOverrideButtonPort);
	fourbarLimitSwitchPressed = false;
	m_tankDisengageButton = new OperatorButton(1, 3);




}

void ElevatorSubsystem::DoRobotInit()
{
	elevatorIndex = 0;
	m_elevatorIsRunning = false;
	m_elevatorState = 0;
	m_error = 0;
	isResetting = false;
	homeswitchhit = false;
	stopswitchhit = false;
	indexstop = false;
	deindexstop = false;
	pos6dist =  949;
}

void ElevatorSubsystem::DoTeleopInit()
{
	m_elevatorState = 0;
	m_elevatorMotor->Set(0);
	last = 0;
	m_elevatorFaultOccured = false;
	m_elevatorFault1 = 0;
	m_elevatorFault2 = 0;
}

void ElevatorSubsystem::DoTeleopPeriodic()
{
	if (m_fourbarLockOverrideButton->Get() == OperatorButton::kJustPressed)
	{
		fourbarLimitSwitchOverride = !fourbarLimitSwitchOverride;
	}

	m_LEDLight1->Set(false);
	m_LEDLight2->Set(false);


	m_elevatorFaultOccured = false;
	if (m_elevatorResetLimitSwitch->GetVoltage() > 4 && m_elevatorIndexButton->Get() != OperatorButton::kPressed)
	{
		if( m_elevatorStopLimitSwitch->GetVoltage() < 2)
		{
			homeswitchhit = true;
			m_elevatorEncoder->Reset();
			m_elevatorIsRunning = false;
			if(m_elevatorState > 1)
			{
				m_elevatorState = 1;
			}
		}

	}

	if(homeswitchhit == true)
	{
		m_elevatorMotor->Set(0);

	}

	if(m_elevatorStopLimitSwitch->GetVoltage() > 4
			&& m_elevatorDeIndexButton->Get() != OperatorButton::kPressed
			&& m_elevatorDisengageButton->Get() != OperatorButton::kPressed
			&& m_elevatorResetButton->Get() != OperatorButton::kPressed)
	{
		if(m_elevatorResetLimitSwitch->GetVoltage() < 2)
		{
			stopswitchhit = true;
			m_elevatorIsRunning = false;
			if(m_elevatorState == 6)
			{
				pos6dist = m_elevatorEncoder->GetDistance();
			}

		}
	}

	if(stopswitchhit == true)
	{
		if (m_elevatorState < 5 && m_elevatorState != 999)
		{
			m_elevatorMotor->Set(0);
		}

	}


	if (m_xbox->GetRawButton(3) == false)
	{

		if (m_elevatorState > 6 && !(m_elevatorState == 999))
		{
			m_elevatorMotor->Set(0);
			m_elevatorState = 6;
		}

		if (m_elevatorState < 0)
		{
			m_elevatorState = 0;
		}


// TANK MODE--------------------------------------------------------------------------------------------------------------------------------------------

		if (m_fourbarLimitSwitch->GetVoltage() < .2 || fourbarLimitSwitchOverride)
		{
			if (m_elevatorIndexButton->Get() == OperatorButton::kPressed && stopswitchhit == false)
			{

				if (m_elevatorIsRunning == false &&  indexstop == false)
					{
						m_LEDLight1->Set(true);
						m_LEDLight2->Set(false);
						m_elevatorState++;
						indexstop = true;
					}
			}
		}

		if(m_elevatorIndexButton->Get() == OperatorButton::kPressed)
		{

			homeswitchhit = false;
			m_timer->Reset();
		}
		if(m_elevatorIndexButton->Get() == OperatorButton::kReleased)
		{
			m_timer->Start();
			if(m_timer->Get() > .5)
			{
				indexstop = false;
				m_timer->Stop();
			}
		}


		if (m_elevatorDeIndexButton->Get() == OperatorButton::kPressed  && homeswitchhit == false  )
		{

			if (m_elevatorIsRunning == false && deindexstop == false)
			{
				m_LEDLight1->Set(false);
				m_LEDLight2->Set(true);
				m_elevatorState--;
				deindexstop = true;


			}

		}
		if (m_elevatorDeIndexButton->Get() == OperatorButton::kPressed)
		{
			stopswitchhit = false;
			m_deindexTimer->Reset();
		}

		if (m_elevatorDeIndexButton->Get() == OperatorButton::kReleased)
		{
			m_deindexTimer->Start();
			if(m_deindexTimer->Get() > .5)
			{
				deindexstop = false;
				m_deindexTimer->Stop();
			}
		}

		if (m_elevatorResetButton->Get() == OperatorButton::kPressed  && homeswitchhit == false  )
		{

			if (m_elevatorIsRunning == false)
			{
				m_LEDLight1->Set(true);
				m_LEDLight2->Set(true);

				m_elevatorState = 0;
			}

		}
		if (m_elevatorResetButton->Get() == OperatorButton::kPressed )
		{
			stopswitchhit = false;
		}

		if (m_tankDisengageButton->Get() == OperatorButton::kPressed && homeswitchhit == false  )
		{
			if (m_elevatorState > 0)
			{

				if (m_elevatorIsRunning == false)
				{
					m_elevatorState = 999;

				}

			}
		}
		if (m_tankDisengageButton->Get() == OperatorButton::kPressed )
		{
			stopswitchhit = false;
		}
	}

	if (m_masterFaultReset->Get() == OperatorButton::kPressed)
	{
		m_elevatorFaultOccured = false;
		stopswitchhit = false;
		homeswitchhit = false;
	}
	IndexByOne();
	SmartDashboard::PutBoolean("Elevator Fault", m_elevatorFaultOccured);



	if (m_xbox->GetRawButton(3) == true)
	{
		if (m_elevatorStopLimitSwitch->GetVoltage() > 4)
		{
			m_elevatorMotor->Set(0);
		}

		if (m_xbox->GetRawAxis(3) > .1 && m_xbox->GetRawAxis(2) < .1 && stopswitchhit == false)
		{
			m_elevatorMotor->Set(m_xbox->GetRawAxis(3));
		}
		if (m_xbox->GetRawAxis(2) > .1 && m_xbox->GetRawAxis(3) < .1  && homeswitchhit == false)
		{
			m_elevatorMotor->Set(-1 * m_xbox->GetRawAxis(2));
		}
		if (m_xbox->GetRawAxis(2) < .1 && m_xbox->GetRawAxis(3) < .1)
		{
			m_elevatorMotor->Set(0);
		}
	}

	SmartDashboard::PutNumber("lifterEncoder",
			m_elevatorEncoder->GetDistance());
	SmartDashboard::PutNumber("elevator state", m_elevatorState);
	SmartDashboard::PutBoolean("elevatorbool", m_elevatorIsRunning);
	SmartDashboard::PutNumber("limitA", m_elevatorResetLimitSwitch->GetVoltage());
	SmartDashboard::PutNumber("limitB", m_elevatorStopLimitSwitch->GetVoltage() );
	SmartDashboard::PutBoolean("tank mode", TankMode);
	SmartDashboard::PutBoolean("stop switch", stopswitchhit);
	SmartDashboard::PutBoolean("home switch", homeswitchhit);
	SmartDashboard::PutBoolean("Index Button", m_elevatorIndexButton->GetBool());
	SmartDashboard::PutBoolean("index stop", indexstop);
	SmartDashboard::PutBoolean("deindex stop", deindexstop);
	SmartDashboard::PutNumber("timer", m_timer->Get());
	SmartDashboard::PutNumber("Fourbar Limit Switch", m_fourbarLimitSwitch->GetVoltage());
	SmartDashboard::PutNumber("Solenoid Valve Timer", m_solenoidTimer->Get());
	SmartDashboard::PutBoolean("Limit Switch Override: ", fourbarLimitSwitchOverride);


}

void ElevatorSubsystem::DoAutonomousInit()
{
	//m_elevatorState = 0;
}

void ElevatorSubsystem::DoAutonomousPeriodic()
{
	IndexByOne();
	if (m_elevatorResetLimitSwitch->GetVoltage() > 4 && m_elevatorIndexButton->Get() != OperatorButton::kPressed)
			{
			if( m_elevatorStopLimitSwitch->GetVoltage() < 2)
			{
				homeswitchhit = true;
				m_elevatorEncoder->Reset();
				m_elevatorIsRunning = false;
			}

			}
		if(homeswitchhit == true)
		{
			m_elevatorMotor->Set(0);

		}

		if(m_elevatorStopLimitSwitch->GetVoltage() > 4
				&& m_elevatorDeIndexButton->Get() != OperatorButton::kPressed
				&& m_elevatorDisengageButton->Get() != OperatorButton::kPressed
				&& m_elevatorResetButton->Get() != OperatorButton::kPressed)
		{
			if(m_elevatorResetLimitSwitch->GetVoltage() < 2)
			{
				stopswitchhit = true;
				m_elevatorIsRunning = false;
				if(m_elevatorState == 6)
				{
					pos6dist = m_elevatorEncoder->GetDistance();
				}

			}
		}

		if(stopswitchhit == true)
		{
			if (m_elevatorState < 6 && m_elevatorState != 999)
			{
				m_elevatorMotor->Set(0);
			}
			if(m_elevatorState ==  555)
			{
				m_elevatorMotor->Set(0);
			}

}
}

void ElevatorSubsystem::IndexByOne()
{
	switch(m_elevatorState)
	{
	case 0:
		if (m_elevatorResetLimitSwitch->GetVoltage() < 2.5)
		{
			if(m_elevatorEncoder->GetDistance() < 100 && homeswitchhit == false && m_elevatorEncoder->GetDistance() > -30)
			{
				m_elevatorMotor->Set(-.15);
			}
			if(m_elevatorEncoder->GetDistance() < 0  && homeswitchhit == true)
			{
				m_elevatorMotor->Set(.15);
			}
		}
		if (m_loopCount > c_processorSpeedPerSecond)
		{
			m_loopCount = 0;
		}

		if (stopswitchhit == false && homeswitchhit == false )
		{
			m_error = c_pos0Dist - m_elevatorEncoder->GetDistance();
			if(m_elevatorEncoder->GetDistance() > 100)
			{
				m_elevatorMotor->Set((c_elevatorP * m_error) / c_correction);

			}
		}

		if (m_loopCount == c_processorClock1)
		{
			m_elevatorFault1 = m_elevatorEncoder->GetDistance();
		}

		if (m_loopCount == c_processorClock2)
		{
			m_elevatorFault2 = m_elevatorEncoder->GetDistance();
		}

		if (m_elevatorFault2 - m_elevatorFault1 < c_elevatorEncoderFaultBound
				&& m_elevatorFault2 - m_elevatorFault1
						> -c_elevatorEncoderFaultBound
				&& m_loopCount > c_processorCheck)
		{
			if (m_error > 30 || m_error < -30)
			{
				m_elevatorFaultOccured = true;
			}
		}

		if (m_elevatorFaultOccured == true)
		{
			//m_elevatorMotor->Set(0);
		}

		if (m_elevatorEncoder->GetDistance() > c_pos0Dist + 3
				|| m_elevatorEncoder->GetDistance() < c_pos0Dist - 3)
		{
			m_elevatorIsRunning = true;
		}
		if (m_elevatorEncoder->GetDistance() < c_pos0Dist + 3
				&& m_elevatorEncoder->GetDistance() > c_pos0Dist - 3)
		{
			elevatorIndex = 0;
			m_elevatorIsRunning = false;
			last = c_pos0Dist;
		}

			m_loopCount++;
		break;
	case 1:

		if (m_loopCount > c_processorSpeedPerSecond)
		{
			m_loopCount = 0;
		}

		if (stopswitchhit == false && homeswitchhit == false)
		{
			m_error = c_pos1Dist - m_elevatorEncoder->GetDistance();
			m_elevatorMotor->Set((.03 * m_error) / c_correction);
		}

		if (m_loopCount == c_processorClock1)
		{
			m_elevatorFault1 = m_elevatorEncoder->GetDistance();
		}

		if (m_loopCount == c_processorClock2)
		{
			m_elevatorFault2 = m_elevatorEncoder->GetDistance();
		}

		if (m_elevatorFault2 - m_elevatorFault1 < c_elevatorEncoderFaultBound
				&& m_elevatorFault2 - m_elevatorFault1
						> -c_elevatorEncoderFaultBound
				&& m_loopCount > c_processorCheck)
		{
			if (m_error > 30 || m_error < -30)
			{
				m_elevatorFaultOccured = true;
			}
		}

		if (m_elevatorFaultOccured == true)
		{
			//m_elevatorMotor->Set(0);
		}
		if (m_elevatorEncoder->GetDistance() > c_pos1Dist + 3
				|| m_elevatorEncoder->GetDistance() < c_pos1Dist - 3)
		{
			m_elevatorIsRunning = true;
		}
		if (m_elevatorEncoder->GetDistance() < c_pos1Dist + 3
				&& m_elevatorEncoder->GetDistance() > c_pos1Dist - 3)
		{
			elevatorIndex = 1;
			m_elevatorIsRunning = false;
			last = c_pos1Dist;
		}

		m_loopCount++;
			break;
	case 2:
		if (m_loopCount > c_processorSpeedPerSecond)
		{
			m_loopCount = 0;
		}

		if (/* m_elevatorFaultOccured == false  && */stopswitchhit == false
				&& homeswitchhit == false)
		{
			m_error = c_pos2Dist - m_elevatorEncoder->GetDistance();
			m_elevatorMotor->Set((c_elevatorP * m_error) / c_correction);
		}

		if (m_loopCount == c_processorClock1)
		{
			m_elevatorFault1 = m_elevatorEncoder->GetDistance();
		}

		if (m_loopCount == c_processorClock2)
		{
			m_elevatorFault2 = m_elevatorEncoder->GetDistance();
		}

		if (m_elevatorFault2 - m_elevatorFault1 < c_elevatorEncoderFaultBound
				&& m_elevatorFault2 - m_elevatorFault1
						> -c_elevatorEncoderFaultBound
				&& m_loopCount > c_processorCheck)
		{
			if (m_error > 30 || m_error < -30)
			{
				m_elevatorFaultOccured = true;
			}
		}

		if (m_elevatorFaultOccured == true)
		{
			//m_elevatorMotor->Set(0);
		}

		if (m_elevatorEncoder->GetDistance() > c_pos2Dist + 3
				|| m_elevatorEncoder->GetDistance() < c_pos2Dist - 3)
		{
			m_elevatorIsRunning = true;
		}
		if (m_elevatorEncoder->GetDistance() < c_pos2Dist + 3
				&& m_elevatorEncoder->GetDistance() > c_pos2Dist - 3)
		{
			elevatorIndex = 2;
			m_elevatorIsRunning = false;
			last = c_pos2Dist;
		}

		m_loopCount++;
			break;
	case 3:
		if(m_loopCount > c_processorSpeedPerSecond)
					{
						m_loopCount = 0;
					}

						if(/* m_elevatorFaultOccured == false  && */  stopswitchhit == false && homeswitchhit == false  )
					{
						m_error = c_pos3Dist - m_elevatorEncoder->GetDistance();
						m_elevatorMotor->Set((.045 * m_error) / c_correction);
					}

						if(m_loopCount == c_processorClock1)
						{
								m_elevatorFault1 = m_elevatorEncoder->GetDistance();
						}

						if(m_loopCount == c_processorClock2)
						{
								m_elevatorFault2 = m_elevatorEncoder->GetDistance();
						}

						if(m_elevatorFault2 - m_elevatorFault1 < c_elevatorEncoderFaultBound &&  m_elevatorFault2 - m_elevatorFault1 > -c_elevatorEncoderFaultBound && m_loopCount > c_processorCheck)
						{
							if(m_error > 30 || m_error < -30)
							{
								m_elevatorFaultOccured = true;
							}
						}

						if(m_elevatorFaultOccured == true)
						{
							//m_elevatorMotor->Set(0);
						}


					if(m_elevatorEncoder->GetDistance() > c_pos3Dist + 3 || m_elevatorEncoder->GetDistance() < c_pos3Dist - 3)
					{
						m_elevatorIsRunning = true;
					}
					if(m_elevatorEncoder->GetDistance() < c_pos3Dist + 3 && m_elevatorEncoder->GetDistance() > c_pos3Dist - 3 )
					{
						elevatorIndex = 3;
						m_elevatorIsRunning = false;
						last = c_pos3Dist;
					}

					m_loopCount++;
			break;
	case 4:
		if(m_loopCount > c_processorSpeedPerSecond)
					{
						m_loopCount = 0;
					}

						if(/* m_elevatorFaultOccured == false  && */  stopswitchhit == false && homeswitchhit == false )
					{
						m_error = c_pos4Dist - m_elevatorEncoder->GetDistance();
						m_elevatorMotor->Set((.05 * m_error) / c_correction);
					}

						if(m_loopCount == c_processorClock1)
						{
								m_elevatorFault1 = m_elevatorEncoder->GetDistance();
						}

						if(m_loopCount == c_processorClock2)
						{
								m_elevatorFault2 = m_elevatorEncoder->GetDistance();
						}

						if(m_elevatorFault2 - m_elevatorFault1 < c_elevatorEncoderFaultBound &&  m_elevatorFault2 - m_elevatorFault1 > -c_elevatorEncoderFaultBound && m_loopCount > c_processorCheck)
						{
							if(m_error > 30 || m_error < -30)
							{
								m_elevatorFaultOccured = true;
							}
						}

						if(m_elevatorFaultOccured == true)
						{
							//m_elevatorMotor->Set(0);
						}

					if(m_elevatorEncoder->GetDistance() > c_pos4Dist + 3 || m_elevatorEncoder->GetDistance() < c_pos4Dist - 3)
					{
						m_elevatorIsRunning = true;
					}
					if(m_elevatorEncoder->GetDistance() < c_pos4Dist + 3 && m_elevatorEncoder->GetDistance() > c_pos4Dist - 3 )
					{
						elevatorIndex = 4;
						m_elevatorIsRunning = false;
						last = c_pos4Dist;
					}

					m_loopCount++;
			break;
	case 5:
		if(m_loopCount > c_processorSpeedPerSecond)
					{
						m_loopCount = 0;
					}

						if(/* m_elevatorFaultOccured == false  && */homeswitchhit == false )
					{
						m_error = c_pos5Dist - m_elevatorEncoder->GetDistance();
						m_elevatorMotor->Set((.07 * m_error) / c_correction);
					}

						if(m_loopCount == c_processorClock1)
						{
								m_elevatorFault1 = m_elevatorEncoder->GetDistance();
						}

						if(m_loopCount == c_processorClock2)
						{
								m_elevatorFault2 = m_elevatorEncoder->GetDistance();
						}

						if(m_elevatorFault2 - m_elevatorFault1 < c_elevatorEncoderFaultBound &&  m_elevatorFault2 - m_elevatorFault1 > -c_elevatorEncoderFaultBound && m_loopCount > c_processorCheck)
						{
							if(m_error > 30 || m_error < -30)
							{
								m_elevatorFaultOccured = true;
							}
						}

						if(m_elevatorFaultOccured == true)
						{
							//m_elevatorMotor->Set(0);
						}


					if(m_elevatorEncoder->GetDistance() > c_pos5Dist + 3 || m_elevatorEncoder->GetDistance() < c_pos5Dist - 3)
					{
						m_elevatorIsRunning = true;
					}
					if(m_elevatorEncoder->GetDistance() < c_pos5Dist + 3 && m_elevatorEncoder->GetDistance() > c_pos5Dist - 3 )
					{
						elevatorIndex = 5;
						m_elevatorIsRunning = false;
						last = c_pos5Dist;
					}

					m_loopCount++;
			break;
	case 6:
		if(m_loopCount > c_processorSpeedPerSecond)
					{
						m_loopCount = 0;
					}
		if(stopswitchhit == false)
		{
			m_elevatorMotor->Set(.25);
		}
				if(stopswitchhit == true)
					{
						m_error = pos6dist - m_elevatorEncoder->GetDistance();
						m_elevatorMotor->Set((.2 * m_error) / c_correction); // incremets of .02
					}

						if(m_loopCount == c_processorClock1)
						{
								m_elevatorFault1 = m_elevatorEncoder->GetDistance();
						}

						if(m_loopCount == c_processorClock2)
						{
								m_elevatorFault2 = m_elevatorEncoder->GetDistance();
						}

						if(m_elevatorFault2 - m_elevatorFault1 < c_elevatorEncoderFaultBound &&  m_elevatorFault2 - m_elevatorFault1 > -c_elevatorEncoderFaultBound && m_loopCount > c_processorCheck)
						{
							if(m_error > 30 || m_error < -30)
							{
								//m_elevatorFaultOccured = true;
							}
						}

						if(m_elevatorFaultOccured == true)
						{
							m_elevatorMotor->Set(0);
						}


					if(m_elevatorEncoder->GetDistance() > pos6dist + 3 || m_elevatorEncoder->GetDistance() < pos6dist - 3)
					{
						m_elevatorIsRunning = true;
					}
					if(m_elevatorEncoder->GetDistance() < pos6dist + 3 && m_elevatorEncoder->GetDistance() > pos6dist - 3 )
					{
						elevatorIndex = 6;
						m_elevatorIsRunning = false;
						last = pos6dist;
					}

					m_loopCount++;

			break;
		// 999 is disengage case
	case 999:
		if(m_loopCount > c_processorSpeedPerSecond)
					{
						m_loopCount = 0;
					}

						if(stopswitchhit == false && homeswitchhit == false )
					{
							if(m_elevatorEncoder->GetDistance() > last - c_disengageDistance + c_elevatorWindow )
								{
									m_elevatorMotor->Set(- c_liftSpeed);
									m_elevatorIsRunning = true;
								}

								if(m_elevatorEncoder->GetDistance() < last - c_disengageDistance - c_elevatorWindow )
								{
									m_elevatorMotor->Set(c_liftSpeed);
									m_elevatorIsRunning = true;
								}

								if(m_elevatorEncoder->GetDistance() < last - c_disengageDistance + c_elevatorWindow &&
										m_elevatorEncoder->GetDistance() > last - c_disengageDistance - c_elevatorWindow  )
								{
									m_elevatorMotor->Set(0);
									m_elevatorIsRunning = false;
								}
					}

						if(m_loopCount == c_processorClock1)
						{
								m_elevatorFault1 = m_elevatorEncoder->GetDistance();
						}

						if(m_loopCount == c_processorClock2)
						{
								m_elevatorFault2 = m_elevatorEncoder->GetDistance();
						}

						if(m_elevatorFault2 - m_elevatorFault1 < c_elevatorEncoderFaultBound &&  m_elevatorFault2 - m_elevatorFault1 > -c_elevatorEncoderFaultBound && m_loopCount > c_processorCheck)
						{
							if(m_error > 30 || m_error < -30)
							{
									m_elevatorFaultOccured = true;
							}
						}

						if(m_elevatorFaultOccured == true)
						{
							//m_elevatorMotor->Set(0);
						}


		m_loopCount++;

		break;

	case 555:
			m_error = 60 - m_elevatorEncoder->GetDistance();
			m_elevatorMotor->Set((.14 * m_error) / c_correction);

			if (m_elevatorEncoder->GetDistance()  < 63 && m_elevatorEncoder->GetDistance() > 57)
			{
				m_elevatorIsRunning = false;
				homeswitchhit = false;
			}
			if (m_elevatorEncoder->GetDistance() < 57)
			{
				m_elevatorIsRunning = true;
			}

		break;
	}

	SmartDashboard::PutNumber("last", last);

}


