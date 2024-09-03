#ifndef ITERATEUR_H
#define ITERATEUR_H



template<class T> class ArrayList;

template<class>	struct Cellule;


template<class T>
class Iterateur
{

private:
	Cellule<T> *pCur;
	ArrayList<T>& list;

public:
	
	Iterateur(ArrayList<T>& i);
	bool end();
	void reset();

	void operator++();
	void operator++(int post);

	operator T();
	T& operator&();
	
	
};




#endif