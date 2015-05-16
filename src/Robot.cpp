#include "WPILib.h"

///// USER PARAMETERS /////

// Tuning Parameters
#define throScale	1

// Wiring Parameters
#define frontLeftChannel	3
#define backLeftChannel		4
#define frontRightChannel	1
#define backRightChannel	2

#define InterLink_Elite_ID	0

///// END USER PARAMETERS /////

class Robot: public IterativeRobot
{
	LiveWindow *lw;
	DriverStation *ds;

	// Motor Controllers
	Talon *frontLeft;
	Talon *backLeft;
	Talon *frontRight;
	Talon *backRight;

	// Input Devices
	Joystick *InterLink;
public:
	Robot()
	{
		frontLeft = new Talon( frontLeftChannel );
		backLeft = new Talon( backLeftChannel );
		frontRight = new Talon( frontRightChannel );
		backRight = new Talon( backRightChannel );

		ds = DriverStation::GetInstance();
		InterLink = new Joystick( InterLink_Elite_ID );
	}

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
	}

	//////////////////////
	///// AUTONOMOUS /////
	//////////////////////

	void AutonomousInit()
	{}

	void AutonomousPeriodic()
	{}

	////////////////////////
	///// TELEOPERATED /////
	////////////////////////

	void TeleopInit()
	{}

	void TeleopPeriodic()
	{}

	////////////////
	///// TEST /////
	////////////////

	void TestPeriodic()
	{
		lw->Run();
		SmartDashboard::PutBoolean( "resetButton", InterLink->GetRawButton(2) );
	}
};

START_ROBOT_CLASS(Robot);
