#ifndef RGBEXCEPTION_H
#define RGBEXCEPTION_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include "Exception.h"

using namespace std;

class RGBException:public Exception
{
	protected:

		int val;

	public:
		//constructeur//
		RGBException();
		RGBException(int val,string MessageErreur);
		RGBException(const RGBException &exception);

		//destructeur//
		~RGBException();

		////get & seter/////
	    int getValeur() const;
	    void setValeur(int valeur);


};

#endif
