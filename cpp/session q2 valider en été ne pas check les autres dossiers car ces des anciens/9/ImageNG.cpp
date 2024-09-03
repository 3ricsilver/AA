#include "ImageNG.h"
#include <iostream>
#include <string.h>

#include "MyQT.h"

#include "RGBException.h"
#include "XYException.h"
using namespace std;

ImageNG :: ImageNG():Image()
{
	cout<<"Constructeur par defaut de ImageNG"<<endl;
	setBackground(0);
}


ImageNG::ImageNG(int num, const char* pnom) :Image(num, pnom)
{
	cout<<"Constructeur avec deux argumentt de ImageNG"<<endl;
	setBackground(0);
}


ImageNG::ImageNG(int num, const char* pnom,const Dimension& dim):Image(num,pnom,dim)
{
	cout<<"Constructeur 3 arg de ImageNG"<<endl;
	setBackground(0);
}



ImageNG::ImageNG(const ImageNG& source):Image(source)
{
	cout<<"Constructeur copie de ImageNG"<<endl;
	
	int i,j;
	setBackground(0);
	for(i=0;i<source.dimension.getLargeur();i++)
		for(j=0;j<source.dimension.getHauteur();j++)
			matrice[i][j]=source.matrice[i][j];

}


ImageNG:: ImageNG(const char *pnom):Image(pnom)
{
	
	importFromFile(pnom);
}

ImageNG ::~ImageNG()
{
	cout<< "Destructeur de ImageNG"<<endl;
}


void ImageNG:: setPixel(int x,int y,int val)
{

	if(val < 0 || val>256) throw RGBException("Valeur du pixel invalide : ",val);

	if (x > dimension.getLargeur()) throw XYException("Valeur du pixel invalide : ",'x');
  	if (y > dimension.getHauteur()) throw XYException("Valeur du pixel invalide : ",'y');
	
	matrice[x][y]= val;

}




int ImageNG:: getPixel(int x,int y)const
{
	return matrice[x][y];
}


void ImageNG:: setBackground(int val)
{
	int i,j;

	if(val < 0 || val>256) throw RGBException("Valeur du pixel invalide : ",val);

	for(i=0;i<L_MAX;i++)
		for(j=0;j<H_MAX;j++)
			matrice[i][j]=val;
}


void ImageNG :: Affiche()const
{
	cout<<"id="<<id<<"	nom="<<nom<<endl;
	dimension.Affiche();

}

void ImageNG:: Dessine()const
{
	MyQT:: ViewImage(*this);
}

void ImageNG:: importFromFile(const char* fichier)
{
	MyQT:: ImportFromFile(*this,fichier);
}

void ImageNG:: exportToFile(const char* fichier, const char* format)const
{
	MyQT:: ExportToFile(*this,fichier,format);
}

int ImageNG:: getLuminance()const
{
	int max=0, i,j,moyenne=0;

	for(i=0;i<dimension.getLargeur();i++)
	{
		for(j=0;j<dimension.getHauteur();j++)
		{
			max=max + matrice[i][j];
			moyenne++;
		}
	}
		

	return max/moyenne;	
}

int ImageNG:: getMinimum()const
{
	int min=matrice[0][0], i,j;

	for(i=0;i<dimension.getLargeur();i++)
	{
		for(j=0;j<dimension.getHauteur();j++)
		{
			if(matrice[i][j]< min)
				min =matrice[i][j];
		}
	}

	return min;	
}

int ImageNG:: getMaximum()const
{
	int max=matrice[0][0], i,j;

	for(i=0;i<dimension.getLargeur();i++)
	{
		for(j=0;j<dimension.getHauteur();j++)
		{
			if(matrice[i][j]> max)
				max =matrice[i][j];
		}
	}

	return max;	
}

float ImageNG:: getContraste()const
{
	float contraste;

	int min,max;

	min = getMinimum();
	max = getMaximum();

	
	contraste = (max-min)/(max+min);

	return contraste;	
}


ImageNG& ImageNG::operator=(const ImageNG& d)
{
	Image::setId(d.id);
	Image::setNom(d.nom);

	dimension.setLargeur(d.dimension.getLargeur());
	dimension.setHauteur(d.dimension.getHauteur());

	int i,j;
	
	for(i=0;i<dimension.getLargeur();i++)
		for(j=0;j<dimension.getHauteur();j++)
			matrice[i][j]=d.matrice[i][j];

	return(*this);
}

ostream& operator<<(ostream& s, const ImageNG& img)
{
	s <<"nom :" << img.nom <<"id :" << img.id <<" Dimension :" <<img.dimension.getLargeur()<< "/"<<img.dimension.getHauteur() << " Luminance :"<<img.getLuminance();

	return s;
}
 
