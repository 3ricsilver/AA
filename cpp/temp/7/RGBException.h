//to do wagner a dit d'utilisr throw

#include <stdlib.h>
#include <iostream>
#include <string>
#include "Exception.h"
using namespace std;

#ifndef RGBEXCEPTION_H
#define RGBEXCEPTION_H

class RGBException:public Exception
{

public:

	//constructeur//
	RGBException();
	RGBException(string message, int valeur);
	RGBException(const RGBException &rgbexception);

	//destructeur//
	~RGBException();

	//getter && seller //
	void setValeur(int valeur);
    int getValeur()const;

    //methode//
    void Affiche()const;

private:
	int ValeurErreurException;    

};


#endif

