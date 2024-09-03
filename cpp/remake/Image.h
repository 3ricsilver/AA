#include <stdlib.h>
#include <iostream>
#include "Dimension.h"
#include <cstring>

using namespace std;

#ifndef IMAGE_H
#define IMAGE_H

class MyQT;

class Image
{
	
	
	protected:


		int id;
    	char *nom;
    	Dimension dimension;

    public:

    	/////////constructeur///////
    	Image();
    	Image (int Id, const char *Nom);
    	Image (const Image &image);
    	Image (int Id, const char *Nom,const Dimension& d);
    	
    	virtual ~Image();

    	//////////////////
    	int getId() const; 
    	void setId (int val);
    	const char *getNom() const;
    	void setNom (const char *n);
    	Dimension getDimension() const;
    	void setDimension(const Dimension& d);


    	//héritage //virtual pure eric futur
    	virtual void Affiche() const = 0;
    	virtual void Dessine()const = 0;
    	virtual void exportToFile(const char* fichier,const char* format) = 0;


    	//hardcoadage//

    	static const int L_MAX = 700;
   		static const int H_MAX = 700;
};

#endif