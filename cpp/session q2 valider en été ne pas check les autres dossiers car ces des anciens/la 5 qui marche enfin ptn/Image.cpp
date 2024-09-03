#include "Image.h"

/*constructeur | destructeur*/
Image :: Image()
{
	cout<<"Constructeur par defaut de Image"<<endl;
	nom = NULL;
	setNom("defaut");
	setId(-1);
}

Image ::~Image()
{
	cout<<"Destructeur par defaut de Image"<<endl;
	if(nom!=NULL);
		delete (nom);
}

Image::Image(int num, const char* pnom)
{
	cout<<"Constructeur d'initialisation Numeroro et Nom de Image"<<endl;
	nom=NULL;
	setNom(pnom);
	setId(num);
}

Image::Image(int num, const char* pnom,const Dimension& dim)
{
	cout<<"Constructeur d'initialisation complet de Image"<<endl;
	nom=NULL;
	setNom(pnom);
	setId(num);
	dimension.setLargeur(dim.getLargeur());
	dimension.setHauteur(dim.getHauteur());

}


Image::Image(const Image& source)
{
	cout<<"Constructeur de copie de Image"<<endl;
	nom=NULL;
	setNom(source.nom);
	setId(source.id);
	dimension.setLargeur(source.dimension.getLargeur());
	dimension.setHauteur(source.dimension.getHauteur());

}

Image:: Image(const char *pnom)
{
	cout<<"Constructeur pour Nom seulement Image"<<endl;
	nom=NULL;
	setNom(pnom);
	setId(0);

}


/*Get | Set */

void Image:: setNom(const char* pnom)
{

	if (nom)
        delete nom;

    nom = new char [strlen(pnom)+1];
    if (strlen(pnom)== 0)
    {
      return;
    }

    strcpy (nom, pnom);
}

void Image::setId(int num)
{
	id =num;

}

void Image::setDimension(const Dimension& dim)
{

	dimension.setLargeur(dim.getLargeur());

	dimension.setHauteur(dim.getHauteur());
}

int Image::getId()const
{
	return id;

}

const char* Image::getNom()const
{
	return nom;

}

Dimension Image::getDimension()const
{
	return dimension;

}






