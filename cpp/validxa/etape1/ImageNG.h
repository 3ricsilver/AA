#ifndef IMAGENG_H //si pas definit on le definit sinon osef car on va boucler
#define IMAGENG_H
/////test 2/////////
#include "Dimension.h"
////////////////////
class ImageNG
{
	private:
		int id;
  		char *nom;
  		//test 2//

  		Dimension d;

  		//////////
	public:
		ImageNG();
		ImageNG(int i,const char *n);
		ImageNG(const ImageNG& i);
		~ImageNG();
		void setId(int val);
		void setNom(const char *n);
		int getId()const;
		const char *getNom() const;
		void Affiche() const;



		///Test 2////////////////////////
		Dimension dimension;//modif pour le test 2
		void setDimension(Dimension Hauteur,Dimension Largeur);
		void getDimension()const;
};

#endif
