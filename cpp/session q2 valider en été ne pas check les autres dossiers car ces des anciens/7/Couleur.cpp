#include "Couleur.h"
#include "RGBException.h"

const Couleur Couleur::ROUGE(255,0,0);
const Couleur Couleur::VERT(0,255,0);
const Couleur Couleur::BLEU(0,0,255);
const Couleur Couleur::BLANC(255,255,255);
const Couleur Couleur::NOIR(0,0,0);

/*constructeur | destructeur*/
//ne decommente pas ca eric du future ca spam trop et c'est trop chiant quand tu lis idem pour le reste mais ca spam pas autant
Couleur:: Couleur()
{
	//cout<<"Constructeur par defaut de ImageRGB"<<endl;
	setRouge(0);
	setVert(0);
	setBleu(0);

}


Couleur::~Couleur()
{
	// cout<<"Destructeur par defaut de la classe Couleur"<<endl;
}



Couleur:: Couleur(int r,int v,int b)
{
	//cout<<"Constructeur d'initialisation  de la classe Couleur"<<endl;
	setRouge(r);
	setVert(v);
	setBleu(b);
}

/*Get | Set */

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

void Couleur::setRouge(int r)
{
	if(r<0 || r>255) throw RGBException("Erreur valeur de rouge : ",r);
	rouge =r;
}

void Couleur::setVert(int v)
{
	if(v<0 || v>255) throw RGBException("Erreur valeur de vert : ",v);
	vert =v;
}

void Couleur::setBleu(int b)
{
	if(b<0 || b>255) throw RGBException("Erreur valeur de bleu : ",b);
	bleu =b;
}


/*Affichage*/

ostream& operator<<(ostream& s, const Couleur& c)
{
	s << "Rouge : "<<  c.rouge << "	vert : "<<  c.vert <<"	Bleu : "<<  c.bleu<<endl;

	return s;
}

void Couleur::Affiche()const
{
	cout << "Rouge : " <<getRouge() << "	vert : "	<<getVert() <<"	Bleu : "<<getBleu()<<endl<<endl;
}