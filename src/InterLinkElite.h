/*
 * InterLinkElite.h
 *
 *  Created on: May 16, 2015
 *      Author: user
 */

#ifndef SRC_INTERLINKELITE_H_
#define SRC_INTERLINKELITE_H_

#include "WPIlib.h"

class InterLinkElite {
public:
	InterLinkElite( int port );
	virtual ~InterLinkElite();

	double getAile();
	double getElev();
	double getThro();
	double getRudd();
	double getCh5();
	double getCh6();
	double getCh7();
	double getCh8();
	double getReset();

	bool GetReset();
	bool GetCh5();
	bool GetCh7();
	bool GetCh8Back();
	bool GetCh8Front();

	// trims	{ min, centered, max }
	double aileTrim[3] = { -0.648,	0.016,	0.654 };
	double elevTrim[3] = {	0.606,	0.000, -0.641 };
	double throTrim[3] = {	0.638,	0.018, -0.602 };
	double ch6Trim[3]  = { -1.000,  0.000,  1.000 };
	double ruddTrim[3] = { -0.641,	0.024,	0.732 };
private:
	Joystick *stick;

	// axis mapping
	int aile = 0;
	int elev = 1;
	int thro = 2;
	int ch6 = 3;
	int rudd = 4;

	// button mapping
	int ch5 = 1;
	int ch7 = 2;
	int reset = 3;
	int ch8b = 4;
	int ch8f = 5;
};

#endif /* SRC_INTERLINKELITE_H_ */
