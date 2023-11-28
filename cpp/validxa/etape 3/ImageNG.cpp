
#include "ImageNG.h"
#include <stdlib.h>
#include <iostream>
#include "MyQT.h"
#include<cstring>

//partie 2test//
///home/student/AA/LaboCpp2023_Enonce/MyQT.h
using namespace std;

  //constructeur par defaut////////////////////////////////////
  ImageNG::ImageNG()
  {
    nom = NULL;//pour pas avoir un probleme de memorie on mallovc
    setNom("default");
    setId(1);
    //setDimension(d);
    setBackground(0);
  }

  //constructeur par initiation/////////////////////
  ImageNG::ImageNG(int i,const char *n)
  {
    nom=NULL;
    setNom(n);
    setId(i);
    setBackground(0);
  }

    ImageNG::ImageNG(int i,const char *n,const Dimension &d)
  {
    nom=NULL;
    setNom(n);
    setId(i);
    setDimension(d);
    setBackground(0);
  }


  // constructeur de copie /////////////////
  ImageNG::ImageNG(const ImageNG& image)
  {
    nom=NULL;
    setNom(image.getNom());
    setId(image.getId());
    setDimension(image.getDimension());//pour faire copie parfaite  car avant cloner tout sauf dimension
    for(int i=0;i<d.getLargeur();i++)
    {
      for(int j=0;j<d.getHauteur();j++)
      {
        matrice[i][j]=image.matrice[i][j];
      }
    }
  }
  //le destructeur////////////////////
  ImageNG::~ImageNG()
  {
    if(nom)
      delete nom;
  }



 ///////////setter///////////////////
void ImageNG::setId(int val)
{
  if(val<0)
    return;
  id=val;
}

void ImageNG::setNom(const char *n)
{
  if(nom)
    delete nom;
  nom=new char [strlen(n)+1];
  strcpy(nom,n);
}
//test 2 essai

void ImageNG::setDimension(const Dimension &dimension)
{
  if(dimension.getHauteur() > H_MAX)
  {
    d.setHauteur(H_MAX);
  }
  else
  {
    d.setHauteur(dimension.getHauteur());
  }
  if(dimension.getLargeur()>L_MAX)
  {
    d.setLargeur(L_MAX);
  }
  else 
  {
    d.setLargeur(dimension.getLargeur());
  }
  
}
//////////////////getter////////////////////////

int ImageNG::getId() const
{
  return id;
}

const char *ImageNG::getNom() const
{
  return nom;
}

Dimension ImageNG::getDimension()const
{
  return d;
}
////////////////Affiche///////////////

void ImageNG::Affiche() const
{
  cout <<"nom:"<<nom<<" id:"<<id<<"Dimension:"<< endl;
  d.Affiche();
}


////test 3 //////////////
void ImageNG::setPixel(int xpixel,int ypixel,int valpixel)
{
  matrice[xpixel][ypixel]=valpixel;

}

int ImageNG::getPixel(int x,int y) const
{
  return matrice[x][y];
}

void ImageNG::setBackground(int val)
{
  // for(int i=0;i<d.getLargeur();i++)
  // {
  //   for (int j = 0; j <d.getHauteur(); j++)
  //   {
  //     matrice[i][j]=val;
  //   }
  // }
  for(int i=0;i<H_MAX;i++)//ca marchera pas si image plus petit que 500 et superieur 500
  {
    for (int j = 0; j <L_MAX; j++)
    {
      matrice[i][j]=val;
    }
  }
}


void ImageNG::Dessine()const
{
   MyQT::ViewImage(*this);
}  
void ImageNG::importFromFile(const char* fichier)
{
  MyQT::ImportFromFile(*this,fichier);
}

void ImageNG::exportToFile(const char* fichier, const char* format)
{
  MyQT::ExportToFile(*this,fichier,format);
}
