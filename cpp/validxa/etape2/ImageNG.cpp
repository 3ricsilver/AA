
#include "ImageNG.h"
#include <stdlib.h>
#include <iostream>

#include<cstring>

//partie 2test//
//
using namespace std;

  //constructeur par defaut////////////////////////////////////
  ImageNG::ImageNG()
  {
    nom = NULL;//pour pas avoir un probleme de memorie on mallovc
    setNom("default");
    setId(1);
    //setDimension(d);
  }

  //constructeur par initiation/////////////////////
  ImageNG::ImageNG(int i,const char *n)
  {
    nom=NULL;
    setNom(n);
    setId(i);
    
  }

    ImageNG::ImageNG(int i,const char *n,const Dimension &d)
  {
    nom=NULL;
    setNom(n);
    setId(i);
    setDimension(d);
  }


  // constructeur de copie /////////////////
  ImageNG::ImageNG(const ImageNG& i)
  {
    nom=NULL;
    setNom(i.getNom());
    setId(i.getId());
    setDimension(i.getDimension())//pour faire copie parfaite  car avant cloner tout sauf dimension
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
  d = dimension;
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








///////Test 2//////////////////