ImageNG ImageNG ::operator+(int p)const
{
	int i,j;

	ImageNG img(*this);


	for(i=0;i<dimension.getLargeur();i++)
	{
		for(j=0;j<dimension.getHauteur();j++)
		{
			img.matrice[i][j]=img.matrice[i][j]+ p;

			if(img.matrice[i][j]>255)
			{
				img.matrice[i][j]=255;
			}
		}
	}
	

	return img;
}


ImageNG ImageNG ::operator-(int p)const
{
	int i,j;

	ImageNG img(*this);

	for(i=0;i<dimension.getLargeur();i++)
	{
		for(j=0;j<dimension.getHauteur();j++)
		{
			img.matrice[i][j]=img.matrice[i][j]- p;

			if(img.matrice[i][j]<0)
			{
				img.matrice[i][j]=0;
			}
		}
	}

	return img;
}

ImageNG operator+(int p,const ImageNG& img)
{
	return img + p;
}

ImageNG ImageNG::operator++() //pre
{
	
	(*this)=(*this) +20;
	
	
	return (*this);
}

ImageNG ImageNG::operator++(int post)
{


	ImageNG img(*this);

	(*this) = (*this) + 20;
	
	return img;
}

ImageNG ImageNG:: operator--()
{
		
	(*this)=(*this) -20;
	
	
	return (*this);
	
}

ImageNG ImageNG::operator--(int post)
{

	ImageNG img(*this);

	(*this) = (*this) - 20;
	
	return img;
	
}

ImageNG ImageNG:: operator-(const ImageNG& image)
{
	int i,j;


	ImageNG img(*this);

	for(i=0;i<dimension.getLargeur();i++)
		for(j=0;j<dimension.getHauteur();j++)
			img.matrice[i][j]=img.matrice[i][j]- image.matrice[i][j];


	for(i=0;i<dimension.getLargeur();i++)
	{
		for(j=0;j<dimension.getHauteur();j++)
		{

			if(img.matrice[i][j]<0)
			{
				img.matrice[i][j]=0;
			}
		}
	}

	return img;
}

bool ImageNG:: operator<(const ImageNG& image)
{
	int i,j;


	//ImageNG img(*this);//ca fait bug

	if(dimension.getLargeur() != image.dimension.getLargeur())  throw XYException("largeur differente",'x');

	if(dimension.getHauteur() != image.dimension.getHauteur()) throw XYException("hauteur differente",'y');

	for(i=0;i<dimension.getLargeur();i++)
	{
		for(j=0;j<dimension.getHauteur();j++)
		{
			if(matrice[i][j]>=image.matrice[i][j])
				return false;	
		}
	}

	return true;	
}

bool ImageNG::operator>(const ImageNG& image)
{
	int i,j;


	//ImageNG img(*this);

	if(dimension.getLargeur() != image.dimension.getLargeur())  throw XYException("largeur differente : ",'x');

	if(dimension.getHauteur() != image.dimension.getHauteur()) throw XYException("hauteur differente : ",'y');

	for(i=0;i<dimension.getLargeur();i++)
	{
		for(j=0;j<dimension.getHauteur();j++)
		{
			if(matrice[i][j]<=image.matrice[i][j])
				return false;	
		}
	}

	return true;	
}

bool ImageNG::operator==(const ImageNG& image)
{
	int i,j;


	//ImageNG img(*this);

	if(dimension.getLargeur() != image.dimension.getLargeur())  throw XYException("largeur differente : ",'x');

	if(dimension.getHauteur() != image.dimension.getHauteur()) throw XYException("hauteur differente : ",'y');

	for(i=0;i<dimension.getLargeur();i++)
	{
		for(j=0;j<dimension.getHauteur();j++)
		{
			if(matrice[i][j]!=image.matrice[i][j]) 
				return false;	
		}
	}

	return true;	
}


/*sauvegarde sur un fichier*/

void ImageNG::Save(ofstream &fichier) const
{
	Image::Save(fichier);

	for(int x=0;x<dimension.getLargeur();x++)
	{
		for(int y=0; y<dimension.getHauteur();y++)
		{
				
			fichier.write((char*)&matrice[x][y],sizeof(int));
		}
	}
}



void ImageNG::Load(ifstream &fichier)
{
	Image::Load(fichier);

	for(int x=0;x<dimension.getLargeur();x++)
	{
			for(int y=0; y<dimension.getHauteur();y++)
			{
				fichier.read((char*)&matrice[x][y],sizeof(int));
			}
	}
}	