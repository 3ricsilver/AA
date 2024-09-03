#include "ImageNG.h"
#include "MyQT.h"
#include <iostream>
#include <string.h>

using namespace std;



/*CONSTRUCTEUR ET DESTRUCTEUR*/


ImageNG::ImageNG() : Image()  
{
  setBackground(0);

  cout << "Constructeur par défaut ImageNG" << endl;
}


ImageNG::ImageNG(int id, const char* N) : Image(id, N)  
{
  setBackground(0);

  cout << "Constructeur avec Argument ImageN-" << endl;
}

ImageNG::ImageNG(const ImageNG& image1) : Image(image1) 
{
  for(int i = 0; i < dimension.getLargeur(); i++)
    for(int j = 0; j < dimension.getHauteur(); j++) matrice[i][j] = image1.matrice[i][j];

  cout << "Constructeur de copie ImageNG" << endl;
}

ImageNG::ImageNG(int id, const char* N, const Dimension& dim) : Image(id, N, dim) 
{
  setBackground(0);

  cout << "Constructeur avec Argument ImageNG" << endl;
}

ImageNG::ImageNG(const char* fichier) : Image(fichier)
{
  importFromFile(fichier);

  cout << "Constructeur avec fichier ImageNG" << endl;
}


ImageNG::~ImageNG() 
{
  cout << "Passage du destructeur ImageNG" << endl;
}

/* SETTERS ET GETTERS*/


void ImageNG::setBackground(int val)
{
  if(val < 0) return; 
  
  for(int i = 0; i < L_MAX; i++)
  {
    for(int j = 0; j < H_MAX; j++) matrice[i][j] = val; // je mets tous les pixels au meme niveau de gris
  }
}

void ImageNG::setPixel(int x, int y, int val)
{
  if (x < 0) return;
  if (y < 0) return;
  if (val < 0) return;

  matrice[x][y] = val; // je donne un niveau de gris à un pixel précis de la matrice
}

int ImageNG::getPixel(int x, int y) const
{
  return matrice[x][y]; // je retourne le niveau de gris du pixel
}

int ImageNG::getLuminance() const
 {
  int somme = 0, moyenne = 0;

  for(int i = 0; i<dimension.getHauteur(); i++)
  {
    for(int j = 0; j<dimension.getLargeur(); j++) somme = somme + matrice[i][j];
  }

  moyenne = somme / (dimension.getHauteur() * dimension.getLargeur());

  return moyenne;
 }

int ImageNG::getMinimum() const
 {
  int minimum = 255;

  for(int i = 0; i<dimension.getHauteur(); i++)
  {
    for(int j = 0; j<dimension.getLargeur(); j++)
      {
        if(minimum > matrice[i][j]) minimum = matrice[i][j];
      }
  }

  return minimum;
 }

int ImageNG::getMaximum() const
 {
  int maximum = 0;

  for(int i = 0; i<dimension.getHauteur(); i++)
  {
    for(int j = 0; j<dimension.getLargeur(); j++)
    {
      if(maximum < matrice[i][j]) maximum = matrice[i][j];
    }
  }

  return maximum;
 }

float ImageNG::getContraste() const
{
  float contraste = 0;

  contraste = (float)(getMaximum()-getMinimum()) / (float)(getMaximum()+getMinimum());

  return contraste;
}



/* METHODE*/


void ImageNG::Affiche() const
{
  cout << "Nom : " << getNom() << endl;
  cout << "ID : " << getId() << endl;
  dimension.Affiche();
}

void ImageNG::Dessine() const
{
  MyQT::ViewImage(*this);
}

void ImageNG::importFromFile(const char* fichier) 
{
  MyQT::ImportFromFile(*this, fichier);
}

void ImageNG::exportToFile(const char* fichier, const char* format)
{
  MyQT::ExportToFile(*this, fichier, format);
}



/* METHODE AVEC Surchages DES OPERATEURS*/


ImageNG& ImageNG::operator=(const ImageNG& image) // on return une reference d'un objet
{
  setNom(image.nom);
  setId(image.id);
  dimension.setHauteur(image.dimension.getHauteur());
  dimension.setLargeur(image.dimension.getLargeur());

  for(int i = 0; i < dimension.getLargeur(); i++)
  {
    for(int j = 0; j < dimension.getHauteur(); j++) matrice[i][j] = image.matrice[i][j];
  }

  return(*this);
}

