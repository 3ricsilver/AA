#include "RGBException.h"

using namespace std;


RGBException::RGBException():Exception() 
{
	cout<<"Constructeur par defaut de la classe RGBException"<<endl;
}




RGBException:: RGBException(const RGBException& cop):Exception(cop)
{
	cout<<"Constructeur de Copie de la classe RGBException"<<endl;

	valeur=cop.valeur;
}

RGBException:: RGBException(string msgErreur,int valeurE):Exception(msgErreur)
{
	setValeur(valeurE);
}

RGBException::~RGBException()
{
	cout<<"Destructeur par defaut de la classe RGBException"<<endl;
}

int RGBException::getValeur()const
{
	return valeur;
}

void RGBException::setValeur(int valeurE)
{
	valeur=valeurE;
}