
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
		static const int L_MAX=500;//le  prof nous dit de les changer a 700
  		static const int H_MAX=500;
  		
		ImageNG();
		ImageNG(int i,const char *n);
		ImageNG(int i,const char *n,const Dimension &d);
		ImageNG(const char* cheminFichierPhoto);

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