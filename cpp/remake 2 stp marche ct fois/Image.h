#ifndef IMAGE_H
#define IMAGE_H
#include "Dimension.h"
#include <string>

class Image
{
	protected:

	int id;
	char* nom;
	Dimension dimension;

	public:

	    /////////constructeur///////
    	Image();
    	Image (int Id, const char *Nom);
    	Image (const Image &image);
    	Image (int Id, const char *Nom,const Dimension& d);
    	Image(const char* fichier);
    	
    	virtual ~Image();

    	//////////////////
    	int getId() const; 
    	void setId (int val);
    	const char *getNom() const;
    	void setNom (const char *n);
    	Dimension getDimension() const;
    	void setDimension(const Dimension& d);


    	//héritage //virtual pure eric futur
    	virtual void Affiche() const = 0;
    	virtual void Dessine()const = 0;
    	virtual void exportToFile(const char* fichier,const char* format) = 0;


    	//hardcoadage//

    	static const int L_MAX = 1000;
   		static const int H_MAX = 1000;

};

#endif

/*


On vous demande de créer la classe abstraite Image qui possède
• les variables membres id (int), nom (char* → string si vous le souhaitez) et dimension
(Dimension)
• les accesseurs getXXX/setXXX pour ces trois variables membres.
• Les méthodes virtuelles pures void Affiche(), void Dessine() et void exportToFile(const
char* fichier, const char* format)

*/