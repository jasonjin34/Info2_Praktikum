#pragma once
//this class indicates the difference of Fahrzeugs Verhalten
//the Fahrzeug's behavior is also based on the Weg class
#include <iostream>
#include "Weg.h"
#include "Fahrzeug.h"

class Fahrzeug;
class Weg;

class FzgVerhalten
{
public:
	/*constructors and destructor*/
	FzgVerhalten();
	FzgVerhalten(Weg* wegptr);
	virtual ~FzgVerhalten();

	/*caculate the driving distance of the Fahrzeug within given period*/
	virtual double dStreck(Fahrzeug*, double) = 0; // double variable  shows the time period

	virtual Weg* pGetWegptr();

	/*get the Weg Max speed limit*/
	virtual double dMaxGeschwindigkeit();
protected:
	Weg* p_pWegptr;
};