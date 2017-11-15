#pragma once
#include "AktivesVO.h"
#include "Fahrzeug.h"
#include "Weg.h"

class Kreuzung;
class Fahrzeug;
class Weg;

class FahrAusnahme
{
public:
	/*constructor and destructor*/
	FahrAusnahme();
	FahrAusnahme(Fahrzeug*, Weg*);
	virtual ~FahrAusnahme();

	/*rein virtual function*/
	virtual void vBearbeiten() = 0;


protected:
	Fahrzeug* fahrzeugptr;
	Weg* wegptr;
};

