#include "Image.h"

//constructeur//

Image :: Image()
{
	nom = NULL;
    setNom ("Default");
    setId (1);
}

Image ::Image (int Id, const char *Nom) 
{
    nom = NULL;
    setNom (Nom);
    setId (Id);
}

Image ::Image (int Id, const char *Nom, const Dimension& d) 
{
    nom = NULL;
    setNom (Nom);
    setId (Id);
    setDimension(d);
}

Image ::Image (const Image &image)
{
  	nom = NULL;
    setId (image.getId());
    setNom (image.getNom());
    setDimension(image.getDimension());
}

//destructeur//

Image::~Image()
{ 
	if(nom)
        delete nom;
}


////////////////

int Image :: getId() const
{
	return id;
}

void Image :: setId (int val)
{

	if (val >= 0)
      
        id = val;  
	
}

const char * Image :: getNom() const
{
  return nom;
}

void Image :: setNom (const char *n)
{

	if (nom)
        delete nom;
      nom = new char [strlen(n)+1];
      if (strlen(n)== 0)
      {
        return;
      }

      strcpy (nom, n);

}


Dimension Image::getDimension() const
{
  return dimension;
}

void Image::setDimension(const Dimension& d)
{
  dimension.setLargeur(d.getLargeur());

  dimension.setHauteur(d.getHauteur());
    
}

