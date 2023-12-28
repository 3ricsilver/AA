#include "ImageRGB.h"
#include "MyQT.h"
#include <iostream>
using namespace std;


//constructeru//

ImageRGB :: ImageRGB(): Image()
{
	for(int i = 0; i< dimension.getLargeur(); i++)
	{
		for(int j = 0; j < dimension.getHauteur(); j++)
		{
			matrice[i][j];
		}
	}
}

ImageRGB :: ImageRGB(int Id, const char *nom): Image(Id, nom)
{
	for(int i = 0; i< dimension.getLargeur(); i++)
	{
		for(int j = 0; j < dimension.getHauteur(); j++)
		{
			matrice[i][j];
		}
	}
}

ImageRGB :: ImageRGB (const ImageRGB &imagergb): Image(imagergb)
{
	setDimension(imagergb.getDimension());

	for(int i = 0; i< dimension.getLargeur(); i++)
	{
		for(int j = 0; j < dimension.getHauteur(); j++)
		{
			matrice[i][j] = imagergb.matrice[i][j];
		}
	}
}

ImageRGB :: ImageRGB (int Id, const char *Nom, const Dimension &d) : Image(Id, Nom, d)
{
	for(int i = 0; i< dimension.getLargeur(); i++)
	{
		for(int j = 0; j < dimension.getHauteur(); j++)
		{
			matrice[i][j];
		}
	}
}

ImageRGB :: ImageRGB (const char *fichier)
{
	nom = NULL;
	setNom(fichier);
	setId(0);
	MyQT::ImportFromFile(*this, fichier);
}

//destructeur//

ImageRGB :: ~ImageRGB()
{

}


//methode//

void ImageRGB :: Affiche()const
{
		cout << "id : " <<id<< endl;
    cout << "nom : "<<nom<< endl;
    dimension.Affiche();
}

void ImageRGB :: Dessine()const
{
	MyQT::ViewImage(*this);
}

void ImageRGB :: exportToFile(const char *fichier, const char *format)
{
	MyQT::ExportToFile (*this, fichier, format);
}

void ImageRGB :: importFromFile(const char *fichier)
{
	MyQT::ImportFromFile(*this, fichier);
}

//setter && getter //


void ImageRGB :: setBackground(const Couleur &valeur)
{
	for(int i = 0; i < L_MAX; i++)
	{
		for(int j = 0; j < H_MAX; j++)
		{
			matrice[i][j] = valeur;
		}
	}
}

void ImageRGB :: setPixel(int x, int y, const Couleur &valeur)
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



Couleur ImageRGB :: getPixel(int x, int y)const
{
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
}

//surcharge//


ImageRGB &ImageRGB :: operator =(const ImageRGB &imagergb)
{
	setNom(imagergb.nom);
	setId(imagergb.id);
	dimension.setLargeur(imagergb.getDimension().getLargeur());
	dimension.setHauteur(imagergb.getDimension().getHauteur());

	for(int i = 0; i < dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j] = imagergb.matrice[i][j];

	return *this;
}

ostream &operator <<(std :: ostream &out, const ImageRGB &imagergb)
{
  out <<"Nom : " << imagergb.getNom() << std :: endl;
  out <<"ID : " << imagergb.getId() << std :: endl;
  out <<"Largeur : " <<imagergb.dimension.getLargeur() << std :: endl;
  out <<"Hauteur : " <<imagergb.dimension.getHauteur() << std :: endl;
  return out;
}




















