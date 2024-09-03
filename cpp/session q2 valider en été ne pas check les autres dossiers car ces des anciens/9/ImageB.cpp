#include "ImageB.h"

#include "MyQT.h"

#include "XYException.h"
/*
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


//sauvegarde sur un fichier

void ImageB::Save(ofstream &fichier) const
{
	Image::Save(fichier);

		
	for(int x=0;x<dimension.getLargeur();x++)
	{
		for(int y=0; y<dimension.getHauteur();y++)
		{
			fichier.write((char*)&matrice[x][y],sizeof(bool));
		}
	}

}

void ImageB::Load(ifstream &fichier)
{
	Image::Load(fichier);

		for(int x=0;x<dimension.getLargeur();x++)
		{
			for(int y=0; y<dimension.getHauteur();y++)
			{
				fichier.read((char*)&matrice[x][y],sizeof(bool));
			}
		}
}   

Couleur ImageB::couleurTrue = Couleur(255,255,255);
Couleur ImageB::couleurFalse = Couleur(0,0,0);


*/

#include <string.h>
#include <iostream>
#include "ImageB.h"
#include "MyQT.h"


using namespace std; 
const int L_NOM=20;
Couleur ImageB::couleurTrue= Couleur::BLANC ;
Couleur ImageB::couleurFalse= Couleur::NOIR;




	ImageB::ImageB() : Image() 
	{
		#ifdef DEBUG
		
			cout << "-------- ImageB : Constructeur par defaut" << endl;

		#endif
		
		
		setBackground(0);
	}



	ImageB::ImageB(int i, const char *s): Image(i,s)
	{
		#ifdef DEBUG
		
			cout << "-------- ImageB : Constructeur initialisation" << endl;

		#endif

		
		setBackground(0);

	}


	ImageB::ImageB(int i,const char *s, const Dimension& dim): Image(i,s,dim)
	{
		#ifdef DEBUG
		
		cout << "-------- ImageB : Constructeur initialisation bis " << endl;

		#endif


		
		setBackground(0);
		
	}
	
//--------------------Constructeur de copie-------------------
	ImageB::ImageB(const ImageB& img) : Image(img)
	{
		#ifdef DEBUG
		
		cout << "-------- ImageB : Constructeur de copie" << endl;

		#endif
		

		bool valeur;

		int xMax= dimension.getLargeur();
		int yMax= dimension.getHauteur();
		for(int x=0; x<xMax; x++)
		{
			for(int y =0;y<yMax;y++)
			{
				valeur=img.getPixel(x,y);
				setPixel(x,y,valeur);
			}
		}

	}
	
// ------------ Destructeur---------
	ImageB::~ImageB() 
	{
		#ifdef DEBUG
		
		cout << "-------- ImageB: Destructeur" << endl;

		#endif
			
	}



	void ImageB::setPixel(int x, int y , bool valeur)throw(XYException)
	{	
		if(x>dimension.getLargeur())
			throw XYException("largeur trop grande",'X');

		else if(0>x)
			throw XYException("largeur negative",'X');

		else if(y>dimension.getHauteur())
			throw XYException("hauteur trop grande",'Y');

		else if(0>y)
			throw XYException("hauteur negative",'Y');
		
		else
		matrice[x][y]=valeur;
		
	}


	void ImageB::setBackground(const bool valeur)
	{
		for(int y=0; y<dimension.getHauteur(); y++)
		
		{
			for(int x =0 ; x<dimension.getLargeur();x++)
			{
				if(valeur==0)
					setPixel(x,y,0);
				else
					setPixel(x,y,1);
			}
		}
	}

//---------- Getter------------
	bool ImageB:: getPixel(int x , int y) const throw(XYException)
	{
		bool val;

		if(x>dimension.getLargeur())
		{	
			if(y>dimension.getHauteur())
				throw XYException("largeur et hauteur trop grande",'D');

			else if(0>y)
				throw XYException("largeur trop grande et hauteur negative",'D');
			
			else
				throw XYException("largeur trop grande",'X');
			
		}
		else if(0>x)
		{	
			if(y>dimension.getHauteur())
				throw XYException("largeur negative et hauteur trop grande",'D');

			else if(0>y)
				throw XYException(" largeur et hauteur negative",'D');
			
			else
			throw XYException("largeur negative",'X');
		}

		else if(y>dimension.getHauteur())
			throw XYException("hauteur trop grande",'Y');

		else if(0>y)
			throw XYException("hauteur negative",'Y');

		else
		val = matrice[x][y];
		return val;
	} 
	
// ---------Methode D'instance---------

	void ImageB::Affiche() const 
	{
		
		
		cout << "Image : nom = ";
		if(nom)
			cout << nom;
		else
			cout << "NomparDefaut";

		cout << "\n id = " << id << "]" << endl;
		dimension.Affiche();
	
	}

	void ImageB::Dessine()const
	{	

		MyQT::ViewImage(*this);
		
	}

	

	void ImageB::exportToFile(const char* fichier, const char* format)
	{
    	
    	MyQT::ExportToFile(*this, fichier, format);
	}




// ------ surcharge---

	ImageB& ImageB::operator=(const ImageB& im)
	{

		setNom(im.getNom());
		setId(im.getId());
		setDimension(im.getDimension());
		for(int h=0; h<dimension.getHauteur();h++)

			for(int l=0;l<dimension.getLargeur(); l++)
				
				matrice[l][h]=im.matrice[l][h];

		return(*this);
	}


	ostream& operator<<(ostream& s, const ImageB& im)
	{
		s<<"ID:"<<im.getId()<<"\n Nom:"<<im.getNom()<<"\n Dimension:"<<im.getDimension()<<endl;
		return s ;
	} 

	

	/*sauvegarde sur un fichier*/

	void ImageB::Save(ofstream &fichier) const
	{
		Image::Save(fichier);

		
		for(int x=0;x<dimension.getLargeur();x++)
			for(int y=0; y<dimension.getHauteur();y++)
			{
				fichier.write((char*)&matrice[x][y],sizeof(bool));
			}


	}



	void ImageB::Load(ifstream &fichier)
	{
		Image::Load(fichier);

		
		for(int x=0;x<dimension.getLargeur();x++)
			for(int y=0; y<dimension.getHauteur();y++)
			{
				fichier.read((char*)&matrice[x][y],sizeof(bool));
			}
	}   