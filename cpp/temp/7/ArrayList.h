#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
#include "Couleur.h"

using namespace std;
//en gros pense au truc de jacket avec les 3 structures d'apres c que j'ai capté vu la gueule du truc 

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

template<class T> struct Cellule
{
	T valeur ;
	Cellule<T> *next ;
}

template<class T> class ArrayList
{
	private :
	Cellule<T> *pTete=nullptr ;//pas necassaire mais dans l'algo de jacket elle disait ct mieux

	public:
	
	//constructeur && copie/:
	ArrayList();
	ArrayList(const ArrayList &arraylist);

	//destructeur //
	~ArrayList();

	//methode//
	bool estVide()const;
	void Affiche()const;

	//gestion elemeent
	int getNombreElements()const;
	void insereElement(const T & val);
	T &getElement(int ind)const;
	T retireElement(int ind);

	//surcharge//

	ArrayList &operator=(const ArrayList &liste);

}


#endif


// La classe ArrayList devra disposer des méthodes suivantes :
// • Un constructeur par défaut permettant d’initialiser le pointeur de tête à NULL.
// • Un constructeur de copie.
// • Un destructeur permettant de libérer correctement la mémoire.
// • La méthode estVide() retournant le booléen true si la liste est vide et false sinon.
// • La méthode getNombreElements() retournant le nombre d’éléments présents dans la liste.
// • La méthode Affiche() permettant de parcourir la liste et d’en afficher chaque élément.
// • La méthode void insereElement(const T & val) permettant d’insérer un nouvel élément à 
// la fin de la liste.
// • La méthode &T getElement(int ind) qui permet de récupérer l’élément situé à l’indice ind
// dans la liste mais sans le supprimer. Les valeurs possibles pour ind sont 0, …, 
// getNombreElements()-1.
// • La méthode T retireElement(int ind) qui permet de supprimer et de retourner l’élément 
// situé à l’indice ind dans la liste. Les valeurs possibles pour ind sont 0, …, 
// getNombreElements()-1.
// • Un opérateur = permettant de réaliser l’opération « liste1 = liste2 ; » sans altérer la liste2 et 
// de telle sorte que si la liste1 est modifiée, la liste2 ne l’est pas et réciproquement.
// Dans un premier temps, vous testerez votre classe ArrayList avec des entiers, puis ensuite avec 
// des objets de la classe Couleur. 
// Bien sûr, on travaillera, comme d'habitude, en fichiers séparés afin de maîtriser le problème de 
// l'instanciation des templates.