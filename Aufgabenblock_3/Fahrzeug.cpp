#include "Fahrzeug.h"
#include "FzgFahren.h"
#include "FzgParken.h"

using namespace std;

// default Konstructor 
Fahrzeug::Fahrzeug()
{
	vInitialisierung();
}

void Fahrzeug::vInitialisierung()
{
	this->p_dGesamtStrecke = 0;
	this->p_dGesamtZeit = 0;
	this->p_dMaxGeschwindigkeit = 0;
	this->p_dAbschnittStrecke = 0;
	this->p_pVerhalten = NULL;
}

// Konstructor, only name
Fahrzeug::Fahrzeug(string name)
{
	this->p_sName = name;
}
// Konstructor, name and maximale speed
Fahrzeug::Fahrzeug(string name, double Maxspeed)
{
	this->p_sName = name;
	this->p_dMaxGeschwindigkeit = Maxspeed;
}

// Konstructor Name,Geschwindigkeit, gesamtstrecke, gesamtzeit, zeit
Fahrzeug::Fahrzeug(string name, double speed, double totaldistance, double totaltime, double time)
{
	this->p_sName = name;
	this->p_iID = ++p_iMaxID;
	this->p_dMaxGeschwindigkeit = speed;
	this->p_dGesamtStrecke = totaldistance;
	this->p_dGesamtZeit = totaltime;
	this->p_dZeit = time;
}

Fahrzeug::Fahrzeug(string name, double speed, FzgVerhalten* verhalteninput)
{
	this->p_sName = name;
	this->p_dMaxGeschwindigkeit = speed;
	this->p_pVerhalten = verhalteninput;
}

// Static ID number print out
void Fahrzeug::MaxIDnumber()
{
	cout << "the number of class Fahrzeug objects:\t" << p_iMaxID << endl;
}

// Destructor 
Fahrzeug::~Fahrzeug()
{
	p_iMaxID--;
	delete p_pVerhalten;
}

void Fahrzeug::vAusgabe()
{
	AktivesVO::vAusgabe();
	// use setiosflags to active the leftside 
	cout << setw(3) << ":";
	cout << showpoint << fixed << setprecision(2);
	cout << setw(16) << dGeschwindigkeit()
		 << setw(15) << p_dAbschnittStrecke
		 << setw(18) << p_dGesamtStrecke
		 << setw(14) << p_dGesamtZeit
		 << setw(15) << p_dZeit;
	cout << resetiosflags(ios::left);
}

//define the ostreamAusgabe function, create a ostream reference object
//all the member variables are available

ostream& Fahrzeug::ostreamAusgabe(ostream& output)
{
	output << setiosflags(ios::left);
	output << setw(4) << p_iID
		   << setw(7) << p_sName
		   << setw(3) << ":";
	output << showpoint << fixed << setprecision(2);
	output << setw(16) << p_dMaxGeschwindigkeit
		<< setw(18) << p_dGesamtStrecke
		<< setw(14) << p_dAbschnittStrecke
		<< setw(15) << p_dZeit;
	output << resetiosflags(ios::left);

	return output;
}

istream & Fahrzeug::istreamEingabe(istream& input)
{
	AktivesVO::istreamEingabe(input);
	input >> p_dMaxGeschwindigkeit;
	return input;
}

/*compare the total distance*/
bool Fahrzeug::operator<(Fahrzeug& fahrzeug1)
{
	return (p_dGesamtStrecke < fahrzeug1.dGesamtstreckvalue()) ? true : false;
}

double Fahrzeug::dGesamtstreckvalue()
{
	return p_dGesamtStrecke;
}

string Fahrzeug::sName()
{
	return p_sName;
}

double Fahrzeug::dAbschnittStrecke()
{
	return p_dAbschnittStrecke;
}

