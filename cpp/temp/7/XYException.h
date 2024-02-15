#include <stdlib.h>
#include <iostream>
#include <string>
#include "Exception.h"
using namespace std;


#ifndef XYEXCEPTION_H
#define XYEXCEPTION_H

class XYException : public Exception
{

private:
	char ErreurValeur;
	int x, y;

public:
	//constructeur//
	XYException();
	XYException(const string& message, const char erreur, const int x, const int y);
	XYException(const string& message, const char erreur, const int valeur);
	XYException(const string& message, const char erreur);
	//copie//
	XYException(const XYException &xyexception);
	//destructeur//
	~XYException();
	///getter &&setter//
	void setErreurValeur(const char erreur);
	void setY(const int y);
	void setX(const int x);
	char getErreurValeur()const;
	int getX()const;
	int getY()const;
	//methode//
	void Affiche()const;
};

#endif