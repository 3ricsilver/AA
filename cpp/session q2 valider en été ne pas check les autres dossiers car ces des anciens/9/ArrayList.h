#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "Iterateur.h"

template<class T> struct Cellule
{

	T valeur ;
	Cellule<T> *suivant ;

};

template<class T> class Iterateur;

template<class T> class ArrayList
{

private:
	Cellule<T> *pTete;//wtf c comme algorithme 


public:
	ArrayList ();
	ArrayList(const ArrayList & l);
	~ArrayList();

	int getNombreElements()const;
	T& getElement(int ind);


	void Affiche()const;
	bool estVide();


	void insereElement(const T & val);
	T retireElement(int ind);

	T& operator=(const ArrayList & l);

	friend class Iterateur<T>;


};


#endif