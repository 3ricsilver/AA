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

	/*constructeur | destructeur*/
	Image();
	Image(const char *pnom);
	Image(int num, const char* pnom);
	Image(int num, const char* pnom,const Dimension& dim);
	Image(const Image& source);

	virtual ~Image();

	/*Get | Set */
	void setId(int num);

	void setNom(const char *pnom);

	void setDimension(const Dimension& dim);

	Dimension getDimension()const;

	int getId()const;

	const char* getNom()const;

	/*héritage*/
	//virtual pure eric futur
	virtual void Affiche()const =0;
	virtual void Dessine()const =0;
	virtual void exportToFile(const char* fichier,const char* format)const =0;

};



 
#endif


