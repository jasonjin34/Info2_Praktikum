#pragma once
#include "FahrAusnahme.h"

class Fahrzeug;
class Weg;

class Losfahren :
	public FahrAusnahme
{
public:
	Losfahren(Fahrzeug*, Weg*);

	virtual ~Losfahren();

	virtual void vBearbeiten();
};

