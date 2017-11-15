#include "FzgParken.h"

FzgParken::FzgParken()
{
}

FzgParken::FzgParken(double zeitpunkt)
{
	this->dStartzeitPunkt = zeitpunkt;
}

FzgParken::FzgParken(Weg* wegptr, double zeitpunkt)
{
	this->p_pWegptr = wegptr;
	this->dStartzeitPunkt = zeitpunkt;
}

double FzgParken::dStreck(Fahrzeug* fahrzeugptr, double zeitraum)
{
	if (abs(dGlobaleZeit - dStartzeitPunkt) > 0.5) return 0.0;
	else throw Losfahren(fahrzeugptr, p_pWegptr);
}

FzgParken::~FzgParken()
{
}
