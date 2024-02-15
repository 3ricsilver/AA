#include "XYException.h"
#include <iostream>

XYException :: XYException() : Exception()
{
	setMessage("\nException XY\n");
}

XYException :: XYException(const string& message, const char e, const int x, const int y) : Exception(message)
{
	setErreurValeur(e);

	setX(x);

	setY(y);
}

XYException :: XYException(const string& message, const char e, const int valeur) : Exception(message)
{
	setErreurValeur(e);

	setX(valeur);

	setY(valeur);

}

XYException :: XYException(const string& message, const char e) : Exception(message)
{
	setErreurValeur(e);
}

XYException :: XYException(const XYException &xyexception) : Exception(xyexception)
{
	setErreurValeur(xyexception.getErreurValeur());

	setX(xyexception.getX());

	setY(xyexception.getY());
}

XYException :: ~XYException()
{

}

void XYException :: setErreurValeur(const char e)
{
	if(ErreurValeur < 0 || ErreurValeur > 700)
	{
		ErreurValeur = e;
	}
}

char XYException :: getErreurValeur()const
{
	return ErreurValeur;
}

void XYException:: setX(const int x)
{
	
	if(x < 0 || x > 700)
	{
		ErreurValeur = x;
	}

	
}

int XYException :: getX()const
{
	return x;
}

void XYException :: setY(const int y)
{
	if(y < 0 || y > 700)
	{
		ErreurValeur = y;
	}
}

int XYException :: getY()const
{
	return y;
}

void XYException :: Affiche()const
{
	Exception::Affiche();
}