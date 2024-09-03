#ifndef IMAGEB_H
#define IMAGEB_H

#include "Couleur.h"
#include "Image.h"


class ImageB : public Image
{
	public:
	/*constructeur | destructeur*/
	ImageB();
	ImageB(const ImageB& img);
	ImageB(int num, const char* pnom,const Dimension& dim);
	~ImageB()override;
	

	/*Get | Set */
	void setBackground(bool valeur);

	void setPixel(int x,int y,bool valeur);

	bool getPixel(int x,int y)const;

	//méthode//

	void Affiche()const override;
	void Dessine()const override;

	void exportToFile(const char* fichier,const char* format)const override;

	ImageB& operator=(const ImageB & img);

	friend ostream& operator<<(ostream& s, const ImageB& img);

	static const int L_MAX=640;
	static const int H_MAX=500;
	static Couleur couleurTrue;
	static Couleur couleurFalse;

	private:
	bool matrice[L_MAX][H_MAX];

};






#endif

