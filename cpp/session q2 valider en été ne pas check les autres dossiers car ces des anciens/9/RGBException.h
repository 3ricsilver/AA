#ifndef RGBEXECPTION_H
#define RGBEXECPTION_H

#include "Exception.h"
#include "Couleur.h"
#include "ImageNG.h"
using namespace std;


class RGBException :public Exception
{
private:
	int valeur;

public:
	RGBException();
	RGBException(const RGBException& cop);
	RGBException(string  msgErreur, int valeurE);

	~RGBException();

	int getValeur()const;
	void setValeur(int valeurE);
	

};
#endif