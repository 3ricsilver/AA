#ifndef IMAGE_H
#define IMAGE_H
#include "Dimension.h"

#include <cstring>

class Image
{
protected:
	int id;
	char* nom;
	Dimension dimension;

public:

	virtual void Affiche()const =0;
	virtual void Dessine()const =0;
	virtual void exportToFile(const char* fichier,const char* format)const =0;

	Image();	//Constructeur par defaut
	virtual ~Image(); //Destructeur par defaut
	Image(int num, const char* pnom);//const init partielle
	Image(int num, const char* pnom,const Dimension& dim);//constructeur d'initialisation complet
	Image(const Image& source);  //constructeur de copie

	Image(const char *pnom); //nouveau constructeur E4

	void setId(int num);

	void setNom(const char *pnom);

	void setDimension(const Dimension& dim);

	Dimension getDimension()const;

	int getId()const;

	const char* getNom()const;

};



 
#endif


