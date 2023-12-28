#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
#include "Dimension.h"
#include "Image.h"
#include "Couleur.h"
using namespace std;

#ifndef IMAGEB_H
#define IMAGEB_H

class ImageB : public Image
{


private:
	bool matrice[L_MAX][H_MAX];


public:

	//constructeur..
	ImageB();
    ImageB (int Id, const char *Nom);
    ImageB (const ImageB &imageb);
    ImageB (int Id, const char *Nom,const Dimension& d);
    ~ImageB();

    //setter & getter//

	void setBackground(bool valeur);
	void setPixel(int x, int y, bool valeur);
	bool getPixel(int x, int y)const;
	//methide//

    void Affiche() const;
    void Dessine()const;
    void exportToFile(const char* fichier,const char* format);
    //surchage//
	ImageB& operator= (const ImageB &imageb);
    friend std::ostream& operator<< (std::ostream &out,const ImageB &imageb);


	//hardcodage//
	static const int L_MAX = 700;
	static const int H_MAX = 700;

	static Couleur couleurTrue;
	static Couleur couleurFalse;

};

#endif


