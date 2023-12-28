
#include "Image.h"
#include <stdlib.h>
#include <iostream>
#include "MyQT.h"
#include<cstring>

using namespace std;

//constructeur

Image::Image()
{
  nom = NULL;//pour pas avoir un probleme de memorie on mallovc
  setNom("default");
  setId(1);

}

Image::Image(int i,const char *n)
{
  nom=NULL;
  setNom(n);
  setId(i);

}

Image::Image(int i,const char *n,const Dimension &d)
{
  nom=NULL;
  setId(i);
  setNom(n);
  setDimension(d);

}
//pour recup les foto
Image::Image(const char* cheminFichierPhoto): id(0),nom(nullptr)//initialise
{
	setNom(cheminFichierPhoto);
	setId(id);


}


Image::Image(const Image& i)
{
    nom=NULL;
    setNom(i.getNom());
    setId(i.getId());
    setDimension(i.getDimension());//pour faire copie parfaite  car avant cloner tout sauf dimension

}


//destructeur////


Image::~Image()
{
    if(nom)
      delete nom;
}



// setter

void Image::setId(int val)
{
  if(val<0)
    return;
  id=val;
}

void Image::setNom(const char *n)
{
  if(nom)
    delete nom;
  nom=new char [strlen(n)+1];
  strcpy(nom,n);
}

void Image::setDimension(const Dimension &dimension)
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

int Image::getId() const
{
  return id;
}

const char *Image::getNom() const
{
  return nom;
}

Dimension Image::getDimension()const
{
  return d;
}