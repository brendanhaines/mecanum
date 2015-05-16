/*
 * InterLinkElite.cpp
 *
 *  Created on: May 16, 2015
 *      Author: user
 */

#include "InterLinkElite.h"

InterLinkElite::InterLinkElite( int port )
{
	stick = new Joystick( port );
}

double InterLinkElite::getAile()
{
	return stick->GetRawAxis( aile ) / (aileTrim[2]-aileTrim[0]);
}

double InterLinkElite::getElev()
{
	return stick->GetRawAxis( elev ) / (elevTrim[2]-elevTrim[0]);
}

double InterLinkElite::getThro()
{
	return stick->GetRawAxis( thro ) / (throTrim[2]-throTrim[0]);
}

double InterLinkElite::getRudd()
{
	return stick->GetRawAxis( rudd ) / (ruddTrim[2]-ruddTrim[0]);
}

double InterLinkElite::getCh5()
{
	if( GetCh5() )
		return 1;
	return -1;
}

double InterLinkElite::getCh6()
{
	return stick->GetRawAxis( ch6 ) / (ch6Trim[2]-ch6Trim[0]);
}

double InterLinkElite::getCh7()
{
	if( GetCh7() )
		return 1;
	return -1;
}

double InterLinkElite::getCh8()
{
	if( GetCh8Front() )
		return 1;
	else if( GetCh8Back() )
		return -1;
	return 0;
}

double InterLinkElite::getReset()
{
	if( GetReset() )
		return 1;
	return -1;
}

bool InterLinkElite::GetReset()
{
	return stick->GetRawButton( reset );
}

bool InterLinkElite::GetCh5()
{
	return stick->GetRawButton( ch5 );
}

bool InterLinkElite::GetCh7()
{
	return stick->GetRawButton( ch7 );
}

bool InterLinkElite::GetCh8Back()
{
	return stick->GetRawButton( ch8b );
}

bool InterLinkElite::GetCh8Front()
{
	return stick->GetRawButton( ch8f );
}

InterLinkElite::~InterLinkElite() {}

