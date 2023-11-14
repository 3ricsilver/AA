#ifndef IMAGENG_H //si pas definit on le definit sinon osef car on va boucler
#include "ImageNG.h"
#include <stdlib.h>
#include <iostream>

#include<cstring>


using namespace std;


  ImageNG::ImageNG()//constructeur par defaut
  {
    nom = NULL;//pour pas avoir un probleme de memorie on mallovc
    setNom("default");
    setId(1);
  }
  ImageNG::ImageNG(int i,const char *n)//constructeur par initiation
  {
    nom=NULL;
    setNom(n);
    setId(i);
  }


  ImageNG::ImageNG(const ImageNG& i)// constructeur de copie 
  {
    nom=NULL;
    setNom(i.getNom());
    setId(i.getId());
  }
  ImageNG::~ImageNG()//le destructeur
  {
    if(nom)
      delete nom;
  }




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

int ImageNG::getId() const
{
  return id;
}

const char *ImageNG::getNom() const
{
  return nom;
}

void ImageNG::Affiche() const
{
  cout <<"nom:"<<nom<<" id:"<<id<<endl;
}
#endif
