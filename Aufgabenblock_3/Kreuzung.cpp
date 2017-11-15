#include "Kreuzung.h"

Kreuzung::Kreuzung()
{
}

Kreuzung::Kreuzung(string name)
{
	this->p_sName = name;
}

Kreuzung::Kreuzung(double Tankstelle, string name): AktivesVO::AktivesVO(name),p_dTankestelle(Tankstelle)
{
}

Kreuzung::Kreuzung(double p_dTankestelle)
{
	this->p_dTankestelle = p_dTankestelle;
}

Kreuzung::~Kreuzung()
{
}

void Kreuzung::vAnnahme(Fahrzeug* fahrzeugptr, double zeit)
{
	//put the fahrzeug in the weg list
	(*p_pWegelist.begin())->vAnnahme(fahrzeugptr,zeit);

	vTanken(fahrzeugptr);
}

void Kreuzung::vAnnahme(Fahrzeug* fahrzeugptr)
{
	(*p_pWegelist.begin())->vAnnahme(fahrzeugptr);

	vTanken(fahrzeugptr);
}

void Kreuzung::vTanken(Fahrzeug* fahrzeugptr)
{
	double dMenge;
	if (p_dTankestelle == 0.0) // Tankestelle empty
	{
		return;
	}
	else
	{
		dMenge = fahrzeugptr->dTanken(0.0);
		(p_dTankestelle - dMenge < 0) ? p_dTankestelle = 0 : p_dTankestelle -= dMenge;
	}
}

void Kreuzung::vAbfertigung()
{
	list<Weg*>::iterator it = p_pWegelist.begin();
	do
	{
		(*it)->vAbfertigung();
		it++;
	} while (it != p_pWegelist.end());

    it = p_pWegelist.begin();
	while (it != p_pWegelist.end())
	{
		(*it)->vZeichen();
		it++;
	}
}


void Kreuzung::vVerbinde(string sNamehin,string sNameruck, double length, Weg::Begrezung begrezung, bool buberholverbot, Kreuzung* kreuzungptr)
{
	// Weg weiß auf welche Kreuzung erführt!! 
	Weg* ruckweg = new Weg(sNameruck, length, begrezung, buberholverbot, kreuzungptr);
	Weg* hinweg = new Weg(sNamehin, length, begrezung, buberholverbot, this);

	//connect two wegs
	ruckweg->vSetRuckweg(hinweg);
	hinweg->vSetRuckweg(ruckweg);

	//add ruckweg and hinweg in the protected member pWeglist
	p_pWegelist.push_back(ruckweg);
	kreuzungptr->p_pWegelist.push_back(hinweg);
}

ostream & Kreuzung::ostreamAusgabe(ostream& output)
{
	output << setiosflags(ios::left);
	output << setw(4) << p_iID
		   << setw(7) << p_sName
		   << setw(3) << ":";
	output << setw(15) << resetiosflags(ios::left) 
		   << "Tankestelle:  " 
		   <<p_dTankestelle;

	return output;
}

istream & Kreuzung::istreamEingabe(istream& input)
{
	AktivesVO::istreamEingabe(input);
	input >> p_dTankestelle;
	return input;
}

Weg* Kreuzung::ptZufaelligerWeg(Weg* wegptr)
{
	if (p_pWegelist.size() == 1) return wegptr->pGetRuckweg();
	while (1)
	{
		int randomnumber;
		randomnumber = rand() % (p_pWegelist.size());

		cout << "randomnumber" << randomnumber << endl;

		list<Weg*>::iterator it = p_pWegelist.begin();
		int counter = 0;
		while(counter != randomnumber)
		{
			counter++;
			it++;
		};
		if (*it == wegptr->pGetRuckweg() || *it == wegptr) continue;
		else return *it;
	}
}

string Kreuzung::sGetname()
{
	return this->p_sName;
}

double Kreuzung::dGetTankestelle()
{
	return this->p_dTankestelle;
}

ostream & operator<<(ostream& output, Kreuzung& kreuzung)
{
	return kreuzung.ostreamAusgabe(output);
}

istream & operator >> (istream & output, Kreuzung & kreuzunginput)
{
	return kreuzunginput.istreamEingabe(output);
}
