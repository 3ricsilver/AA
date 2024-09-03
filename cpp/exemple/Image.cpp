#include "Image.h"


Image :: Image():nom(nullptr)
{
	#ifdef DEBUG
	cout<<"Constructeur par defaut de ImageNG"<<endl;
	#endif

	setNom("defaut");

	setId(-1);


}

Image ::~Image()
{
	#ifdef DEBUG
	cout<<"Destructeur par defaut de ImageNG"<<endl;
	#endif

	if(nom!=NULL);
		free(nom);


	cout<< "Destructeur de ImageNG"<<endl;
}

Image::Image(int num, const char* pnom)
{
	#ifdef DEBUG
	cout<<"Constructeur d'initialisation partielle de ImageNG"<<endl;
	#endif

	setId(num);
	nom=NULL;

	setNom(pnom);

}

Image::Image(int num, const char* pnom,const Dimension& dim)
{
	#ifdef DEBUG
	cout<<"Constructeur d'initialisation complet de ImageNG"<<endl;
	#endif

	setId(num);
	nom=NULL;

	setNom(pnom);

	dimension.setLargeur(dim.getLargeur());
	dimension.setHauteur(dim.getHauteur());

}


Image::Image(const Image& source)
{
	#ifdef DEBUG
	cout<<"Constructeur de copie de ImageNG"<<endl;
	#endif

	nom=NULL;
	setNom(source.nom);

	setId(source.id);

	dimension.setLargeur(source.dimension.getLargeur());
	dimension.setHauteur(source.dimension.getHauteur());

}

Image:: Image(const char *pnom):nom(nullptr)
{
	#ifdef DEBUG
	cout<<"Nouveau Constructeur pour les images"<<endl;
	#endif

	setNom(pnom);
	setId(0);

}

void Image:: setNom(const char* pnom)
{
	// if(nom!=NULL)
	// {
	// 	free(nom);
	// }

 //  int taille=strlen(pnom);
 //  nom=(char *)malloc(taille + 1);
 //  strcpy(nom,pnom);

	if(nom) delete[]nom;
	nom= new char[strlen(pnom)+1];
	strcpy(nom,pnom);

	
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






