#include "Exception.h"
#include <iostream> 

using namespace std;


Exception:: Exception()
{
	cout<<"Constructeur par defaut de la classe Exception"<<endl;
	setMsg("Execption Défaut");
}


Exception::Exception(string msg)
{
	cout<<"Constructeur d'initialisation de la classe Exception"<<endl;
	setMsg(msg);
}

Exception:: Exception(const Exception& cop)
{
	cout<<"Constructeur de Copie de la classe Exception"<<endl;
	setMsg(cop.errorMsg);
}
	

Exception::~Exception()
{
	cout<<"Destructeur par defaut de la classe Exception"<<endl;
}

string Exception::getMsg()const
{
	return errorMsg;
}

void Exception::setMsg(string msg)
{
	errorMsg=msg;
}