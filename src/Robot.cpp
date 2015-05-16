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
#define InterLink_Elite_AILE		0
#define InterLink_Elite_ELEV		1
#define InterLink_Elite_THRO		2
#define	InterLink_Elite_CH6			3
#define InterLink_Elite_YAW			4

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
		// Write Buttons to SmartDashboard
		SmartDashboard::PutBoolean( "CH5", InterLink->GetRawButton( InterLink_Elite_CH5 ) );
		SmartDashboard::PutBoolean( "CH7", InterLink->GetRawButton( InterLink_Elite_CH7 ) );
		SmartDashboard::PutBoolean( "RESET", InterLink->GetRawButton( InterLink_Elite_RESET ) );
		if( InterLink->GetRawButton( InterLink_Elite_CH8_BACK ) )
			SmartDashboard::PutNumber( "CH8", -1 );
		else if( InterLink->GetRawButton( InterLink_Elite_CH8_FRONT ) )
			SmartDashboard::PutNumber( "CH8", 1 );
		else
			SmartDashboard::PutNumber( "CH8", 0 );

		// Write axes to SmartDashboard
		SmartDashboard::PutNumber( "AILE", InterLink->GetRawAxis( InterLink_Elite_AILE ) );
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
