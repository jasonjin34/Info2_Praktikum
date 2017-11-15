#include "AktivesVO.h"


AktivesVO::AktivesVO()
{
	vInitialiserung(); 
}

AktivesVO::AktivesVO(string name)
{
	vInitialiserung();
	this->p_sName = name;
}

AktivesVO::AktivesVO(string name, double time)
{
	vInitialiserung();
	this->p_sName = name;
	this->p_dZeit = time;
}


AktivesVO::~AktivesVO()
{
}

void AktivesVO::vAbfertigung()
{
	if (p_dZeit != dGlobaleZeit) p_dZeit = dGlobaleZeit;
}

void AktivesVO::vAusgabe()
{
	cout << setiosflags(ios::left);
	cout << setw(4) << p_iID
	     << setw(7) << p_sName;
}

void AktivesVO::vInitialiserung()
{
	p_sName = "";
	p_iID = ++p_iMaxID;
	p_dZeit = 0.0;
}

istream & AktivesVO::istreamEingabe(istream& input)
{
	string sFehler = " Name Input Fehlerfall";

	if (p_sName == "")
	{
		input >> p_sName;
	}
	else throw (sFehler);

	return input;
}

AktivesVO* AktivesVO::ptObject(string name)
{
	
	if (map_VS.find(name) == map_VS.end())
	{
		throw string("Error aktivesVO: " + name + " not exist");
	}
	else
	{
		return  map_VS.find(name)->second;
	}
}

ostream&  AktivesVO::ostreamAusgabe(ostream& output)
{
	output << setiosflags(ios::left);
	output << setw(4) << p_iID
		<< setw(7) << p_sName
		<< setw(3) << ":";
	return output;
}

istream & operator >> (istream& input, AktivesVO& aktivesvoinput)
{
	return aktivesvoinput.istreamEingabe(input);
}

ostream & operator<<(ostream& output, AktivesVO & aktivesVOobject)
{
	return aktivesVOobject.ostreamAusgabe(output);
}
