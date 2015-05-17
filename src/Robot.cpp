#include "WPILib.h"
#include "InterLinkElite.h"

#define PI 3.141592653589793238462643383279

///// USER PARAMETERS /////

// Tuning Parameters
#define throScale	1
#define ruddScale   1

// Wiring Parameters
#define frontLeftChannel	4
#define backLeftChannel		3
#define frontRightChannel	1
#define backRightChannel	2

// adjust sign so that (+)*speed results in bot turning clockwise
#define frontLeftSpeed	1.0
#define backLeftSpeed	1.0
#define frontRightSpeed	1.0
#define backRightSpeed	1.0

const double frontLeftAngle = PI/4;
const double backLeftAngle = 3*PI/4;
const double frontRightAngle = -PI/4;
const double backRightAngle = -3*PI/4;

#define InterLink_ID			0

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
	InterLinkElite *InterLink;

public:

	////////////////////////////////
	///// ROBOT INITIALIZATION /////
	////////////////////////////////

	void RobotInit()
	{
		frontLeft = new Talon( frontLeftChannel );
		backLeft = new Talon( backLeftChannel );
		frontRight = new Talon( frontRightChannel );
		backRight = new Talon( backRightChannel );

		InterLink = new InterLinkElite( InterLink_ID );
		ds = DriverStation::GetInstance();
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
		double aile = InterLink->getAile();
		double elev = InterLink->getElev();
		double rudd = InterLink->getRudd();
		SmartDashboard::PutNumber( "Rudder", rudd );

		double driveAngle = atan2( -aile, elev );
		SmartDashboard::PutNumber( "Drive Angle", driveAngle );

		double driveSpeed = sqrt( aile*aile + elev*elev );
		SmartDashboard::PutNumber( "Drive Speed", driveSpeed );

		frontLeft->Set( (float)(
				throScale * frontLeftSpeed * ( driveSpeed * sin( frontLeftAngle-driveAngle ) + ruddScale * rudd )
				) );
		backLeft->Set( (float)(
				throScale * backLeftSpeed * ( driveSpeed * sin( backLeftAngle-driveAngle ) + ruddScale * rudd )
				) );
		frontRight->Set( (float)(
				throScale * frontRightSpeed * ( driveSpeed * sin( frontRightAngle-driveAngle ) + ruddScale * rudd )
				) );
		backRight->Set( (float)(
				throScale * backRightSpeed * ( driveSpeed * sin( backRightAngle-driveAngle ) + ruddScale * rudd )
				) );
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
