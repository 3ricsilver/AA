#include "ImageB.h"

#include "MyQT.h"


ImageB::ImageB():Image()
{
	#ifdef DEBUG
	cout<<"Constructeur par defaut de ImageB"<<endl;
	#endif

	setBackground(false);

}

ImageB::~ImageB()
{
	#ifdef DEBUG
	cout<<"Destructeur par defaut de la classe ImageB"<<endl;
	#endif

	cout<< "Destructeur de ImageB"<<endl;
}

ImageB::ImageB(const ImageB& img):Image(img.id,img.nom,img.dimension)
{

	int i,j;
	

	for(i=0;i<img.dimension.getLargeur();i++)
		for(j=0;j<img.dimension.getHauteur();j++)
			matrice[i][j]=img.matrice[i][j];
}

ImageB::ImageB(int num, const char* pnom,const Dimension& dim):Image(num,pnom,dim)
{

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
	matrice[x][y]= valeur;
}

bool ImageB:: getPixel(int x,int y)const
{
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

 Couleur ImageB:: couleurTrue(Couleur::BLANC);
 Couleur ImageB:: couleurFalse(Couleur::NOIR);


