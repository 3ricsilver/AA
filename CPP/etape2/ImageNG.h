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
		ImageNG(int i,const char *n,const Dimension &d);

		ImageNG(const ImageNG& i);
		~ImageNG();
		void setId(int val);
		void setNom(const char *n);
		int getId()const;
		const char *getNom() const;
		void Affiche() const;



		///Test 2///////////////////////
		//void setDimension(int Hauteur,int Largeur);// avant j'avais fait Dimension a la place de int a modifier 
		Dimension getDimension()const;
		void setDimension(const Dimension &d);
};


