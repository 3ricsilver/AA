#include "ImageRGB.h"

#include "MyQT.h"

using namespace std;

ImageRGB::ImageRGB():Image()
{
	cout<<"Constructeur par defaut de ImageRGB"<<endl;
	setBackground(Couleur::NOIR);
}

ImageRGB::~ImageRGB()
{
	cout<< "Destructeur de ImageRGB"<<endl;
	setBackground(Couleur::NOIR);
}

ImageRGB::ImageRGB(const ImageRGB& img):Image(img)
{
	cout<<"Constructeur copie de ImageRGB"<<endl;

	int i,j;
	for(i=0;i<img.dimension.getLargeur();i++)
		for(j=0;j<img.dimension.getHauteur();j++)
			matrice[i][j]=img.matrice[i][j];
}

ImageRGB::ImageRGB(int num, const char* pnom,const Dimension& dim):Image(num,pnom,dim)
{
	cout<<"Constructeur avec 3 argument de ImageRGB"<<endl;
	setBackground(Couleur::NOIR);
}

void ImageRGB::Affiche()const
{
	cout<<"id="<<id<<"	nom="<<nom<<endl;
	dimension.Affiche();
}

void ImageRGB::Dessine()const
{
	MyQT:: ViewImage(*this);
}

void ImageRGB::setBackground(const Couleur& valeur)
{
	int i,j;

	for(i=0;i<dimension.getLargeur();i++)
		for(j=0;j<dimension.getHauteur();j++)
			matrice[i][j]=valeur;
}

void ImageRGB::setPixel(int x,int y,const Couleur& valeur)
{
	
	matrice[x][y]= valeur;
}


Couleur ImageRGB::getPixel(int x,int y)const
{
	return matrice[x][y];
}

void ImageRGB::importFromFile(const char* fichier)
{
	MyQT:: ImportFromFile(*this,fichier);
}


	
void ImageRGB::exportToFile(const char* fichier, const char* format)const
{
	MyQT:: ExportToFile(*this,fichier,format);
}


ImageRGB& ImageRGB:: operator=(const ImageRGB& img)
{
	Image::setId(img.id);
	Image::setNom(img.nom);

	dimension.setLargeur(img.dimension.getLargeur());
	dimension.setHauteur(img.dimension.getHauteur());

	int i,j;
	
	for(i=0;i<dimension.getLargeur();i++)
		for(j=0;j<dimension.getHauteur();j++)
			matrice[i][j]=img.matrice[i][j];

	return(*this);
}


ostream& operator<<(ostream& s, const ImageRGB& img)
{
	s <<"nom :" << img.nom <<"id :" << img.id <<" Dimension :" <<img.dimension.getLargeur()<< "/"<<img.dimension.getHauteur() ;

	return s;
}