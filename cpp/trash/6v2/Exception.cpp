#include "Exception.h"
#include <iostream>
#include <string.h>

using namespace std;

	//constructeur//
	Exception::Exception()
	{
		setMessage("");
		cout <<"Constructeur par défaut de la classe Exception"<< endl;
	}

	Exception::Exception(string MessageErreur)
	{
		setMessage(MessageErreur);
		cout <<"Constructeur de la classe Exception"<< endl;
	}
	
	Exception::Exception(const Exception &exception)
	{
		setMessage(exception.MessageErreur);
		cout <<"Constructeur de copie de la classe Exception"<< endl;		
	}

	//destructeur//
	Exception::~Exception()
	{
		cout <<"Destructeur de la classe Exception"<< endl;
	}

	////get & seter/////
    string Exception::getMessage() const
    {
    	return MessageErreur;
    }

    void Exception::setMessage(string Erreur)
    {
    	MessageErreur=Erreur;
    }