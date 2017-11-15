#include "PKW.h"

PKW::PKW()
{	
}

PKW::PKW(string name,double speed, double Verbrauch,double Tankvolume, double Tankinhalt)
	: Fahrzeug(name,speed),p_dVerbrach(Verbrauch),p_dTankvolume(Tankvolume),p_dTankinhalt(Tankinhalt)
{
}

PKW::PKW(string name,double speed) : Fahrzeug(name, speed), p_dTankvolume(55), p_dTankinhalt(55/2),p_dVerbrach(5)
{
}

PKW::PKW(string name, double speed, FzgVerhalten* verhalten)
{
	this->p_sName = name;
	this->p_dMaxGeschwindigkeit = speed;
	this->p_pVerhalten = verhalten;
}

PKW::~PKW()
{
	p_iMaxID--;
}

double PKW::dGeschwindigkeit()
{
	double Maxwegspeed = p_pVerhalten->dMaxGeschwindigkeit();
	
	if (Maxwegspeed == 50) return (p_dMaxGeschwindigkeit > Maxwegspeed) ? Maxwegspeed:p_dMaxGeschwindigkeit;
	else if (Maxwegspeed == 100) return (p_dMaxGeschwindigkeit > Maxwegspeed) ? Maxwegspeed : p_dMaxGeschwindigkeit;
	else 
	{
		return (p_dMaxGeschwindigkeit > 101) ? p_dMaxGeschwindigkeit:101;
	}
}

void PKW::vZeichen(Weg* wegptr)
{
	double dRelPosition = dAbschnittStrecke() / (wegptr->dLaengeoutput());
	/*to make sure the dRealPosition is between 0 to 1*/
	if (dRelPosition == 0) dRelPosition += 0.0001;
	else if (dRelPosition > 1) dRelPosition = 1;

	bZeichnePKW(p_sName,wegptr->sWegname(),dRelPosition,dGeschwindigkeit(),dTankoutput());
}

double PKW::dTankoutput()
{
	return this->p_dTankinhalt;
}

ostream & PKW::ostreamAusgabe(ostream& output)
{
	Fahrzeug::ostreamAusgabe(output);
	output << setw(15) << p_dTankinhalt;
	return output;
}

istream & PKW::istreamEingabe(istream & input)
{
	Fahrzeug::istreamEingabe(input);
	input >> p_dVerbrach;
	input >> p_dTankvolume;
	p_dTankinhalt = p_dTankvolume / 2;
	return input;
}

/* function dVerbrauch, show the total use of the gas*/
double PKW::dVerbruch()
{
	return p_dMaxGeschwindigkeit* p_dVerbrach / 100; // the p_dVerbrauch is Verbrauch / 100 km states in the aufgabe skript 
}

double PKW::dTanken(double dMenge)
{
	if (dMenge == 0.0 || dMenge >= p_dTankvolume - p_dTankinhalt)
	{
		dMenge = p_dTankvolume - p_dTankinhalt;
		p_dTankinhalt = p_dTankvolume;
		return dMenge;
	}
	else
	{
		p_dTankinhalt += dMenge;
		return dMenge;
	}
}

void PKW::vAbfertigung()
{
	if (p_dTankinhalt == 0)
	{
		cout << p_sName << " out of gas" << endl;
		return;
	}

	p_bAusnahme = false;
	double dDistance = 0;

	if (dGlobaleZeit != p_dZeit)
	{
		//dDistance need to be used with being initialized, otherweise if throw was not execute
		//it will cause complier failer 
		double dZeitraum = dGlobaleZeit - p_dZeit;
		p_dGesamtZeit += dZeitraum;
		p_dZeit = dGlobaleZeit;

		try
		{
			dDistance = p_pVerhalten->dStreck(this, dZeitraum);// dStreck function can only be executed once
		}
		catch (FahrAusnahme& e)
		{
			e.vBearbeiten();
			p_bAusnahme = true; // indicates that Fahrzeug expections occurs 
		};

		p_dGesamtStrecke = dDistance + p_dGesamtStrecke;
		p_dAbschnittStrecke = dDistance + p_dAbschnittStrecke;
	}

	double dDeltatankinhalt = p_dTankinhalt -dDistance*dVerbruch()/100;
	// tankinhalt can only be positive
	p_dTankinhalt = (dDeltatankinhalt >= 0) ? dDeltatankinhalt:0;
}

void PKW::vAusgabe()
{
	Fahrzeug::vAusgabe();
	cout << setiosflags(ios::left);
	cout << showpoint << fixed << setprecision(2);
	cout << setw(15) << p_dTankinhalt;
}	

ostream & operator<<(ostream& output, PKW& pkwinput)
{
	return pkwinput.ostreamAusgabe(output);
}

istream & operator >> (istream& input, PKW& pkwinput)
{
	return pkwinput.istreamEingabe(input);
}
