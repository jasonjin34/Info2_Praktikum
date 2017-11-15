#include "Welt.h"

Welt::Welt()
{
}


Welt::~Welt()
{
}

void Welt::vEinlesen(string inputfile)
{
	ifstream infile(inputfile);
	//check if the file open successfully
	if (infile.good()) cout << "Open the file successful" << endl;
	else cout << "Fail" << endl;
	
	bool b_endfile = false;

	while (1)
	{
		string sKeyword;
		infile >> sKeyword;

		if (sKeyword == "PKW")
		{
			PKW* pkwptr = new PKW();
			infile >> *pkwptr;
		
			string sKreuzungname;
			infile >> sKreuzungname;

			double dLosfahrentime;
			infile >> dLosfahrentime;

			try
			{
				AktivesVO::ptObject(sKreuzungname);
			}
			catch (const string s)
			{
				cout <<  "PKW Kreuzung "  << s << endl;
				continue;
			}

			Kreuzung* kreuzungptr = (Kreuzung*) AktivesVO::ptObject(sKreuzungname); // typecasting from type AktivesVO pointer to Kreuzung pointer
			kreuzungptr->vAnnahme(pkwptr,dLosfahrentime);
			cout << "PKW " << pkwptr->sName() << " added. " << endl;
		}
		else if (sKeyword == "KREUZUNG")
		{
			Kreuzung* kreuzungptr = new Kreuzung();
			infile >> *kreuzungptr;

			AktivesVO::map_VS.insert(pair<string,AktivesVO*>(kreuzungptr->sGetname(),kreuzungptr));
			cout << "Kreuzung " << kreuzungptr->sGetname() << " added" << endl;
		}
		else if (sKeyword == "STRASSE")
		{
			string NameQ;	
			infile >> NameQ;
			string NameZ;
			infile >> NameZ;
			string NameW1;
			infile >> NameW1;
			string NameW2;
			infile >> NameW2;
			double length;
			infile >> length;

			/*Speed limiting setting*/
			int Begrenzung;
			infile >> Begrenzung;
			Weg::Begrezung eBegrenzung;
			if (Begrenzung == 1) eBegrenzung = Weg::Innerorts;
			else if (Begrenzung == 2) eBegrenzung = Weg::Landstrasse;
			else if (Begrenzung == 3) eBegrenzung = Weg::Unbegrenzt;

			/*bool member varialbe read*/
			int ibool;
			infile >> ibool;
			bool bUberholtverbot;
			if(ibool == 1) bUberholtverbot = true;
			else bUberholtverbot = false;

			/*kreuzung connection*/
			try
			{
				AktivesVO::ptObject(NameQ); // typecasting from type AktivesVO pointer to Kreuzung pointer
				AktivesVO::ptObject(NameZ);
			}
			catch (const string s) { 
				cout << "Street" << s << endl; 
				continue; };

			Kreuzung* krQuelleptr = (Kreuzung*)AktivesVO::ptObject(NameQ); // typecasting from type AktivesVO pointer to Kreuzung pointer
			Kreuzung* krZieleptr = (Kreuzung*)AktivesVO::ptObject(NameZ);

			krQuelleptr->vVerbinde(NameW1, NameW2, length,eBegrenzung ,bUberholtverbot, krZieleptr);
			krZieleptr->vVerbinde(NameW2, NameW1, length, eBegrenzung, bUberholtverbot, krQuelleptr);

			cout << "Street "<< NameW1 << ","<< NameW2 << " added" << endl;
		}
		else if (sKeyword == "FAHRRAD")
		{
			Fahrrad* bikeptr = new Fahrrad();
			infile >> *bikeptr;

			string sKreuzungname;
			infile >> sKreuzungname;

			double dLosfahrentime;
			infile >> dLosfahrentime;

			try
			{
				AktivesVO::ptObject(sKreuzungname);
			}
			catch (const string s)
			{
				cout << "FAHRRAD Kreuzung " << s << endl;
				continue;
			}

			//find the kreuzung ptr 
			Kreuzung* kreuzungptr = (Kreuzung*)AktivesVO::ptObject(sKreuzungname); // typecasting from type AktivesVO pointer to Kreuzung pointer
			kreuzungptr->vAnnahme(bikeptr, dLosfahrentime);

			cout << "Fahrrad " << bikeptr->sName() << " added" << endl;
		}

		//end of file checking
		b_endfile = infile.eof();
		if (b_endfile) break;
	}
}

