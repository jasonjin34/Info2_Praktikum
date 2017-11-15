#include "FzgVerhalten.h"

FzgVerhalten::FzgVerhalten()
{
}

FzgVerhalten::FzgVerhalten(Weg* input)
{
	this->p_pWegptr = input;
}

FzgVerhalten::~FzgVerhalten()
{
}

Weg * FzgVerhalten::pGetWegptr()
{
	return p_pWegptr;
}

double FzgVerhalten::dMaxGeschwindigkeit()
{
	if (p_pWegptr->eLimitoutput() == Weg::Innerorts)
	{
		return 50;
	}
	else if (p_pWegptr->eLimitoutput() == Weg::Landstrasse)
	{
		return 100;
	}
	else
	{
		return 101;
	}
}
