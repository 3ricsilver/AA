#include "ImageRGB.h"
#include "MyQT.h"
#include <iostream>
using namespace std;

ImageRGB::ImageRGB():Image()
{
  for(int i=0;i<H_MAX;i++)
  {
    for (int j = 0; j <L_MAX; j++)
    {
      matrice[i][j];
    }
  }
}
//le reste//
ImageRGB::ImageRGB(int id, const char* nom):Image(id,nom)
{
  for(int i=0;i<H_MAX;i++)
  {
    for (int j = 0; j <L_MAX; j++)
    {
      matrice[i][j];
    }
  }
}
ImageRGB::ImageRGB(int id, const char* nom, const Dimension& d):Image(id,nom,d)
{
  for(int i=0;i<H_MAX;i++)
  {
    for (int j = 0; j <L_MAX; j++)
    {
      matrice[i][j];
    }
  }
}
//copie//
ImageRGB::ImageRGB(const ImageRGB& image):Image(image)
{
  for(int i=0;i<H_MAX;i++)
  {
    for (int j = 0; j <L_MAX; j++)
    {
      matrice[i][j]=image.matrice[i][j];
    }
  }
}

ImageRGB::ImageRGB(const char *fichier)
{
    nom=NULL;
    setNom(FichierImage);
    setId(0);
    MyQT::ImportFromFile(*this,FichierImage);
}
//destructeur//
ImageRGB::~ImageRGB()//image le fait déja donc faut rien faire eric fuutur
{
    //héritage
}

//setter//
void ImageRGB::setPixel(int x,int y,const Couleur& valeur)
{
  matrice[y][x] = valeur;
}

void ImageRGB::setBackground(const Couleur& valeur)
{
  for(int i=0;i<H_MAX;i++)
  {
    for (int j = 0; j <L_MAX; j++)
    {
      matrice[i][j] = valeur;
    }
  }
}


//getter// 
Couleur ImageRGB::getPixel(int x,int y) 
{
    return matrice[y][x];
}


//methode//

//opérateur//
ostream& operator <<(std::ostream &out,const ImageRGB& imagergb)
{
    //todo
}
ImageRGB& ImageRGB::operator=(const ImageRGB &imagergb)
{
    //todo
}
//héritage::

void ImageRGB::Dessine()const
{
    MyQT::ViewImage(*this);
}
void ImageRGB::importFromFile(const char* fichier)
{
    MyQT::ImportFromFile(*this,fichier);
}
void ImageRGB::exportToFile(const char* fichier, const char* format) 
{
    MyQT::ExportToFile(*this,fichier,format);
}

void ImageRGB::affiche() const
{
  cout <<"nom:"<<nom<<" id:"<<id<<"Dimension:"<< endl;
  d.Affiche();
}