#include "Couleur.h"
#include <iostream>
using namespace std;

//constructeur//

Couleur :: Couleur()
{
	setBleu(0);
	setRouge(0);
	setVert(0);
}

Couleur :: Couleur(int r, int v, int b)
{
	setBleu(b);
	setRouge(r);
	setVert(v);
}

//copie//

Couleur :: Couleur(const Couleur &couleur)
{

	bleu = couleur.bleu;

	rouge = couleur.rouge;

	vert = couleur.vert;
}

//getter//

int Couleur :: getVert()const
{
	return vert;
}

int Couleur :: getBleu()const
{
	return bleu;
}


int Couleur :: getRouge()const
{
	return rouge;
}

//Setter//

void Couleur :: setVert(int val)
{
	if (val >= 0)
		vert = val;
}

void Couleur :: setRouge(int val)
{
	if (val >= 0)
		rouge = val;
}

void Couleur :: setBleu(int val)
{
	if (val >= 0)
		bleu = val;
}


/////////////

//Surcharge//

std::ostream& operator<< (std::ostream &out,const Couleur &couleur)
{
	out <<"Bleu : " << couleur.getBleu() <<endl;
	out <<"Rouge : " << couleur.getRouge() <<endl;
	out <<"Vert : " << couleur.getVert() <<endl;

	return out;
}

//methode//

void Couleur :: Affiche()const
{
	cout <<"Bleu : " << bleu << endl;
	cout <<"Rouge : " << rouge << endl;
	cout <<"Vert : " << vert << endl;

}

//hardcoder//

const Couleur Couleur::BLEU(0, 0, 255);

const Couleur Couleur::ROUGE(255, 0, 0);

const Couleur Couleur::VERT(0, 255, 0);

const Couleur Couleur::BLANC(255, 255, 255);

const Couleur Couleur::NOIR(0, 0, 0);