Fahrzeug & Fahrzeug::operator=(const Fahrzeug & input)
{
	p_sName = input.p_sName;
	p_dMaxGeschwindigkeit = input.p_dMaxGeschwindigkeit;
	p_dGesamtStrecke = input.p_dGesamtStrecke;
	p_dGesamtZeit = input.p_dGesamtZeit;
	p_dZeit = input.p_dZeit;

	p_iID = ++p_iMaxID; // avoid the doule id

	// this Fahrzeug object can be accessed by using this pointer 
	// therefore, we need to dereference this pointer to get the object
	return *this;
}

/*add Fzgverhalten to Fahrzeug member variable*/
void Fahrzeug::vNeueStrecke(Weg* wegptr)
{
	p_pVerhalten = new FzgFahren(wegptr);

	// redefine the p_dAbeschnittStrecke 
	p_dAbschnittStrecke = 0.0;
}
/* function overloading*/
/* the double variable zeit is Startzeitpunkt*/
void Fahrzeug::vNeueStrecke(Weg* wegptr, double zeit)
{
	p_pVerhalten = new FzgParken(wegptr, zeit);
	p_dAbschnittStrecke = 0.0;
}

bool Fahrzeug::bGetboolAusnahme()
{
	return this->p_bAusnahme;
}

void Fahrzeug::vZeichen(Weg* wegptr)
{
	double dRelposition = dAbschnittStrecke() / wegptr->dLaengeoutput();
	/*to make sure the dRealPosition is between 0 to 1*/
	if (dRelposition == 0) dRelposition += 0.0001;
	else if (dRelposition > 1) dRelposition = 1;

	bZeichneFahrrad(p_sName, wegptr->sWegname(), dRelposition, dGeschwindigkeit());
}

/*the default the copy constructor*/
Fahrzeug::Fahrzeug(const Fahrzeug & obj)
	:p_dGesamtStrecke(obj.p_dGesamtStrecke), p_dGesamtZeit(obj.p_dGesamtZeit),
	 p_dMaxGeschwindigkeit(obj.p_dMaxGeschwindigkeit)
{
	 p_dZeit = obj.p_dZeit;
	 p_sName = obj.p_sName;
	 p_iID = ++p_iMaxID;
}

// Abfertigung member function to update the actual data
void Fahrzeug::vAbfertigung()
{
	p_bAusnahme = false;

	if (dGlobaleZeit != p_dZeit)
	{
		//dDistance need to be used with being initialized, otherweise if throw was not execute
		//it will cause complier failer 
		double dDistance = 0;
		double dZeitraum = dGlobaleZeit - p_dZeit;
		p_dGesamtZeit += dZeitraum;
		p_dZeit = dGlobaleZeit;

		try
		{
			 dDistance = p_pVerhalten->dStreck(this,dZeitraum);// dStreck function can only be executed once
		}
		catch (FahrAusnahme& e) 
		{
			e.vBearbeiten(); 
			p_bAusnahme = true; // indicates that Fahrzeug expections occurs 
		};

		p_dGesamtStrecke = dDistance + p_dGesamtStrecke;
		p_dAbschnittStrecke = dDistance + p_dAbschnittStrecke;
	}
}

double Fahrzeug::dGeschwindigkeit()
{
	return p_dMaxGeschwindigkeit;
}


ostream& operator<< (ostream& output, Fahrzeug& fahrzeug1)
{
	return fahrzeug1.ostreamAusgabe(output) ;
}
istream & operator >> (istream& input, Fahrzeug & fahrzeuginput)
{
	return fahrzeuginput.istreamEingabe(input);
}
// overloading the stream insertion operator, compiler generate the cout << Fahrzeug; as 
// operator << (iostream& , Fahrzeug&), lhs is iostream reference, and rhs is Fahrzeug reference
// when this call execute, reference parameter, here is output, will be an alias for cout(like die übergebenden Variable)
// return ostream& ensure that the cout << Fahrzeug1 << Fahrzeug2 << endl; can be execuated.