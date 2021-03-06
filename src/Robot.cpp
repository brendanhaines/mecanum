#include "WPILib.h"
#include "InterLinkElite.h"

#define PI 3.141592653589793238462643383279

///// USER PARAMETERS /////

// Tuning Parameters
double throScale =	1;
#define ruddScale   1
#define aileScale	1
#define elevScale	1

// Wiring Parameters
#define frontLeftChannel	3
#define backLeftChannel		2
#define frontRightChannel	1
#define backRightChannel	0

// adjust sign so that (+)*speed results in bot turning clockwise
#define frontLeftSpeed	1.0
#define backLeftSpeed	1.0
#define frontRightSpeed	1.0
#define backRightSpeed	1.0

const double frontLeftAngle = PI/4;
const double backLeftAngle = 3*PI/4;
const double frontRightAngle = -PI/4;
const double backRightAngle = -3*PI/4;

#define Master_InterLink_ID			0
#define Slave_InterLink_ID			1

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
	InterLinkElite *MasterInterLink;
	InterLinkElite *SlaveInterLink;
	InterLinkElite *ActiveInterLink;

	// Driver Station Selections
	SendableChooser *BuddyBoxEnableChooser;
	SendableChooser *SlaveSpeedControlChooser;

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

		MasterInterLink = new InterLinkElite( Master_InterLink_ID );
		SlaveInterLink = new InterLinkElite( Slave_InterLink_ID );
		ds = DriverStation::GetInstance();
		lw = LiveWindow::GetInstance();

		BuddyBoxEnableChooser = new SendableChooser();
		BuddyBoxEnableChooser->AddDefault( "Buddy Box Disabled", (void*) false );
		BuddyBoxEnableChooser->AddObject( "Buddy Box Enabled", (void*) true );
		SmartDashboard::PutData( "BuddyBoxEnableChooser", BuddyBoxEnableChooser );

		SlaveSpeedControlChooser = new SendableChooser();
		SlaveSpeedControlChooser->AddDefault( "Trainer Controls Speed", (void*) false );
		SlaveSpeedControlChooser->AddObject( "Slave Controls Speed", (void*) true );
		SmartDashboard::PutData( "SlaveSpeedControlChooser", SlaveSpeedControlChooser );
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
		double throttle;

		bool BuddyBoxEnabled = BuddyBoxEnableChooser->GetSelected();
		bool SlaveInControl = MasterInterLink->GetCh5();
		SmartDashboard::PutBoolean( "Slave In Control", BuddyBoxEnabled ? SlaveInControl : false );
		bool SlaveControlsSpeed = SlaveSpeedControlChooser->GetSelected();

		if( BuddyBoxEnabled && SlaveInControl ) ActiveInterLink = SlaveInterLink;
		else ActiveInterLink = MasterInterLink;

		if( SlaveInControl && SlaveControlsSpeed ) throttle = SlaveInterLink->getCh6();
		else throttle = MasterInterLink->getCh6();

		double aile = ActiveInterLink->getAile();
		double elev = ActiveInterLink->getElev();
		double rudd = ActiveInterLink->getRudd();
		SmartDashboard::PutNumber( "Rudder", rudd );
		SmartDashboard::PutNumber( "Throttle", throttle );

		throScale = throttle + 1;

		double driveAngle = atan2( -aile*aileScale, elev*elevScale );
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

	void TestInit()
	{}

	void TestPeriodic()
	{
		lw->Run();
	}

	////////////////////
	///// DISABLED /////
	////////////////////

	void DisabledInit()
	{}

	void DisabledPeriodic()
	{}
};

START_ROBOT_CLASS(Robot);
