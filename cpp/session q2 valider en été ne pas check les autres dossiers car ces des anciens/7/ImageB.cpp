#include "ImageB.h"

#include "MyQT.h"

#include "XYException.h"

ImageB::ImageB():Image()
{
	cout<<"Constructeur par defaut de ImageB"<<endl;
	setBackground(false);
}


ImageB::ImageB(const ImageB& img):Image(img)
{
	cout<<"Constructeur copie de ImageB"<<endl;
	int i,j;
	for(i=0;i<img.dimension.getLargeur();i++)
		for(j=0;j<img.dimension.getHauteur();j++)
			matrice[i][j]=img.matrice[i][j];
}


ImageB::ImageB(int num, const char* pnom,const Dimension& dim):Image(num,pnom,dim)
{
	cout<< "Constructeur avec 3 arguments de ImageB"<<endl;
	setBackground(false);
}

ImageB::~ImageB()
{
	cout<< "Destructeur de ImageB"<<endl;
}



void ImageB::Affiche()const
{
	cout<<"id="<<id<<"	nom="<<nom<<endl;
	dimension.Affiche();
}

void ImageB::Dessine()const
{
	MyQT:: ViewImage(*this);
}


void ImageB:: setBackground(bool valeur)
{
	int i,j;

	for(i=0;i<dimension.getLargeur();i++)
		for(j=0;j<dimension.getHauteur();j++)
			matrice[i][j]=valeur;
}

void ImageB:: setPixel(int x,int y,bool valeur)
{
	if(x<0 || x> dimension.getLargeur()) throw XYException("largeur de pixel binaire invalide : ",'x');
	if(y<0 || y> dimension.getHauteur()) throw XYException("hauteur de pixel binaire invalide : ",'y');

	matrice[x][y]= valeur;
}

bool ImageB:: getPixel(int x,int y)const
{
	if(x<0 || x> dimension.getLargeur()) throw XYException("largeur de pixel binaire invalide : ",'x');
	if(y<0 || y> dimension.getHauteur()) throw XYException("hauteur de pixel binaire invalide : ",'y');

	return matrice[x][y];
}


 void ImageB:: exportToFile(const char* fichier,const char* format)const
 {
 	MyQT:: ExportToFile(*this,fichier,format);
 }

 ostream& operator<<(ostream& s, const ImageB& img)
 {
 	s <<"nom :" << img.nom <<"id :" << img.id <<" Dimension :" <<img.dimension.getLargeur()<< "/"<<img.dimension.getHauteur() ;

	return s;
 }


ImageB& ImageB:: operator=(const ImageB& img)
{
	setNom(img.nom);
	setId(img.id);
	dimension.setLargeur(img.getDimension().getLargeur());
	dimension.setHauteur(img.getDimension().getHauteur());

	for(int i = 0; i < dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j] = img.matrice[i][j];

	return *this;
}

Couleur ImageB::couleurTrue = Couleur(255,255,255);
Couleur ImageB::couleurFalse = Couleur(0,0,0);


