#include "RGBException.h"
#include <iostream>
#include <string.h>

using namespace std;




	//constructeur//
	RGBException::RGBException(): Exception()
	{
		setValeur(0);
		cout <<"Constructeur par défaut de la classe RGBException"<< endl;

	}

	RGBException::RGBException(int val,string MessageErreur): Exception(MessageErreur)
	{
		setValeur(val);
		cout <<"Constructeur de la classe RGBException"<< endl;

	}
	RGBException::RGBException(const RGBException &exception): Exception(exception)
	{
		setValeur(exception.val);
		cout << "--Constructeur de copie de la RGBException--" << endl;
	}

	//destructeur//
	RGBException::~RGBException()
	{
		cout <<"Destructeur de la classe RGBException"<< endl;
	}

	////get & seter/////
    int RGBException::getValeur() const
    {
    	return val;
    }
    void RGBException::setValeur(int valeur)
    {
    	val=valeur;
    }