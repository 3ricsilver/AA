#include<iostream>
#include"ArrayList.h"

//pense a la pile eric a la place des int use Cellule<T> 
	
	//constructeur && copie/:

	template<class T>
	ArrayList<T>::ArrayList()
	{

	}

	template<class T>
	ArrayList<T>::ArrayList(const ArrayList &arraylist)
	{
		Cellule<T> *cur=arraylist.pTete;
		while(estVide(cur)!=0)
		{
			insereElement(cur->valeur !=nullptr);
			cur=cur->next;
		}
	}

	//destructeur //

	template<class T>
	ArrayList<T>::~ArrayList()
	{


		Cellule<T> *cur = curptete;
		Cellule<T> *next = nullptr;

		while (cur != nullptr)
		{
			next = cur->Suivant;
			delete cur;
			cur = next;
		}		
	}

	//methode//
	template<class T>
	ArrayList<T>::bool estVide()const
	{
		if (PTete == nullptr)
		{
			return true;			
		}

		return false;
	}
	
	template<class T>
	ArrayList<T>::void Affiche()const
	{
		Cellule<T> *cur = PTete;

		while (cur != nullptr)
		{
			cout << "Voici la valeur : " <<cur->valeur << endl;

			cur = cur->next;
		}		
	}

	//gestion elemeent
	
	template<class T>
	ArrayList<T>::int getNombreElements()const
	{

	}

	template<class T>
	ArrayList<T>::void insereElement(const T & val)
	{

	}

	template<class T>
	ArrayList<T>::T &getElement(int ind)const
	{

	}

		template<class T>
	ArrayList<T>::T retireElement(int ind);

	//surcharge//

	ArrayList &operator=(const ArrayList &liste);
