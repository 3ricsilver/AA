#ifndef XYEXCEPTION_H
#define XYEXCEPTION_H

#include "Exception.h"
#include "Dimension.h"
using namespace std;


class XYException :public Exception
{
private:
	char coordonne;
public:

	XYException();
	~XYException();
	XYException(const XYException& cop);
	XYException(string  msgErreur, char coord);

	char getCoordonee()const;
	void setCoordonee(char coord);
	
};




#endif