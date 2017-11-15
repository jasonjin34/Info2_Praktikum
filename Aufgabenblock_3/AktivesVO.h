#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <map>

using namespace std; 

extern double dGlobaleZeit;

class AktivesVO
{
public:
	/*constructor and destructor*/
	AktivesVO();
	AktivesVO(string);
	AktivesVO(string, double);
	virtual ~AktivesVO();

	/*rein virtual function for ostream operator overloading*/
	virtual ostream& ostreamAusgabe(ostream& ) = 0;

	/*aktualize function*/
	virtual void vAbfertigung();

	virtual void vAusgabe();

	void vInitialiserung();

	/*operator overloading input function*/
	istream& istreamEingabe(istream&);

   /*static variable and function*/
	static int p_iMaxID;

	static map<string, AktivesVO*> map_VS;
	
	static AktivesVO* ptObject(string);

protected:
	string p_sName;
	int p_iID;
	double p_dZeit;
};

istream& operator >> (istream&, AktivesVO&);
