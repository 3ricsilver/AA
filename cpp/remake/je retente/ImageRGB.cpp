#include "ImageRGB.h"
#include "MyQT.h"
#include <iostream>
using namespace std;

ImageRGB :: ImageRGB(): Image()
{
  for(int i = 0; i< dimension.getLargeur(); i++)
    for(int j = 0; j < dimension.getHauteur(); j++)
      matrice[i][j];
  cout << "--Constructeur par défaut ImageRGB" << endl;
}

ImageRGB :: ImageRGB(int Id, const char *nom): Image(Id, nom)
{
  for(int i = 0; i< dimension.getLargeur(); i++)
    for(int j = 0; j < dimension.getHauteur(); j++)
      matrice[i][j];
  cout << "-- Constructeur ImageRGB avec comme argument Id: " << Id << ", Nom: " << nom << std::endl;
}

ImageRGB :: ImageRGB (const ImageRGB &imagergb): Image(imagergb)
{
  setDimension(imagergb.getDimension());

  for(int i = 0; i< dimension.getLargeur(); i++)
    for(int j = 0; j < dimension.getHauteur(); j++)
      matrice[i][j] = imagergb.matrice[i][j];

  cout << "--Constructeur par copie ImageRGB" << endl;
}

ImageRGB :: ImageRGB (int Id, const char *Nom, const Dimension &d) : Image(Id, Nom, d)
{
  for(int i = 0; i< dimension.getLargeur(); i++)
    for(int j = 0; j < dimension.getHauteur(); j++)
      matrice[i][j];
  cout << "-- Constructeur ImageRGB avec comme argument Id: " << Id << ", Nom: " << Nom <<",Dimension:"<< d <<std::endl;
}

ImageRGB :: ImageRGB (const char *fichier)
{
  nom = NULL;
  setNom(fichier);
  setId(0);
  MyQT::ImportFromFile(*this, fichier);
  cout << "--Constructeur par fichier ImageRGB" << endl;

}

ImageRGB :: ~ImageRGB()
{
  cout << "Destructeur ImageRGB ps:il fait rien mais c drole" << endl;

}

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

void ImageRGB :: setBackground(const Couleur &valeur)
{
  for(int i = 0; i < L_MAX; i++)
    for(int j = 0; j < H_MAX; j++)
      matrice[i][j] = valeur;
}

void ImageRGB :: setPixel(int x, int y, const Couleur &valeur)
{
  if (x < 0)
    return;

  if (y < 0)
    return;

  matrice[x][y] = valeur;
}

Couleur ImageRGB :: getPixel(int x, int y)const
{
  return matrice[x][y];
}

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

void ImageRGB :: exportToFile(const char *fichier, const char *format)
{
  MyQT::ExportToFile (*this, fichier, format);
}

void ImageRGB :: importFromFile(const char *fichier)
{
  MyQT::ImportFromFile(*this, fichier);
}






































