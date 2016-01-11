#ifndef ROBOT_SUBSYSTEM_H
#define ROBOT_SUBSYSTEM_H

class RobotSubsystem
{
public:
	RobotSubsystem();
	virtual ~RobotSubsystem();

	virtual void DoRobotInit(void);
	virtual void DoAutonomousInit(void);
	virtual void DoTeleopInit(void);
	virtual void DoDisabledInit(void);
	virtual void DoAutonomousPeriodic(void);
	virtual void DoTeleopPeriodic(void);
	virtual void DoDisabledPeriodic(void);

protected:

private:

};
#endif
