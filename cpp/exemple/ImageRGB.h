#ifndef IMAGERGB_H
#define IMAGERGB_H
#include "Couleur.h"
#include "Image.h"


#include <stdlib.h>




class ImageRGB :public Image
{
friend ostream& operator<<(ostream& s, const ImageRGB& img);
public:
	static const int L_MAX=640;
	static const int H_MAX=500;

private:

	Couleur matrice[L_MAX][H_MAX];
	

public:
	ImageRGB();
	~ImageRGB()override;
	ImageRGB(const ImageRGB& img);
	ImageRGB(int num, const char* pnom,const Dimension& dim);

	void Affiche()const override;
	void Dessine()const override;

	void setBackground(const Couleur& valeur);

	void setPixel(int x,int y,const Couleur& valeur);

	Couleur getPixel(int x,int y)const;

	void importFromFile(const char* fichier);
	void exportToFile(const char* fichier, const char* format)const override;

	ImageRGB& operator=(const ImageRGB& img);

	
	
};



#endif