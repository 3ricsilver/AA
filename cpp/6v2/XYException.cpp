#include "XYException.h"
#include <iostream>
#include <string.h>

using namespace std;

//constructeur//

XYException::XYException() : Exception(),coordonnee('A'){}
// {
// 	setCoordonnee('d');

// 	cout << "--Constructeur par défaut XYException--" << endl;
// }

XYException::XYException(char coord, string message):Exception(move(message)),coordonnee(coordonnee){}
// {
// 	setCoordonnee(coord);

// 	cout << "--Constructeur d'init XYException--" << endl;
// }

//destructeur//

XYException::~XYException()
{
	cout << "--Destructeur XYException--" << endl;
}

//getter &&  setter //

char XYException::getCoordonnee() const
{
    return coordonnee;
}

void XYException::setCoordonnee(char coord) 
{
    coordonnee = coord;
}