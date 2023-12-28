#include <iostream>
using namespace std; // Add this line
#include "Couleur.h"
#include <stdlib.h>
#include <string.h>



////constructeur///
//par Défaut//
Couleur::Couleur()
{
	setRouge(0);
	setVert(0);
	setBleu(0);
}

//le reste

Couleur::Couleur(int rouge,int vert,int bleu)
{
	setRouge(rouge);
	setVert(vert);
	setBleu(bleu);
}
// constructeur de copie
Couleur::Couleur(const Couleur& couleur)
{
	setRouge(couleur.rouge);
	setVert(couleur.vert);
	setBleu(couleur.bleu);
}

//Destructeur CR7//
Couleur::~Couleur()
{
	cout <<"passage destructeur"<<endl;// a amodif
}
////setter//
void Couleur::setRouge(int val)
{
	rouge=val; 
}
void Couleur::setVert(int val)
{
	vert=val;
}
void Couleur::setBleu(int val)
{
	bleu=val;
}

//getter//

int Couleur::getBleu()const
{
	return bleu;
}

int Couleur::getRouge()const
{
	return rouge;
}

int Couleur::getVert()const
{
	return vert;
}

////////////
void Couleur::Affiche() const
{
cout <<"Rouge:"<<rouge<<" Vert:"<<vert<<"Bleu:"<<bleu<< endl;
}

//surchage
ostream& operator<<(std::ostream& s,const Couleur& valeur)
{
  s << "Rouge: " << valeur.rouge << ", Vert: " << valeur.vert << ", Bleu: " << valeur.bleu ;
  return s;
}

//les couleurs hardcodé

const Couleur Couleur::NOIR(0, 0, 0);
const Couleur Couleur::BLEU(0, 0, 255);
const Couleur Couleur::VERT(0, 255, 0);
const Couleur Couleur::ROUGE(255, 0, 0);
const Couleur Couleur::BLANC(255, 255, 255);
