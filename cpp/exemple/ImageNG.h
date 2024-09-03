#ifndef IMAGENG_H
#define IMAGENG_H
//#include "Dimension.h"
#include "Image.h"

#include <stdlib.h>

class MyQT;

class ImageNG : public Image
{
public:
	static const int L_MAX=640;
	static const int H_MAX=500;

private:
	
	int matrice[L_MAX][H_MAX];

public:
	ImageNG();	//Constructeur par defaut
	~ImageNG()override; //Destructeur par defaut
	ImageNG(int num, const char* pnom);//const init partielle
	ImageNG(int num, const char* pnom,const Dimension& dim);//constructeur d'initialisation complet
	ImageNG(const ImageNG& source);  //constructeur de copie

	ImageNG(const char *pnom); //nouveau constructeur E4

	
	
	void Affiche()const override;

	void setPixel(int x,int y,int val);

	int getPixel(int x,int y)const;

	void setBackground(int val);

	void Dessine()const override;

	void importFromFile(const char* fichier);
	
	void exportToFile(const char* fichier, const char* format)const override;

	int getLuminance()const;

	int getMinimum()const;

	int getMaximum()const;

	float getContraste()const;

	ImageNG& operator=(const ImageNG& d);

	friend ostream& operator<<(ostream& s, const ImageNG& img);

	ImageNG operator+(int p)const;

	ImageNG operator-(int p)const;

	friend ImageNG operator+(int p, const ImageNG& img);

	ImageNG operator++();

	ImageNG operator++(int post );

	ImageNG operator--();

	ImageNG operator--(int post);

	ImageNG operator-(const ImageNG& image);

	bool operator<(const ImageNG& image);

	bool operator>(const ImageNG& image);

	bool operator==(const ImageNG& image);

};

#endif

