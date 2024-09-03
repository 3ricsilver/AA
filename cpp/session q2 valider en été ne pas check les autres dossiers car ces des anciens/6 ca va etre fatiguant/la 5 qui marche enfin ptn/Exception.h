#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
using namespace std;

class Exception {
protected:
    string errorMsg; 

public:
    Exception();
    Exception(string msg);
    Exception(const Exception& cop);
    virtual ~Exception();

    virtual string getMsg() const;
    virtual void setMsg(string msg);
};

#endif
