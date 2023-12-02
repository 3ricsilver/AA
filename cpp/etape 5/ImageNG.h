
#ifndef IMAGENG_H
#define IMAGENG_H

/////test 2/////////
#include "Dimension.h"
#include "Image.h"

#include "MyQT.h"
////////////////////
class MyQt;//pour dire qu'on va le

//j'ai inverser la hauteur et largeur dans le trucs
class ImageNG : public Image
{
	public:

				//test 3//
		
  		
		ImageNG();
		ImageNG(int i,const char *n);
		ImageNG(int i,const char *n,const Dimension &d);
		ImageNG(const char* cheminFichierPhoto);

		ImageNG(const ImageNG& i);

		~ImageNG();

		void Affiche() const; 

		void setPixel(int x,int y,int val);
		int getPixel(int x,int y)const;

		void setBackground(int val);

		void Dessine()const;

		void importFromFile(const char* fichier);
		void exportToFile(const char* fichier, const char* format) ;


		int getLuminance()const;
		int getMinimum() const;
		int getMaximum() const;
		float getContraste() const;


		//////operateur///////////
		ImageNG& operator=(const ImageNG& valeur);// =
		friend std::ostream& operator<<(std::ostream& s,const ImageNG& valeur); // <<
		// friend std::istream& operator>>(std::istream& is,ImageNG& img); // pas necessaire j'ai fais de trop et surement faux

		ImageNG operator+(int valeurajouter)const;// + pourquoi pas de et //pour i = 20 + i ;
		friend ImageNG operator+(int valeurajouter,const ImageNG& img);
		ImageNG operator-(int valeurretirer)const;// -


		ImageNG operator++();//++i
		ImageNG operator++(int);//i++
		ImageNG operator--();//--i
		ImageNG operator--(int);//i--

		ImageNG operator-(const ImageNG& image) const;// deux class - class

		////operateur de comparaison ///////////:

		friend bool operator==(ImageNG const& objet1, ImageNG const& objet2);
      	friend bool operator>(ImageNG const& objet1, ImageNG const& objet2);
      	friend bool operator<(ImageNG const& objet1, ImageNG const& objet2);





	private:
		
  		
  		int matrice[L_MAX][H_MAX];

  		//pixel//








};

#endif