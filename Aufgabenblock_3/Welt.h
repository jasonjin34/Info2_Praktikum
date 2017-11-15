#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "AktivesVO.h"
#include "Kreuzung.h"
#include "PKW.h"
#include "Fahrrad.h"

class Fahrzeug;
class Kreuzung;
class PKW;
class Faharrd;
class AktviesVO;

class Welt
{
public:
	Welt();
	virtual ~Welt();

	void vEinlesen(string );

	void vEinlesenMitGrafik(string);

	void vSimulation();
};

