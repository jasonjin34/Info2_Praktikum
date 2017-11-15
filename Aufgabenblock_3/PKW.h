#pragma once
#include "Fahrzeug.h"
#include "AktivesVO.h"
#include <string>

class PKW :
	public Fahrzeug
{
public:
	PKW();
	/*konstructor with fahrzeug membervariable and also pkw variable */
	// name, maxspeed, verbrauch, tankinhalt, tankvolume
	PKW(string,double, double, double,double);

	/*konstructor with default under class member*/
	PKW(string, double);

	PKW(string, double, FzgVerhalten*);
	
	double dVerbruch();

	// set up default argument 0.0
	virtual double dTanken(double dMenge = 0.0); 

	// complete the vAbfertigung function
	virtual void vAbfertigung();

	// extend the vAusgabe function from Fahrzeug
	virtual void vAusgabe();

	virtual ~PKW();

	double dGeschwindigkeit();
	
	virtual void vZeichen(Weg*);

	double dTankoutput();

	ostream& ostreamAusgabe(ostream&);

	istream& istreamEingabe(istream&);

private:
	double p_dVerbrach;
	double p_dTankinhalt;
	double p_dTankvolume;
};

ostream& operator<<(ostream&, PKW&);

istream& operator >> (istream&, PKW&);