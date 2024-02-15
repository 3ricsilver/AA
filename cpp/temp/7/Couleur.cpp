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

Couleur :: Couleur(int rouge, int vert, int bleu)
{
	setBleu(bleu);
	setRouge(rouge);
	setVert(vert);
}

//copie//

Couleur :: Couleur(const Couleur &couleur)
{

	Bleu = couleur.Bleu;

	Rouge = couleur.Rouge;

	Vert = couleur.Vert;
}

//getter//

int Couleur :: getVert()const
{
	return Vert;
}

int Couleur :: getBleu()const
{
	return Bleu;
}


int Couleur :: getRouge()const
{
	return Rouge;
}

//Setter//

void Couleur :: setVert(int val)
{
	if (val >= 0)
	{
		Vert = val;
	}
	if(val < 0 || val > 255)
	{
		throw RGBException("\nValeur Vert incorrecte !", val);		//
	}
}

void Couleur :: setRouge(int val)
{
	if (val >= 0)
	{
		Rouge = val;
	}
	if(val < 0 || val > 255)
	{
		throw RGBException("\nValeur Rouge incorrecte !", val);		
	}
}

void Couleur :: setBleu(int val)
{
	if (val >= 0 )
	{
		Bleu = val;
	}
	if(val < 0 || val > 255)
	{
		throw RGBException("\nValeur Bleue incorrecte !", val);		
	}
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
	cout <<"Bleu : " << Bleu << endl;
	cout <<"Rouge : " << Rouge << endl;
	cout <<"Vert : " << Bleu << endl;

}

//hardcoder//

const Couleur Couleur::BLEU(0, 0, 255);

const Couleur Couleur::ROUGE(255, 0, 0);

const Couleur Couleur::VERT(0, 255, 0);

const Couleur Couleur::BLANC(255, 255, 255);

const Couleur Couleur::NOIR(0, 0, 0);






