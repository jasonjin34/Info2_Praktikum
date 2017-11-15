#pragma once
#include <list>
#include "LazyListe.h"
#include "AktivesVO.h"
#include "Weg.h"

class Fahrzeug;
class Weg;

class Kreuzung : public AktivesVO
{
public:
	/*contructors and destructors*/
	Kreuzung();
	Kreuzung(string); //param name
	Kreuzung(double, string); // param name, Tankstelleinhalt
	Kreuzung(double);// param Tankstelleinhalt
	virtual ~Kreuzung();

	/*vAnnahme function for parkenden fahrzeug*/
	void vAnnahme(Fahrzeug*, double); // parma double zeit
	
    /*vAnnahme function for fahrende fahrzeug*/
	void vAnnahme(Fahrzeug*);

	void vTanken(Fahrzeug* );

	void vAbfertigung();

	/*generate two new Weg with same length and same type and Ziel Kreuzung*/
	void vVerbinde(string, string, double,Weg::Begrezung,bool,Kreuzung*);

	/*generate random Weg option for the fahrzeug*/
	Weg* ptZufaelligerWeg(Weg*);

	/*get Kreuzung name*/
	string sGetname();

	double dGetTankestelle();

	/*ostreamAusgabe function for ostream overloading*/
	ostream& ostreamAusgabe(ostream&);

	/*istream overloading*/
	istream& istreamEingabe(istream&);

protected:
	list<Weg*> p_pWegelist;

	double p_dTankestelle;
};

ostream& operator<<(ostream&, Kreuzung&);

istream& operator>>(istream&, Kreuzung&);

