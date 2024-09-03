#ifndef IMAGEB_H
#define IMAGEB_H

#include "Couleur.h"
#include "Image.h"


class ImageB : public Image
{
	friend ostream& operator<<(ostream& s, const ImageB& img);

	public:

	static const int L_MAX=640;
	static const int H_MAX=500;
	private:
	bool matrice[L_MAX][H_MAX];

	public:
	ImageB();
	~ImageB()override;

	ImageB(const ImageB& img);
	ImageB(int num, const char* pnom,const Dimension& dim);
	
	static Couleur couleurTrue;
	static Couleur couleurFalse;

	void Affiche()const override;
	void Dessine()const override;

	void setBackground(bool valeur);

	void setPixel(int x,int y,bool valeur);

	bool getPixel(int x,int y)const;


	void exportToFile(const char* fichier,const char* format)const override;

	ImageB& operator=(const ImageB & img);

};






#endif

