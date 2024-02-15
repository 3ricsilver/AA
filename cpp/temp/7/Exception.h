#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

class Exception
{

protected:

	string MessageErreur;

public:
	//constructeur//
	Exception();
	Exception(string MessageErreur);
	Exception(const Exception &exception);

	//destructeur//
	virtual ~Exception();

	////get & seter/////
    string getMessage() const;
    void setMessage(string MessageErreur);


    //////////////////////
    void Affiche()const;
};

#endif


/*
to do 



*/