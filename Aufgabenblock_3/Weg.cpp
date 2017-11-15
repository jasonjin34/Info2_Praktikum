#include "Weg.h"

Weg::Weg()
{
	vInitialiserung();
}

Weg::Weg(string name)
{
	this->p_sName = name;
}

Weg::Weg(string name, double distance)
{
	this->p_sName = name;
	this->p_dLaenge = distance;
}

Weg::Weg(string name, double distance, Weg::Begrezung speed)
{
	this->p_sName = name;
	this->p_dLaenge = distance;
	this->p_eLimit = speed;
}

Weg::Weg(string name, double distance, Weg::Begrezung speed, bool uberholtverbot, Kreuzung* kreuzungptr)
{
	this->p_sName = name;
	this->p_dLaenge = distance;
	this->p_eLimit = speed;
	this->p_bUeberholverbot = uberholtverbot;
	this->p_pKreuzung = kreuzungptr;
}

Weg::Weg(string name, double distance, Weg::Begrezung speed, bool uberholtverbot)
{
	this->p_sName = name;
	this->p_dLaenge = distance;
	this->p_eLimit = speed;
	this->p_bUeberholverbot = uberholtverbot;
}

Weg::~Weg()
{
	p_lfahrzeuglist.clear();
}

void Weg::vAbfertigung()
{
	AktivesVO::vAbfertigung();

	//fahrzeug abferitung
	list<Fahrzeug*>::iterator it = p_lfahrzeuglist.begin();
	do
	{
		if (p_lfahrzeuglist.empty()) break;
		(*it)->vAbfertigung();
		cout << **it << endl;
		it++;
	} while (it != p_lfahrzeuglist.end());

	p_lfahrzeuglist.vAktualisieren();
	p_dVschranke = p_dLaenge;
 }

void Weg::vAusgabe()
{
	AktivesVO::vAusgabe();
	cout << setprecision(2) << fixed
   		 << setw(10) << p_dZeit;
}

void Weg::vInitialiserung()
{
	p_dLaenge = 0;
	p_eLimit = Unbegrenzt;
	p_bUeberholverbot = true; // default member variable value 
}

ostream & Weg::ostreamAusgabe(ostream & output)
{
	output << setiosflags(ios::right) << setw(4) << p_iID
		   << setw(10) << p_sName
		   << setw(10) << p_dLaenge;
	output << " (";

	if (!p_lfahrzeuglist.empty())
	{
		list<Fahrzeug*>::iterator it;
		for (it = p_lfahrzeuglist.begin(); it != p_lfahrzeuglist.end(); it++)
		{
			output << (**it).sName() << " ";
		}
		output << ")";
	}
	else
	{
		output << "List is empty)";
	}
	return output;
}


double Weg::dLaengeoutput()
{
	return p_dLaenge;
}

void Weg::vAnnahme(Fahrzeug* inputfahrzeug)
{
	inputfahrzeug->vNeueStrecke(this);

	p_lfahrzeuglist.push_back(inputfahrzeug);
}

void Weg::vAnnahme(Fahrzeug * fahrzeugptr, double zeit)
{
	fahrzeugptr->vNeueStrecke(this, zeit);
	p_lfahrzeuglist.push_back(fahrzeugptr);
}

void Weg::vAbgabe(Fahrzeug* Fahrzeugptr)
{
	// initiatlisation it as iterator of list<Fahrzeug*>
	list<Fahrzeug*>::iterator it;
	for (it = p_lfahrzeuglist.begin(); it != p_lfahrzeuglist.end(); it++)
	{
		if (*it == Fahrzeugptr)
		{
			p_lfahrzeuglist.erase(it);
		}
	}
}

Weg::Begrezung Weg::eLimitoutput()
{
	return p_eLimit;
}

string Weg::sWegname()
{
	return this->p_sName;
}

bool Weg::bListempty()
{
	return p_lfahrzeuglist.empty();
}

bool Weg::bGetuberholverbot()
{
	return this->p_bUeberholverbot;
}

void Weg::vSetdVschranke(double virtuelle_schranke)
{
	this->p_dVschranke = virtuelle_schranke;
}

double Weg::dGetVschranke()
{
	return this->p_dVschranke;
}

void Weg::vSetRuckweg(Weg* street)
{
	this->p_pRuckweg = street;
}

Weg * Weg::pGetRuckweg()
{
	return p_pRuckweg;
}

void Weg::vSetkreuzung(Kreuzung* kreuzungptr)
{
	this->p_pKreuzung = kreuzungptr;
}

Kreuzung * Weg::pGetKreuzung()
{
	return this->p_pKreuzung;
}

void Weg::vZeichen()
{
	list<Fahrzeug*>::iterator it = p_lfahrzeuglist.begin();
	while (it != p_lfahrzeuglist.end())
	{
		(*it)->vZeichen(this);
		cout << *(*it) << endl;
		it++;
	}
}

LazyListe<Fahrzeug*> Weg::lGetLazyliste()
{
	return p_lfahrzeuglist;
}

ostream & operator<<(ostream & output, Weg & weg1)
{
	return weg1.ostreamAusgabe(output);
}
