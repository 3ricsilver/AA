#include "Dimension.h"
#include <stdlib.h>
#include <iostream>

#include<cstring>
using namespace std;

    // Dimensions standard statiques
  const Dimension Dimension::VGA(640, 480);
  const Dimension Dimension::HD(1280, 720);
  const Dimension Dimension::FULL_HD(1920, 1080);


  Dimension::Dimension()//constructeur par defaut
  {
    
    setHauteur(400);
    setLargeur(300);


  }

  Dimension::Dimension(int Hauteur,int Largeur)//constructeur par defaut
  {
    setLargeur(Largeur);
    setHauteur(Hauteur);
  }
  Dimension::Dimension(const Dimension& i)// constructeur de copie 
  {
    setLargeur(i.Largeur);
    setHauteur(i.Hauteur);
  }
  Dimension::~Dimension()//le destructeur
  {
  	cout <<"passage destructeur"<<endl;


  }

void Dimension::setLargeur(int val)
{
  if(val<0)
    return;
  Largeur=val;
}

void Dimension::setHauteur(int val)
{
  if(val<0)
    return;
  Hauteur=val;
}

int Dimension::getLargeur() const
{
  return Largeur;
}

int Dimension::getHauteur() const
{
  return Hauteur;
}

void Dimension::Affiche() const
{
  cout <<"Hauteur"<<Hauteur<<"Largeur"<<Largeur<<endl;
}
