#include "ImageB.h"
#include "MyQT.h"
#include <iostream>
using namespace std;

///constructeur///////////////////////

ImageB :: ImageB(): Image()
{
	for(int i = 0; i< dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j] = false;
	
}

ImageB :: ImageB(int Id, const char *nom): Image(Id,nom)
{
	for(int i = 0; i< dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j] = false;
	
}

ImageB :: ImageB (const ImageB &imageb): Image(imageb)
{
	for(int i = 0; i< dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j] = imageb.matrice[i][j];
}

ImageB :: ImageB (int Id, const char *Nom, const Dimension &d) : Image(Id,Nom,d)
{
	for(int i = 0; i< dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j] = false;
}

////////////////////////////////////////////////

ImageB :: ~ImageB()
{
	//héritage
}



void ImageB :: setBackground(bool valeur)
{
	for(int i = 0; i < L_MAX; i++)
	{
		for(int j = 0; j < H_MAX; j++)
		{
			matrice[i][j] = valeur;
		}
	}
}

void ImageB :: setPixel(int x, int y, bool valeur)//ca ne marche pas
{
	if ((x < 0 || x >= L_MAX) && (y < 0 || y >= H_MAX))
	{
		throw XYException("\nErreur de la Largeur et de la Longueur !\n", x, y);
	}

	if (x < 0 || x >= L_MAX)
	{
		throw XYException("\nErreur la Longueur !\n", x);
		
	}

	if (y < 0 || y >= H_MAX)
	{
		throw XYException("\nErreur de la Largeur !\n", y);
	}
	matrice[x][y] = valeur;
}

bool ImageB :: getPixel(int x, int y)const
{

	int Largeur = dimension.getLargeur();
	int Hauteur = dimension.getHauteur();

	if ((x < 0 || x >= Largeur) && (y < 0 || y >= Hauteur))
	{
		throw XYException("\nErreur de la Largeur et de la Longueur !\n", x, y);
	}

	if (x < 0 || x >= Largeur)
	{
		throw XYException("\nErreur la Longueur !\n", x);
		
	}

	if (y < 0 || y >= Hauteur)
	{
		throw XYException("\nErreur de la Largeur !\n", y);
	}

	return matrice[x][y];
}

//////////////////////

void ImageB :: exportToFile(const char *fichier, const char *format)
{
	MyQT::ExportToFile (*this, fichier, format);
}

void ImageB :: Affiche()const
{
	cout << "id : " <<id<< endl;
  cout << "nom : "<<nom<< endl;
  dimension.Affiche();
}

void ImageB :: Dessine()const
{
	MyQT::ViewImage(*this);
}


//surchage//

ImageB &ImageB :: operator =(const ImageB &imageb)
{
	setNom(imageb.nom);
	setId(imageb.id);
	dimension.setLargeur(imageb.getDimension().getLargeur());
	dimension.setHauteur(imageb.getDimension().getHauteur());

	for(int i = 0; i < dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j] = imageb.matrice[i][j];

	return *this;
}

ostream &operator <<(std :: ostream &out, const ImageB &imageb)
{
  out <<"Nom : " << imageb.getNom() << std :: endl;
  out <<"ID : " << imageb.getId() << std :: endl;
  out <<"Largeur : " <<imageb.dimension.getLargeur() << std :: endl;
  out <<"Hauteur : " <<imageb.dimension.getHauteur() << std :: endl;
  return out;
}



//hardcodage//

Couleur ImageB::couleurTrue = Couleur(255,255,255);
Couleur ImageB::couleurFalse = Couleur(0,0,0);
