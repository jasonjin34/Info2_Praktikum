#pragma once
#include "AktivesVO.h"
#include "Fahrzeug.h"
#include "LazyListe.h"
#include "LazyAktion.h"
#include <list>

class Fahrzeug;
class Kreuzung;

using namespace std;

extern double dGlobaleZeit;

class Weg : public AktivesVO
{
public:
	//Aufzählung data type
	enum Begrezung
	{
		Innerorts = 50,
		Landstrasse = 100,
		Unbegrenzt
	};

	Weg();
	// konstructor with name
	Weg(string);

	Weg(string, double);

	Weg(string, double, Weg::Begrezung);

	Weg(string, double, Weg::Begrezung, bool, Kreuzung*);

	Weg(string, double, Weg::Begrezung, bool);

	virtual ~Weg();

	/*abfertigung function*/
	virtual void vAbfertigung();
	
	/*output function*/
	virtual void vAusgabe();

	virtual void vInitialiserung();	

	/*ostreamAusgabe function*/
	ostream& ostreamAusgabe(ostream& output);
	 
	//output for weg p_dLaenge 
	double dLaengeoutput();

	// Fahrzeug aufnehmen function
	virtual void vAnnahme(Fahrzeug*);

	virtual void vAnnahme(Fahrzeug*, double);

	// Fahhrzeug entfern function
	virtual void vAbgabe(Fahrzeug*);

	// output function for eLimit
	virtual Weg::Begrezung eLimitoutput();

	string sWegname();

	//test if the lazylist is empty
	bool bListempty();

	//get boolesche Member-Variable 
	bool bGetuberholverbot();

	//getter function for virtuelle schranke 
	void vSetdVschranke(double);

	//get virtualle schranke value 
	double dGetVschranke();

	//setting ruckweg function
	void vSetRuckweg(Weg* );

	//get ruckweg function
	Weg* pGetRuckweg();

	void vSetkreuzung(Kreuzung*);

	Kreuzung* pGetKreuzung();	

	void vZeichen();

	LazyListe<Fahrzeug*> lGetLazyliste();

protected:
	double p_dLaenge;

	LazyListe<Fahrzeug*> p_lfahrzeuglist;

	Begrezung p_eLimit;

	double p_dAbschnittStrecke;

	bool p_bUeberholverbot;

	//setting virtuelle Schranke member varialbe 
	double p_dVschranke;

	//ruckweg member variable
	Weg* p_pRuckweg;

	Kreuzung* p_pKreuzung;
};

ostream& operator<<(ostream& output, Weg& weg);