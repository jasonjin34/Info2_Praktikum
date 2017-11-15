/*template*/
#pragma once
#include"LazyAktion.h"
#include <list>
using namespace std;

template <class T>
class LazyListe
{

public:
	//default contructor
	LazyListe() {};

	//destructor 
	virtual ~LazyListe() {};

	// type is list<Fahrzeug*>::iterator 
	typename list<T>::iterator begin(){ return p_ListeObjecte.begin(); };

	typename list<T>::iterator end(){ return p_ListeObjecte.end();};

	bool empty(){return p_ListeObjecte.empty();};

	void push_front(T val) { 
		// Add LazyAktion in the front of the list
		p_ListeAktionen.push_front(new LazyPushFront<T>(val, &p_ListeObjecte));
	};

	void push_back(T val) { 
		p_ListeAktionen.push_back(new LazyPushBack<T>(val, &p_ListeObjecte));
	};

	void erase(typename list<T>::iterator itpos){
		p_ListeAktionen.push_back(new LazyErase<T>(itpos, &p_ListeObjecte));
	}

	void clear()
	{
		p_ListeObjecte.clear();
	}

	void vAktualisieren()
	{
		for (list<LazyAktion<T>*>::iterator it = p_ListeAktionen.begin(); 
			 it != p_ListeAktionen.end(); ++it) { (*it)->vAusfuehren();}
		//all the ListeAktion objects need to be removed after ausfuehren
		//otherweise all the element will be in listeobject again
		p_ListeAktionen.clear();

	};

	void vAusgabe()
	{
		for (list<T>::iterator it = p_ListeObjecte.begin();
			it != p_ListeObjecte.end();
			it++)
		{
			cout << *it << endl;
		}
	};

private:
	list<T> p_ListeObjecte;
	list<LazyAktion<T>*> p_ListeAktionen;
};

