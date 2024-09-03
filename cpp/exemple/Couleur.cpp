#include "Couleur.h"


Couleur:: Couleur()
{
	#ifdef DEBUG
	cout<<"Constructeur par defaut de ImageRGB"<<endl;
	#endif

	setRouge(0);
	setVert(0);
	setBleu(0);

}


Couleur::~Couleur()
{
	#ifdef DEBUG
	cout<<"Destructeur par defaut de la classe Couleur"<<endl;
	#endif
}



Couleur:: Couleur(int r,int v,int b)
{
	#ifdef DEBUG
	cout<<"Constructeur d'initialisation  de la classe Couleur"<<endl;
	#endif

	setRouge(r);
	setVert(v);
	setBleu(b);
}

const Couleur Couleur::ROUGE(255,0,0);
const Couleur Couleur::VERT(0,255,0);
const Couleur Couleur::BLEU(0,0,255);
const Couleur Couleur::BLANC(255,255,255);
const Couleur Couleur::NOIR(0,0,0);

void Couleur::setRouge(int r)
{
	rouge =r;
}

void Couleur::setVert(int v)
{
	vert =v;
}

void Couleur::setBleu(int b)
{
	bleu =b;
}

int Couleur::getRouge()const
{
	return rouge;
}

int Couleur::getVert()const
{
	return vert;
}

int Couleur::getBleu()const
{
	return bleu;
}



ostream& operator<<(ostream& s, const Couleur& c)
{
	s << "Rouge : "<<  c.rouge << "	vert : "<<  c.vert <<"	Bleu : "<<  c.bleu<<endl;

	return s;
}

void Couleur::Affiche()const
{
	cout << "Rouge : " <<getRouge() << "	vert : "	<<getVert() <<"	Bleu : "<<getBleu()<<endl<<endl;
}