#include "Image.h"
#include <string.h>

//CONSTRUCTEUR//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*PAR DEFAUT*/
Image::Image()
{
	nom=NULL;
	setNom("Default");
	setId(1);
}

/*Le reste */

Image::Image(int Id,const char *Nom)
{
	nom=NULL;
	setNom(Nom);
	setId(Id);
}

Image::Image(int Id,const char *Nom,const Dimension &d)
{
	nom=NULL;
	setNom(Nom);
	setId(Id);
	setDimension(d);
}

Image::Image(const Image &image)
{
	nom=NULL;
	setId(image.getId());
	setNom(image.getNom());
	setDimension(image.getDimension());
}

//Destructeur //////////////////////////////////////

Image::~Image()
{
	if(nom)
	{
		delete nom;
	}
}

//getter/////////////////////////////////////////////

int Image::getId()const
{
	return id;
}



const char* Image ::getNom()const
{
	return nom;
}

Dimension Image::getDimension()const
{
  return d;
}

///setter//////////////////////////////////////////////////

void Image::setId(int val)
{
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

  if(dimension.getLargeur()>L_MAX)
  {
    d.setLargeur(L_MAX);
  }
  else 
  {
    d.setLargeur(dimension.getLargeur());
  }

  if(dimension.getHauteur() > H_MAX)
  {
    d.setHauteur(H_MAX);
  }
  else
  {
    d.setHauteur(dimension.getHauteur());
  }
}