#include "XYException.h"
using namespace std;



XYException::XYException():Exception()
{
	cout<<"Constructeur par defaut de la classe XYException"<<endl;
}


XYException::~XYException()
{
	cout<<"Destructeur par defaut de la classe XYException"<<endl;
}

XYException:: XYException(const XYException& cop):Exception(cop.errorMsg)
{
	cout<<"Constructeur de Copie de la classe RGBException"<<endl;

	setCoordonee(cop.coordonne);

}

XYException::XYException(string msgErreur, char coord):Exception(msgErreur), coordonne(coord)
{
	setCoordonee(coord);
}

char XYException:: getCoordonee()const
{
	return coordonne;
}

void XYException:: setCoordonee(char coord)
{
 	coordonne = coord;
}