ImageNG ImageNG::operator+(int val)
{
  ImageNG imageNEW(*this);
  
    for(int i = 0; i < imageNEW.dimension.getLargeur(); i++)
    {
      for(int j = 0; j < imageNEW.dimension.getHauteur(); j++) 
        {
          imageNEW.matrice[i][j] = imageNEW.matrice[i][j] + val;
          if(imageNEW.matrice[i][j] > 255) imageNEW.matrice[i][j] = 255;
          if(imageNEW.matrice[i][j] < 0) imageNEW.matrice[i][j] = 0;
        }
    }
  
  return imageNEW;
}

ImageNG operator+(int val, ImageNG image) // fonction amie
{
  return image + val;
}

ImageNG ImageNG::operator-(int val)
{
  ImageNG imageNEW(*this);

  for(int i = 0; i < imageNEW.dimension.getLargeur(); i++)
  {
    for(int j = 0; j < imageNEW.dimension.getHauteur(); j++) 
      {
        imageNEW.matrice[i][j] = imageNEW.matrice[i][j] - val;
        if(imageNEW.matrice[i][j] < 0) imageNEW.matrice[i][j] = 0;
      }
  }

  return imageNEW;
}

ImageNG ImageNG::operator-(const ImageNG& image)
{
  ImageNG imageNEW(*this);

  for(int i = 0; i < imageNEW.dimension.getLargeur(); i++)
  {
    for(int j = 0; j < imageNEW.dimension.getHauteur(); j++) 
      {
        imageNEW.matrice[i][j] = imageNEW.matrice[i][j] - image.matrice[i][j];
        if(imageNEW.matrice[i][j] < 0) imageNEW.matrice[i][j] = 0;
      }
  }

  return imageNEW;
}

ImageNG ImageNG::operator++() // pré-incrémentation
{
  (*this) = (*this) + 20; 

  return (*this);
}

ImageNG ImageNG::operator++(int AucuneVal) // post-incrémentation
{
  ImageNG temp(*this); // copie de l’objet courant
  (*this) = (*this) + 20;

  return temp;
}

ImageNG ImageNG::operator--() // pré-décrémentation
{
  (*this) = (*this) - 20; 

  return (*this);
}

ImageNG ImageNG::operator--(int AucuneVal) // post-décrémentation
{
  ImageNG temp(*this); // copie de l’objet courant
  (*this) = (*this) - 20;

  return temp;
}

bool ImageNG::operator<(const ImageNG& image) const 
{
    for (int i = 0; i < dimension.getLargeur(); i++) 
    {
        for (int j = 0; j < dimension.getHauteur(); j++) 
        {
            if (matrice[i][j] >= image.matrice[i][j]) return false; // Si au moins un pixel n'est pas <, l'image n'est pas < que l'autre
        }
    }
    return true; // Tous les pixels sont <
}

bool ImageNG::operator>(const ImageNG& image) const 
{
    for (int i = 0; i < dimension.getLargeur(); i++) 
    {
        for (int j = 0; j < dimension.getHauteur(); j++) 
        {
            if (matrice[i][j] <= image.matrice[i][j]) return false; // Si au moins un pixel n'est pas >, l'image n'est pas > que l'autre
        }
    }
    return true; // Tous les pixels sont >
}

bool ImageNG::operator==(const ImageNG& image) const 
{  
    for (int i = 0; i < dimension.getLargeur(); ++i) 
    {
        for (int j = 0; j < dimension.getHauteur(); ++j) 
        {
            if (matrice[i][j] != image.matrice[i][j]) return false; // Si au moins un pixel est différent, les images ne sont pas égales
        }
    }
    return true; // Tous les pixels sont égaux
}

ostream& operator<<(ostream& s,const ImageNG& image)
{
 s << "nom : " << image.nom << " | id : " << image.id  << " | dimension : " << image.dimension.getHauteur() << "/" << image.dimension.getLargeur() << " | Luminance : " << image.getLuminance() << " | Contraste : " << image.getContraste() << endl;

 return s;
}
