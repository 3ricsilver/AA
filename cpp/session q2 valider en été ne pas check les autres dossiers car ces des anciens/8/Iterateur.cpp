#include "Iterateur.h"
#include "Couleur.h"

#include "ArrayList.h"



/*template <class T>//je ne peux pas faire ca selon chat car il doit etre fait a l'iniation et non aprés comme j'ai voulu le faire 
Iterateur<T>::Iterateur(ArrayList<T>& i)
{
    list = i;        
    pCur = i.pTete;  
}*/

template <class T>
Iterateur<T>::Iterateur(ArrayList<T>& i):list(i),pCur(i.pTete)
{

}

template <class T>
bool Iterateur<T>::	 end()
{
	return pCur==nullptr;
}

template <class T>
void Iterateur<T>:: reset()
{
	pCur = list.pTete;
}

template <class T>
void Iterateur<T>:: operator++()
{
	if(pCur)
	{
		pCur= pCur->suivant;
	}
}


template <class T>
void Iterateur<T>:: operator++(int post)
{
	return operator++();
}

template <class T>
Iterateur<T>:: operator T()
{
	return pCur->valeur;
}

template <class T>
T& Iterateur<T>:: operator&()
{
	return pCur->valeur;
}


template class ArrayList<int>;

template class ArrayList<Couleur>;

template class Iterateur<int>;

#include "Couleur.h"
template class Iterateur<Couleur>;

#include "Image.h"
template class Iterateur<Image *>;