void Welt::vEinlesenMitGrafik(string inputfilename)
{
	ifstream infile(inputfilename);
	//check if the file open successfully
	if (infile.good()) cout << "Open the file successful" << endl;
	else cout << "Fail" << endl;

	bool b_endfile = false;

	while (1)
	{
		string sKeyword;
		infile >> sKeyword;

		if (sKeyword == "PKW")
		{
			PKW* pkwptr = new PKW();
			infile >> *pkwptr;

			string sKreuzungname;
			infile >> sKreuzungname;

			double dLosfahrentime;
			infile >> dLosfahrentime;

			try
			{
				AktivesVO::ptObject(sKreuzungname);
			}
			catch (const string s)
			{
				cout << "PKW Kreuzung " << s << endl;
				continue;
			}
			Kreuzung* kreuzungptr = (Kreuzung*)AktivesVO::ptObject(sKreuzungname); // typecasting from type AktivesVO pointer to Kreuzung pointer
			kreuzungptr->vAnnahme(pkwptr, dLosfahrentime);
			cout << "PKW " << pkwptr->sName() << " added. " << endl;
		}
		else if (sKeyword == "KREUZUNG")
		{
			Kreuzung* kreuzungptr = new Kreuzung();
			infile >> *kreuzungptr;

			/*read koordinate data*/
			int x;
			int y;
			infile >> x;
			infile >> y;

			/*draw Kreuzung*/
			bZeichneKreuzung(x,y);

			AktivesVO::map_VS.insert(pair<string, AktivesVO*>(kreuzungptr->sGetname(), kreuzungptr));
			cout << "Kreuzung " << kreuzungptr->sGetname() << " added" << endl;
		}
		else if (sKeyword == "STRASSE")
		{
			string NameQ;
			infile >> NameQ;
			string NameZ;
			infile >> NameZ;
			string NameW1;
			infile >> NameW1;
			string NameW2;
			infile >> NameW2;
			double length;
			infile >> length;

			/*Speed limiting setting*/
			int Begrenzung;
			infile >> Begrenzung;
			Weg::Begrezung eBegrenzung;
			if (Begrenzung == 1) eBegrenzung = Weg::Innerorts;
			else if (Begrenzung == 2) eBegrenzung = Weg::Landstrasse;
			else if (Begrenzung == 3) eBegrenzung = Weg::Unbegrenzt;

			/*bool member varialbe read*/
			int ibool;
			infile >> ibool;
			bool bUberholtverbot;
			if (ibool == 1) bUberholtverbot = true;
			else bUberholtverbot = false;

			/*get the koordinate data*/
			int numberofturn;
			infile >> numberofturn;

			//add the rest position data in koordinatearray
			int* koordinate = new int[2*numberofturn];

			for (int i = 0; i < numberofturn * 2; i++) //total number of koordinate is equal 2 times the number of turn
			{
				infile >> *(koordinate + i);
			}

			bZeichneStrasse(NameW1, NameW2, length, numberofturn, koordinate);

			/*kreuzung connection*/
			try
			{
				AktivesVO::ptObject(NameQ); // typecasting from type AktivesVO pointer to Kreuzung pointer
				AktivesVO::ptObject(NameZ);
			}
			catch (const string s) {
				cout << "Street" << s << endl;
				continue;
			};

			Kreuzung* krQuelleptr = (Kreuzung*)AktivesVO::ptObject(NameQ); // typecasting from type AktivesVO pointer to Kreuzung pointer
			Kreuzung* krZieleptr = (Kreuzung*)AktivesVO::ptObject(NameZ);
				
			krQuelleptr->vVerbinde(NameW2, NameW1, length, eBegrenzung, bUberholtverbot, krZieleptr);
			cout << "Street " << NameW1 << "," << NameW2 << " added" << endl;
		}
		else if (sKeyword == "FAHRRAD")
		{
			Fahrrad* bikeptr = new Fahrrad();
			infile >> *bikeptr;

			string sKreuzungname;
			infile >> sKreuzungname;

			double dLosfahrentime;
			infile >> dLosfahrentime;

			try
			{
				AktivesVO::ptObject(sKreuzungname);
			}
			catch (const string s)
			{
				cout << "FAHRRAD Kreuzung " << s << endl;
				continue;
			}

			Kreuzung* kreuzungptr = (Kreuzung*)AktivesVO::ptObject(sKreuzungname); // typecasting from type AktivesVO pointer to Kreuzung pointer
			kreuzungptr->vAnnahme(bikeptr, dLosfahrentime);

			cout << "Fahrrad " << bikeptr->sName() << " added" << endl;
		}

		//end of file checking
		b_endfile = infile.eof();
		if (b_endfile) break;
	}
}

void Welt::vSimulation()
{
	map<string, AktivesVO*>::iterator it;
	for (it = AktivesVO::map_VS.begin(); it != AktivesVO::map_VS.end(); it++)
	{
		Kreuzung* kreuzungptr;
		it->second->vAbfertigung();
	}
}
