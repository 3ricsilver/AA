#include "ImageRGB.h"

#include "MyQT.h"
#include "RGBException.h"
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


ImageRGB::ImageRGB(const char *path) : Image(path)
{

	cout << " ImageRGB : Constructeur initialisation path " << endl;
	setBackground(Couleur(0,0,0));
		
	importFromFile(path);
		

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
	if(valeur.getRouge() < 0 || valeur.getRouge()>256) throw RGBException("couleur rouge invalide : ",valeur.getRouge());
	if(valeur.getVert() < 0 || valeur.getVert()>256) throw RGBException("couleur vert invalide", valeur.getVert());
	if(valeur.getBleu() < 0 || valeur.getBleu()>256) throw RGBException("couleur Bleu invalide",valeur.getBleu());
	
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



/* sauvegarde sur un fichier*/

void ImageRGB::Save(ofstream &fichier) const
{
	Image::Save(fichier);

		for(int y=0;y<dimension.getHauteur(); y++)
		{
			for(int x=0; x<dimension.getLargeur();x++)
			{
				matrice[x][y].Save(fichier);
			}
		}
				

}


void ImageRGB::Load(ifstream &fichier) 
{
	Image::Load(fichier);

	for(int y=0;y<dimension.getHauteur(); y++)
	{
		for(int x=0; x<dimension.getLargeur();x++)
		{
			matrice[x][y].Load(fichier);
		}
	}
}