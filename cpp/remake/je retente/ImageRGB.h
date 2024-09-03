#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
#include "Dimension.h"
#include "Image.h"
using namespace std;

#ifndef IMAGERGB_H
#define IMAGERGB_H

#include "Couleur.h"
class MyQT;
class ImageRGB : public Image
{
public:
	static const int L_MAX = 700;
	static const int H_MAX = 700;

private:
	Couleur matrice[L_MAX][H_MAX];
	
public:
	//constructeur//
	ImageRGB();
    ImageRGB (int Id, const char *Nom);
    ImageRGB (const ImageRGB &imagergb);
    ImageRGB (int Id, const char *Nom,const Dimension& d);
    ImageRGB (const char *fichier);
    ~ImageRGB();
    
    //Méthode//
    void Affiche() const;
    void Dessine()const;

    //setter et getter//
	void setBackground(const Couleur &valeur);
	void setPixel(int x, int y, const Couleur &valeur);
	Couleur getPixel(int x, int y)const;
	ImageRGB& operator= (const ImageRGB &imagergb);
    

    friend std::ostream& operator<< (std::ostream &out,const ImageRGB &imagergb);
	void exportToFile(const char* fichier,const char* format);
    void importFromFile(const char* fichier);
};

#endif


