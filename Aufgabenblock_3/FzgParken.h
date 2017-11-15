#pragma once
#include "FzgVerhalten.h"
#include <cmath>
#include "FahrAusnahme.h"
#include "Losfahren.h"

class Losfahren;
class Weg;

class FzgParken :
	public FzgVerhalten
{
public:
	/*constructors and destructor*/
	FzgParken();
	FzgParken(double);
	FzgParken(Weg*, double);// constructor with Wegptr as input
	virtual ~FzgParken();

	virtual double dStreck(Fahrzeug*, double); 
private:
	double dStartzeitPunkt;
};

