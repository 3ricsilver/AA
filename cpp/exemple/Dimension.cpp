#include "ImageNG.h"
#include "Dimension.h"

#include <string.h>

using namespace std;

Dimension :: Dimension()
{
	#ifdef DEBUG
	cout<<"Constructeur par defaut de la Classe Dimension"<<endl;
	#endif

	largeur=400;
	hauteur=300;

}

Dimension ::~Dimension()
{
	#ifdef DEBUG
	cout<<"Destructeur par defaut de la classe Dimension"<<endl;
	#endif

}

Dimension ::Dimension(const Dimension& d)
{
	#ifdef DEBUG
	cout<<"Constructeur de copie de la Classe Dimension"<<endl;
	#endif

	setLargeur(d.largeur);
	setHauteur(d.hauteur);
}

Dimension ::Dimension(int l,int h)
{
	#ifdef DEBUG
	cout<<"Constructeur d'initialisation de la classe Dimension"<<endl;
	#endif

	setLargeur(l);
	setHauteur(h);

}


void Dimension ::setLargeur(int l)
{
	if(l>0)
		largeur=l;
}

void Dimension ::setHauteur(int h)
{
	if(h>0)
		hauteur=h;
}

const Dimension Dimension::VGA(640,480);
const Dimension Dimension::HD(1280,720);
const Dimension Dimension::FULL_HD(1920,1080);

int Dimension::getLargeur() const
{
	return largeur;
}

int Dimension ::getHauteur() const
{
	return hauteur;
}

void Dimension ::Affiche() const
{
	cout<<"largeur="<<largeur<<"  hauteur="<<hauteur<<endl;
}

ostream& operator<<(ostream& s, const Dimension& dim)
{
	s << dim.hauteur << "/" << dim.largeur;

	return s;
}

istream& operator>>(istream& s, Dimension& dim)
{
  int h, l;

	do
	{
  		cout << "hauteur : ";
  		cin >>h;

	}while(h< 0);

	do
	{
  		cout << "largeur : ";
  		cin >>l;

	}while(l< 0);

	dim.largeur= l;
	dim.hauteur= h;

	return s;
}

bool Dimension ::operator==(const Dimension& dim)const
{
	
	return (largeur==dim.getLargeur() && hauteur==dim.getHauteur());

}


bool Dimension ::operator!=(const Dimension& dim)const
{
	
	return !(*this==dim);
}