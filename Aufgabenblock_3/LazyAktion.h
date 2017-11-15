#pragma once
#include <list>
#include <iostream>
using namespace std;

template <class T>
class LazyAktion
{
public:
	//default constructor
	LazyAktion() {};
	//defualt destructor
	virtual ~LazyAktion() { delete p_ptListe; };
	//rein virtual function 
	virtual void vAusfuehren() = 0;

protected:
	list<T>* p_ptListe;
};

template <class T>
class LazyPushFront: public LazyAktion<T>
{
public:
	LazyPushFront() {};
	//constructor with T object and plist initialisation 
	LazyPushFront(T p_tObject , list<T>* p_ptList) { p_ptList(p_ptList),p_tObject(p_tObject)};

	virtual void vAusfuehren()
	{
		p_ptListe->push_front(p_tObject);
	};

private:
	T p_tObject;
};

template <class T>
class LazyPushBack : public LazyAktion<T>
{
public:
	LazyPushBack() {};
	//constructor with T object and plist initialisation 
	LazyPushBack(T p_tObject, list<T>* p_ptList) {
		this->p_tObject = p_tObject;
		this->p_ptListe = p_ptList;
	};

	virtual void vAusfuehren()
	{
		p_ptListe->push_back(p_tObject);
	};

private:
	T p_tObject;
};

template <class T>
class LazyErase : public LazyAktion<T>
{
public:
	LazyErase() {};
	//constructor with T object and plist initialisation 
	LazyErase(typename list<T>::iterator p_tObject, list<T>* p_ptList) { 
		this->p_tObject = p_tObject;
		this->p_ptListe = p_ptList;
	};

	virtual void vAusfuehren()
	{
		p_ptListe->erase(p_tObject);
	};

private:
	typename list<T>::iterator p_tObject;
};


