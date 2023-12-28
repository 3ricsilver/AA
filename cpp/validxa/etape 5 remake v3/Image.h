#ifndef IMAGE_H
#define IMAGE_H
#include "Dimension.h"
class Image 
{
	protected:
		int id;
		char*nom;
		Dimension dimension;

	public:
		//variable //
		static const int L_MAX=500;
        static const int H_MAX=500;
      	//constructeur//////
      	Image();
     	Image(int i,const char *n);
     	Image(int i,const char *n,const Dimension &d);
        Image(const Image &image);

      ////setter//////////

      void setId(int val);
      void setNom(const char *n);
      void setDimension(const Dimension &d);


       ////getter//////////

      int getId()const;
      const char *getNom() const;
      Dimension getDimension()const;


      virtual ~Image();//Destructeur virtual mais je peux pas faire sur le constructeur
      virtual void Affiche() const =0;
      virtual void Dessine()const =0;
      virtual void exportToFile(const char* fichier, const char* format) =0;


};
#endif