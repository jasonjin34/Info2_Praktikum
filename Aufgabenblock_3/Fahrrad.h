#pragma once
#include "Fahrzeug.h"
#include <math.h>

class Fahrrad :
	public Fahrzeug
{
public:
	/*constructors and destructor*/
	Fahrrad();
	Fahrrad(string name, double MaxSpeed);
	Fahrrad(string name, double MaxSpeed, FzgVerhalten* verhalten);
	virtual ~Fahrrad();

	/*the speed function for bike*/
	virtual double dGeschwindigkeit();

	virtual void vZeichen(Weg*);

	ostream& ostreamAusgabe(ostream& output);
	istream& istreamEingabe(istream &);
};
ostream& operator<<(ostream&, Fahrrad&);

istream& operator  >> (istream&, Fahrrad&);