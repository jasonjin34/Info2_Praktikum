#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <map>

#include "Fahrzeug.h"
#include "AktivesVO.h"
#include "FzgVerhalten.h"
#include "FzgFahren.h"
#include "FzgParken.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "LazyAktion.h"
#include "LazyListe.h"
#include "SimuClient.h"
#include "Kreuzung.h"
#include "Welt.h"

class Welt;
class Weg;
class PKW;
class FzgFahren;
class Kreuzung;

using namespace std;
//initialisation the statisch variable 
int AktivesVO::p_iMaxID = 0;

//static member variable bekannt machen 
map<string, AktivesVO*> AktivesVO::map_VS;

// global time definition 
double dGlobaleZeit = 0.0;

// output format function

void vHeadformat()
{
	cout << setiosflags(ios::left);
	cout << setw(4) << "ID" << setw(7) << "Name"
		<< setw(3) << ":" << setw(13) << "Kmh"
		<< setw(17) << "GesamtStrecke"
		<< setw(13) << "AbschnittS"
		<< setw(15) << "GesamtZeit"
		<< setw(15) << "Zeit"
		<< setw(15) << "Tankinhalt"
		<< endl;
	cout << resetiosflags(ios::left);
}

void vAufgabe_7()
{
	bInitialisiereGrafik(1000, 1000);

	Weg street1 = Weg("street1", 300, Weg::Innerorts, true);
	Weg street2 = Weg("street2", 300, Weg::Innerorts, true);
	//set up uberholtverbot for street1

	Fahrrad* fBike = new Fahrrad("bike", 15);
	PKW car1 = PKW("car1", 40);
	street1.vAnnahme(fBike);
	street1.vAnnahme(&car1,5);

	int aAnzahlkoordinaten[]= {700, 250, 100, 250};
	bZeichneStrasse("street1", "street2", 200, 2, aAnzahlkoordinaten);

	dGlobaleZeit = 0;
	while (dGlobaleZeit < 20)
	{
		vSetzeZeit(dGlobaleZeit);

		street1.vAbfertigung();
		street1.vZeichen();

		dGlobaleZeit += 0.5;
		vSleep(200);
	}	
	vBeendeGrafik();
}

void vAufgabe_8() 
{
	bInitialisiereGrafik(2000, 1500);

	Kreuzung* kr1 = new Kreuzung("KR1");
	Kreuzung* kr2 = new Kreuzung(1000,"KR2");
	Kreuzung* kr3 = new Kreuzung("KR3");
	Kreuzung* kr4 = new Kreuzung("KR4");

	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);
	/*set street koordinate*/

	int StrasseKorrdinaten1[] = { 680, 300, 680, 40 };
	int StrasseKorrdinaten2[] = { 680, 570, 850, 570, 970, 500, 970, 390, 850, 300, 680, 300 };
	int StrasseKorrdinaten3[] = { 680, 570, 680, 300 };
	int StrasseKorrdinaten4[] = { 320, 300, 680, 300 };
	int StrasseKorrdinaten5[] = { 320, 300, 320, 420, 350, 510, 500, 570, 680, 570 };
	int StrasseKorrdinaten6[] = { 320, 300, 170, 300, 70, 250, 80, 90, 200, 60, 320, 150, 320, 300 };

	bZeichneStrasse("W12", "W21", 40, 2, StrasseKorrdinaten1);
	bZeichneStrasse("W23a", "W32a", 115, 6, StrasseKorrdinaten2);
	bZeichneStrasse("W23b", "W32b", 40, 2, StrasseKorrdinaten3);
	bZeichneStrasse("W24", "W42", 55, 2, StrasseKorrdinaten4);
	bZeichneStrasse("W34", "W43", 85, 5, StrasseKorrdinaten5);
	bZeichneStrasse("W44a", "W44b", 130, 7, StrasseKorrdinaten6);


	kr1->vVerbinde("W12", "W21", 40, Weg::Innerorts, true, kr2);
	kr2->vVerbinde("W23a", "W32a", 115, Weg::Unbegrenzt, false, kr3);
	kr2->vVerbinde("W23b", "W32b", 40, Weg::Innerorts, true, kr3);
	kr2->vVerbinde("W24", "W42", 55, Weg::Innerorts, true, kr4);
	kr4->vVerbinde("W43", "W34", 85, Weg::Unbegrenzt, false, kr3);
	kr4->vVerbinde("W44a", "W44b", 130, Weg::Landstrasse, false, kr4);

	Fahrzeug* car1 = new PKW("car1", 200);
	Fahrzeug* bike = new Fahrrad("bike", 15);
	PKW* car2 = new PKW("car2", 80);
	kr1->vAnnahme(car2);
	kr1->vAnnahme(car1, 2);
	kr1->vAnnahme(bike, 1.5);

	dGlobaleZeit = 0;

	while(dGlobaleZeit < 40)
	{
		srand(time(NULL));
		vSetzeZeit(dGlobaleZeit);
		
		kr1->vAbfertigung();
		kr2->vAbfertigung();
		kr3->vAbfertigung();
		kr4->vAbfertigung();

		dGlobaleZeit += 0.2;
		vSleep(200);
	}

	vBeendeGrafik();
}

void vAufgabe_9_1() 
{
	ifstream infile("VO.dat");

	if (infile.good()) cout << "Open the file successful" << endl;
	else cout << "Fail" << endl;

	PKW bus;
	Fahrrad bike;
	Kreuzung kr1;

	infile >> bus;
	infile >> bike;
	infile >> kr1;

	vHeadformat();
	cout << bus << endl;
	cout << bike << endl;
	cout << kr1 << endl;

	cout << "testfunction for ptObject function" << endl;
	AktivesVO* testptr = new Fahrzeug("testobject");
	AktivesVO* testptr2 = new PKW("pkw", 2);

	AktivesVO::map_VS["name"] = testptr;
	AktivesVO::map_VS["pkw"] = testptr2;
	try
	{
	    //AktivesVO::ptObject("test");
		AktivesVO::ptObject("pkw");
	}
	catch (const string s) { cout << s << endl;};
};

void vAufgabe_9_2()
{

	Welt world;
	world.vEinlesen("Simu.dat");
	while (dGlobaleZeit < 5)
	{
		vSetzeZeit(dGlobaleZeit);
		world.vSimulation();
		dGlobaleZeit += 0.05;
	}
}

void vAufgabe_9_3()
{
	bInitialisiereGrafik(1000,1000);

	Welt world;
	world.vEinlesenMitGrafik("SimuDisplay.dat");
	
	dGlobaleZeit = 0;
	while (dGlobaleZeit < 10)
	{
		vSetzeZeit(dGlobaleZeit);
		world.vSimulation();
		dGlobaleZeit += 0.05;
	}
	
	vBeendeGrafik();

};

int main()
{
	vHeadformat();
	//vAufgabe_7();
	//vAufgabe_8();

	//vAufgabe_9_1();

	//vAufgabe_9_2();  

	vAufgabe_9_3();

	return 0;
}	 