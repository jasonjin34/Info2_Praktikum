#pragma once
#include "FahrAusnahme.h"
#include "Kreuzung.h"
class Weg;
class Fahrzeug;
class Kreuzung;

class Streckenende :
	public FahrAusnahme
{
public:
	Streckenende(Fahrzeug*, Weg*);

	virtual ~Streckenende();

	virtual void vBearbeiten();

};

