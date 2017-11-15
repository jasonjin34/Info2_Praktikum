#pragma once
#include <iostream>
#include "AktivesVO.h"
#include "FzgVerhalten.h"
#include "FahrAusnahme.h"
#include "SimuClient.h"

class Losfahren;
class Streckenende;
class FzgVerhalten;
class FzgFahren;
class FzgParken;
class Weg;

using namespace std;

extern double dGlobaleZeit;

class Fahrzeug : public AktivesVO
{
public:
	/*constructors and destructor*/
	Fahrzeug();
	Fahrzeug(string);
	Fahrzeug(string, double); // name, MaxGeschwindigkeit constructor
	Fahrzeug(string, double, double, double, double);
	Fahrzeug(string, double, FzgVerhalten*); //Konstructor initialisation of Fzgverhalten 
	Fahrzeug(const Fahrzeug &obj); //default copy constructor 
	virtual ~Fahrzeug();

	/* iMaxID output, the total number of Fahrzeug class objects*/
	static void MaxIDnumber();

	/*fahrzeug member variable output function*/
	virtual void vAusgabe();
	
	/*aktualiserung member variable*/
	virtual void vAbfertigung();

	/*PKW dTankfunction with default paramenter for fahrrand and fahrzeug without tank will return 0.0*/ 
	virtual double dTanken(double dMenge = 0.0) { return 0.0; };

	/*the virtual speed function*/
	virtual double dGeschwindigkeit();

	/*function to get the Gesamtstreck value*/
	virtual double dGesamtstreckvalue();

	/*function to get name*/
	virtual string sName();

	/*function to get abschnittstrecke*/
	virtual double dAbschnittStrecke();

	/*new street function with street as input varialbe*/ 
	void vNeueStrecke(Weg*);

	/*new street function with Weg pointer and time parameter*/
	void vNeueStrecke(Weg*, double);

	/*get Ausnahme variable*/
	bool bGetboolAusnahme();

	/*draw function*/
	virtual void vZeichen(Weg*);

	/*operator overloading fucntion*/
	/*zuweisungsoperators function (operator overloading)*/
	Fahrzeug& operator = (const Fahrzeug&);

	/*compare function*/
	bool operator < (Fahrzeug&);

	/*ostream overloading function*/
	ostream& ostreamAusgabe(ostream &);

	istream& istreamEingabe(istream &);

protected:
	double p_dMaxGeschwindigkeit;

	double p_dAbschnittStrecke;

	double p_dGesamtStrecke;

	double p_dGesamtZeit;

	FzgVerhalten* p_pVerhalten;

	bool p_bAusnahme;

private:
	// Initialisierungsfunktion, int double variables are reseted to 0, and string variables set ""
	void vInitialisierung();
};

ostream& operator<<(ostream&, Fahrzeug&);

istream& operator >> (istream&, Fahrzeug&);
