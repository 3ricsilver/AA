#include "XYException.h"
#include "ImageNG.h"
#include "Dimension.h"



#include <string.h>

using namespace std;


/*constructeur | destructeur*/
Dimension :: Dimension()
{
	cout<<"Constructeur par defaut de la Classe Dimension"<<endl;
	setLargeur(400);
	setHauteur(300);
}


Dimension ::Dimension(const Dimension& d)
{
	cout<<"Constructeur de copie de la Classe Dimension"<<endl;
	setLargeur(d.largeur);
	setHauteur(d.hauteur);
}

Dimension ::Dimension(int l,int h)
{
	cout<<"Constructeur d'initialisation de la classe Dimension"<<endl;

	if(l<0 && h<0) throw XYException("Dimension invalide : ",'d');
	{
		setLargeur(l);
		setHauteur(h);		
	}

}

Dimension ::~Dimension()
{
	cout<<"Destructeur par defaut de la classe Dimension"<<endl;
}

/*Get | Set */
void Dimension ::setLargeur(int l)
{
	if(l<0) throw XYException("valeur de la largeur invalide : ",'x');
	{
		largeur=l;
	}
}

void Dimension ::setHauteur(int h)
{
	if(h<0) throw XYException("valeur de la hauteur invalide : ",'y');
	{
		hauteur=h;
	}
}


int Dimension::getLargeur() const
{
	return largeur;
}

int Dimension ::getHauteur() const
{
	return hauteur;
}

/*Méthode*/
void Dimension ::Affiche() const
{
	cout<<"largeur="<<largeur<<"  hauteur="<<hauteur<<endl;
}

/*Surchage*/
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


const Dimension Dimension::VGA(640,480);
const Dimension Dimension::HD(1280,720);
const Dimension Dimension::FULL_HD(1920,1080);