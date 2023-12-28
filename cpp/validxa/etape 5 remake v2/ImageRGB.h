#include "Couleur.h"
#include "Image.h"
#include "Dimension.h"

#ifndef IMAGERGB_H
#define IMAGERGB_H




////////////////////
class MyQt;

class ImageRGB : public Image
{
	public:

	static const int L_MAX =700;
	static const int H_MAX =700;

	//constructeur//
	//defaut//
    ImageRGB();
    //le reste//
    ImageRGB(int id, const char* nom);
    ImageRGB(int id, const char* nom, const Dimension& d);
    //copie//
    ImageRGB(const ImageRGB& image);
    ImageRGB(const char *fichier);
    //destructeur//
    ~ImageRGB();//image le fait déja donc faut rien faire eric fuutur

    //setter//
    void setPixel(int x,int y,const Couleur& valeur);
    void setBackground(const Couleur& valeur);


    //getter// 
    Couleur getPixel(int x,int y)const;


    //methode//
    void Affiche() const;s
    void Dessine()const;
    void exportToFile(const char* fichier,const char* format);
    void importFromFile(const char* fichier);





    //opérateur//
    friend std::ostream& operator<< (std::ostream &out,const ImageRGB &imagergb);
    ImageRGB& operator= (const ImageRGB &imagergb);






	private:
    Couleur matrice[L_MAX][H_MAX];

};

#endif