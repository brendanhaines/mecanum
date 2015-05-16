#include "WPILib.h"

///// USER PARAMETERS /////

// Tuning Parameters
#define throScale	1

// Wiring Parameters
#define frontLeftChannel	3
#define backLeftChannel		4
#define frontRightChannel	1
#define backRightChannel	2

#define InterLink_Elite_ID			0

///// END USER PARAMETERS /////

// InterLink Elite Channel Mapping
#define InterLink_Elite_CH5			1
#define InterLink_Elite_CH7			2
#define InterLink_Elite_RESET		3
#define InterLink_Elite_CH8_BACK	4
#define InterLink_Elite_CH8_FRONT	5

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
	{
		SmartDashboard::PutBoolean( "resetButton", InterLink->GetRawButton( InterLink_Elite_RESET ) );
	}

	////////////////
	///// TEST /////
	////////////////

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
