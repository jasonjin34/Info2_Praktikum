#pragma once
#include "FzgVerhalten.h"
#include "FahrAusnahme.h"
#include "Streckenende.h"

class Streckenende;
class Weg;

class FzgFahren :
	public FzgVerhalten
{
public:
	/*constructors and destructor*/
	FzgFahren();
	FzgFahren(Weg* );
	virtual ~FzgFahren();

	/*this function get the actual AbschnittStreck*/
	virtual double dStreck(Fahrzeug*, double);
};

