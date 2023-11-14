
#ifndef IMAGENG_H
#define IMAGENG_H

/////test 2/////////
#include "Dimension.h"
////////////////////
class MyQt;//pour dire qu'on va le


class ImageNG
{
	public:

				//test 3//
		static const int L_MAX=500;
  		static const int H_MAX=500;
  		
		ImageNG();
		ImageNG(int i,const char *n);
		ImageNG(int i,const char *n,const Dimension &d);

		ImageNG(const ImageNG& i);
		~ImageNG();
		void setId(int val);
		void setNom(const char *n);
		int getId()const;
		const char *getNom() const;
		void Affiche() const;




		Dimension getDimension()const;
		void setDimension(const Dimension &d);

		void setPixel(int x,int y,int val);
		int getPixel(int x,int y)const;

		void setBackground(int val);

		void Dessine()const;

		void importFromFile(const char* fichier);
		void exportToFile(const char* fichier, const char* format) ;
	private:
		int id;
  		char *nom;
  		//test 2//

  		Dimension d;

  		//////////

  		//test 3 //

  		
  		int matrice[L_MAX][H_MAX];

  		//pixel//




};


#endif