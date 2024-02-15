#include "RGBException.h"

RGBException :: RGBException() : Exception()
{
	setValeur(0);
	setMessage("Votre pixel RGB est invalide");
}

RGBException :: RGBException(string MessageErreur, int valeur):Exception(MessageErreur)
{
	setValeur(valeur);
}

RGBException :: RGBException(const RGBException &exception):Exception(exception)
{
	setValeur(exception.getValeur());
}

RGBException :: ~RGBException()
{

}

void RGBException :: setValeur(int NouvelleValeurRGB)
{
		ValeurErreurException = NouvelleValeurRGB;
}

int RGBException :: getValeur()const
{
	return ValeurErreurException;
}

void RGBException :: Affiche()const
{
	cout << "\nException rencontrer RGB de type : " << MessageErreur << endl;
}

//marche pas