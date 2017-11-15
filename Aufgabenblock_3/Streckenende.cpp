#include "Streckenende.h"

Streckenende::Streckenende(Fahrzeug* fahrzeugptr, Weg* wegptr): FahrAusnahme::FahrAusnahme(fahrzeugptr,wegptr)
{
}

Streckenende::~Streckenende()
{
}
void Streckenende::vBearbeiten()
{
	Kreuzung* Kreuzungptr = wegptr->pGetKreuzung();
	if (wegptr->pGetKreuzung() == nullptr)
	{
		cout << "end of the street, there is not back street or the other street" << endl;
		return;
	}
	wegptr->vAbgabe(fahrzeugptr);
	//find new weg
	Weg* newWegptr = Kreuzungptr->ptZufaelligerWeg(wegptr);

	//reset the fahrzeug into the new weg
	newWegptr->vAnnahme(fahrzeugptr);

	//Tank fahrzeug
	Kreuzungptr->vTanken(fahrzeugptr);

	cout << "FahrAusnahme : Streckende" << endl;
	cout << setiosflags(ios::left) << setw(10) << "Zeit" << setw(2) << " : " << dGlobaleZeit << endl
		<< setw(10) << "KREUZUNG" << setw(2) << " : " << Kreuzungptr->sGetname() << "Tankstelle inhalt: " << Kreuzungptr->dGetTankestelle() << endl
		<< setw(10) << "WECHSEL" << setw(2) << " : " << wegptr->sWegname() << "->" << newWegptr->sWegname() << endl
		<< setw(10) << "FAHRZEUG" << setw(2) << " : " << *fahrzeugptr << endl;
	cout << resetiosflags(ios::left);

	cout << setiosflags(ios::left);
	cout << setw(4) << "ID" << setw(7) << "Name"
		<< setw(3) << ":" << setw(13) << "Kmh"
		<< setw(17) << "GesamtStrecke"
		<< setw(13) << "AbschnittS"
		<< setw(15) << "GesamtZeit"
		<< setw(15) << "Zeit"
		<< setw(15) << "Tankinhalt"
		<< endl;
	cout << resetiosflags(ios::left);
}
