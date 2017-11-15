#include "FzgFahren.h"


FzgFahren::FzgFahren()
{
}

FzgFahren::FzgFahren(Weg* wegptr)
{
	this->p_pWegptr = wegptr;
}


FzgFahren::~FzgFahren()
{
}

double FzgFahren::dStreck(Fahrzeug* fahrzeugptr, double zeitraum)
{
	//not überholverbot street
	if (p_pWegptr->bGetuberholverbot() == false)
	{
		double distance = fahrzeugptr->dGeschwindigkeit()*zeitraum;
		if (fahrzeugptr->dAbschnittStrecke() + distance < p_pWegptr->dLaengeoutput())
		{
			return distance;
		}
		else
		{
			throw Streckenende(fahrzeugptr, p_pWegptr);
		}
	}
	else //überholverbot steet
	{
		double distance = fahrzeugptr->dGeschwindigkeit()*zeitraum;
		if (fahrzeugptr->dAbschnittStrecke() + distance < p_pWegptr->dLaengeoutput()
			&& fahrzeugptr->dAbschnittStrecke() + distance < p_pWegptr->dGetVschranke())
		{
			//setting the virtuelle schrank for the next fahrzeug
			p_pWegptr->vSetdVschranke(distance + fahrzeugptr->dAbschnittStrecke());
			return distance;
		}
		else if (fahrzeugptr->dAbschnittStrecke() + distance - p_pWegptr->dLaengeoutput() >= 0.003) //exceeding the weg length
		{
			throw Streckenende(fahrzeugptr, p_pWegptr);
		}
		else if (fahrzeugptr->dAbschnittStrecke() + distance >= p_pWegptr->dGetVschranke()) // shorter than weg lenth, longer than virtuelle schranke
		{
			return p_pWegptr->dGetVschranke() - fahrzeugptr->dAbschnittStrecke();
		}
		else
		{
			return p_pWegptr->dLaengeoutput() - fahrzeugptr->dAbschnittStrecke();
		}
	}
}
