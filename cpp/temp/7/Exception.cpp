#include "Exception.h"
#include <iostream>

//constructeur//


Exception :: Exception()
{
	setMessage("Exception");
}

Exception::Exception(string Message)
{
	setMessage(Message);
}

Exception :: Exception(const Exception &exception)
{
	setMessage(exception.getMessage());
}

//destructeur//

Exception :: ~Exception()
{

}

//getter & setter//

void Exception :: setMessage(string erreur)
{
	MessageErreur = erreur;
}

string Exception::getMessage() const 
{
    return MessageErreur;
}


//méthode//

void Exception :: Affiche()const
{
	cout <<"Exception rencontré :\n " << MessageErreur << endl;
}