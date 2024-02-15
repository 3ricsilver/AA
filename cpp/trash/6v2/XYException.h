#ifndef XYEXCEPTION_H
#define XYEXCEPTION_H
#include "Exception.h"

using namespace std;

class XYException : public Exception
{
private:
	char coordonnee;

public:
	
	//constructeur//
	XYException();
	XYException(char coord, string message);
	//Destructeur//
	~XYException();
	//Getter & setter//

	char getCoordonnee() const;
	void setCoordonnee(char coord);
};

#endif