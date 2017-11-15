#include "Fahrrad.h"

Fahrrad::Fahrrad()
{
}

Fahrrad::Fahrrad(string name, double MaxSpeed) : Fahrzeug::Fahrzeug(name, MaxSpeed)
{
}

Fahrrad::Fahrrad(string name, double MaxSpeed, FzgVerhalten * verhalten)
{
	this->p_sName = name;
	this->p_dMaxGeschwindigkeit = MaxSpeed;
	this->p_pVerhalten = verhalten;
}

Fahrrad::~Fahrrad()
{
}

double Fahrrad::dGeschwindigkeit()
{
	//the speed decrease 10% per 20 km
	double dSpeed =  p_dMaxGeschwindigkeit *(pow(0.9, p_dGesamtStrecke / 20));
	// the lowest possible speed is 12 km/h
	return (dSpeed <= 12) ? 12 : dSpeed;
}

void Fahrrad::vZeichen(Weg* wegptr)
{
	double dRelPosition = dAbschnittStrecke() / wegptr->dLaengeoutput();
	/*to make sure the dRealPosition is between 0 to 1*/
	if (dRelPosition == 0) dRelPosition += 0.0001;
	else if (dRelPosition > 1) dRelPosition = 1;

	bZeichneFahrrad(p_sName, wegptr->sWegname(), dRelPosition, dGeschwindigkeit());
}

ostream & Fahrrad::ostreamAusgabe(ostream & output)
{
	output << setiosflags(ios::left);
	output << setw(4) << p_iID
		<< setw(7) << p_sName
		<< setw(3) << ":";
	output << showpoint << fixed << setprecision(2);
	output << setw(16) << dGeschwindigkeit()
		<< setw(18) << p_dGesamtStrecke
		<< setw(14) << p_dAbschnittStrecke
		<< setw(15) << p_dZeit;
	output << resetiosflags(ios::left);

	return output;
}

istream & Fahrrad::istreamEingabe(istream& input)
{
	return Fahrzeug::istreamEingabe(input);
}

ostream & operator<<(ostream& output, Fahrrad & fahrradouput)
{
	return fahrradouput.ostreamAusgabe(output);
}

istream & operator >> (istream& input, Fahrrad& fahrradinput)
{
	return fahrradinput.istreamEingabe(input);
}
