#include "Losfahren.h"

Losfahren::Losfahren(Fahrzeug*fahrzeugptr , Weg* wegptr): FahrAusnahme::FahrAusnahme(fahrzeugptr,wegptr)
{
}

Losfahren::~Losfahren()
{
}

void Losfahren::vBearbeiten()
{
	cout << "FahrAusnahme: Losfahren: Reach to the Startzeitpunkt" << endl;

	wegptr->vAbgabe(fahrzeugptr);
	wegptr->vAnnahme(fahrzeugptr);
}
