#ifndef ELEVATOR_SUBSYSTEM
#define ELEVATOR_SUBSYSTEM

#include "RobotSubsystem.h"
#include "WPILib.h"
#include "OperatorButton.h"

class ElevatorSubsystem : public RobotSubsystem
{
public:
	ElevatorSubsystem();
	virtual void DoRobotInit();
	virtual void DoTeleopInit();
	virtual void DoTeleopPeriodic();
	virtual void DoAutonomousInit();
	virtual void DoAutonomousPeriodic();

	void IndexByOne();
	int elevatorIndex;
	int m_elevatorState;
	bool m_elevatorIsRunning;
	AnalogInput *m_fourbarLimitSwitch;


private:



	//Encoders
	Encoder *m_elevatorEncoder;

	//Talons
	VictorSP *m_elevatorMotor;

	//Operator Buttons
	OperatorButton *m_elevatorIndexButton;
	OperatorButton *m_elevatorDisengageButton;
	OperatorButton *m_elevatorResetButton;
	OperatorButton *m_masterFaultReset;
	OperatorButton *m_elevatorDeIndexButton;
	OperatorButton *m_tankDisengageButton;
	OperatorButton *m_fourbarLockOverrideButton;

	//Joysticks
	Joystick *m_operatorJoystick;
	Joystick *m_xbox;

	//Limit Switches
	AnalogInput *m_elevatorResetLimitSwitch;
	AnalogInput *m_elevatorStopLimitSwitch;

	Timer *m_timer;
	Timer *m_deindexTimer;
	Timer *m_solenoidTimer;
	double last;
	double m_error;
	double m_elevatorFault1;
	double m_elevatorFault2;
	int m_loopCount;
	bool m_elevatorFaultOccured;
	bool TankMode;
	bool isResetting;
	bool homeswitchhit;
	bool stopswitchhit;
	bool indexstop;
	bool deindexstop;
	double pos6dist;
	bool fourbarLimitSwitchPressed;
	bool fourbarLimitSwitchOverride;

	//DIO for LED Light Strip (Using PCM ports/Solenoids) NOT AN ACTUAL SOLENOID
	Solenoid *m_LEDLight1;
	Solenoid *m_LEDLight2;






};

#endif
