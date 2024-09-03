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


///////////operateur/////////:

ostream& operator<<(std::ostream& os, const Dimension& dim)
{
  os << dim.Largeur << "x" << dim.Hauteur;
  return os;
}

istream& operator>>(std::istream& is,Dimension& dim)
{
  is >> dim.Largeur >> dim.Hauteur;
  return is;
}

//tentative operateur comparaison///////////////

// int Dimension::operator==(const Dimension& d)
// {
//  return compD(d)==0;
// }

// int Dimension::operator!=(const Dimension& d)
// {
//  return compD(d)==-1;
// }

// int Dimension::compD(const Dimension& d)
// {
//  if (d.getHauteur=
//  // dates egales
//  return 0;
// }le truc du cours incomprehensible faudra demander aux ordres s'ils ont réussi avec cette methode


bool operator==(Dimension const& objet1, Dimension const& objet2)
{
    
    if (objet1.Hauteur == objet2.Hauteur && objet1.Largeur == objet2.Largeur)
        return true;
    else
        return false;
}


bool operator!=(Dimension const& objet1, Dimension const& objet2)//wtf pourquoi la premiere fois ca n'avait pas marché demaide au prof 
{
    
    if (objet1.Hauteur != objet2.Hauteur || objet1.Largeur != objet2.Largeur)
        return true;
    else
        return false;
}