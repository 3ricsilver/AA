#include "ImageNG.h"
#include "MyQT.h"
#include <iostream>
#include <string.h>

using namespace std;

//constructeur///

/*Par défaut */
ImageNG::ImageNG():Image()
{
	
}

ImageNG::ImageNG(int Id,const char *Nom):Image(Id,Nom)
{
	
}

ImageNG::ImageNG(int Id,const char *Nom,const Dimension &d):Image(Id,Nom,d)
{
	
}

/*Pour ouvrir des fichiers images  */
ImageNG::ImageNG(const char* FichierImage)
{
	nom=NULL;
	setNom(FichierImage);
	setId(0);
	MyQT::ImportFromFile(*this,FichierImage);//this c'est ont crée une copie temporaire et cette partie permet de pendre le fichier
}
// copie //
ImageNG::ImageNG(const ImageNG &image):Image(image)
{
	for(int i=0;i<d.getHauteur();i++)
    {
      for(int j=0;j<d.getLargeur();j++)
      {
        matrice[i][j]=image.matrice[i][j];
      }
    }
}

//Destructeur//

ImageNG::~ImageNG()
{
	// if(nom)
	// {
	// delete(nom);		
	// }
}

//Afichage

void ImageNG::Affiche() const
{
  cout <<"nom:"<<nom<<" id:"<<id<<"Dimension:"<< endl;
  d.Affiche();
} 


//MYQT//

void ImageNG::setPixel(int xpixel,int ypixel,int valpixel)
{
  matrice[xpixel][ypixel]=valpixel;

}

int ImageNG::getPixel(int x,int y) const
{
  return matrice[x][y];
}

void ImageNG::setBackground(int val)
{
  for(int i=0;i<H_MAX;i++)//ca marchera pas si image plus petit que 500 et superieur 500
  {
    for (int j = 0; j <L_MAX; j++)
    {
      matrice[i][j]=val;
    }
  }
}


void ImageNG::Dessine()const 
{
   MyQT::ViewImage(*this);
}  

void ImageNG::importFromFile(const char* fichier)
{
  MyQT::ImportFromFile(*this,fichier);
}

void ImageNG::exportToFile(const char* fichier, const char* format)
{
  MyQT::ExportToFile(*this,fichier,format);
}


//relative au niveau de gris


int ImageNG::getLuminance() const
{
  int somme = 0;
  for (int i = 0; i < d.getHauteur(); i++) 
  {
    for (int j = 0; j < d.getLargeur(); j++) 
    {
      somme = somme + matrice[j][i]; 
    }
  }
  // Calule la moyenne
  int luminance = somme / (d.getLargeur() * d.getHauteur());
  return luminance;
}


int ImageNG::getMinimum() const
{
  int minimum = matrice[0][0];
  for (int i = 0; i < d.getHauteur(); i++) {
    for (int j = 0; j < d.getLargeur(); j++) {
      if (matrice[i][j] < minimum) {
        minimum = matrice[i][j];
      }
    }
  }
  return minimum;
}


int ImageNG::getMaximum() const
{
  int maximum = matrice[0][0];
  for (int i = 0; i < d.getHauteur(); i++) {
    for (int j = 0; j < d.getLargeur(); j++) {
      if (matrice[i][j] > maximum) {
        maximum = matrice[i][j];
      }
    }
  }
  return maximum;
}


float ImageNG::getContraste() const
{
  int minimum = getMinimum();
  int maximum = getMaximum();
  float contraste = (float)(maximum - minimum)/(float)(maximum + minimum);
  return contraste;
}


/////////operateur /////////////
ImageNG& ImageNG::operator=(const ImageNG& valeur)
{
    if (this != &valeur) //verif si il existe une valeur
    {
        id = valeur.id;
        setNom(valeur.nom);
        d = valeur.d;

        for (int i = 0; i < L_MAX; ++i)
        {
            for (int j = 0; j < H_MAX; ++j)
            {
                matrice[i][j] = valeur.matrice[i][j];
            }
        }
    }
    return *this;
}


ostream& operator<<(std::ostream& os, const ImageNG& img)
{
  os << "Identifiant: " << img.id << ", Nom: " << img.nom << ", Dimension: " << img.d << ", Luminance: " << img.getLuminance() << ", Contraste: " << img.getContraste();
  return os;
}


ImageNG ImageNG::operator+ (int valeurajouter) const
{
    ImageNG resultat(*this); // on crée un objet temporaire à partir de
                           // l’objet courant car celui-ci ne doit pas
                          // être modifié !

    for (int i = 0; i < d.getHauteur(); ++i)//tu additionnes toutes la matrice avec cette valeurs 
    {
        for (int j = 0; j < d.getLargeur(); ++j)
        {
            resultat.matrice[i][j] += valeurajouter;

            
            if (resultat.matrice[i][j] > 255)//verif la val 255
            {
                resultat.matrice[i][j] = 255;
            }
            else if (resultat.matrice[i][j] < 0)//sinon si au cas ou le prof fait un test tordu avec une addition d'une val negative
            {
              resultat.matrice[i][j] = 0;
            }
                
        }
    }

    return resultat;
}



ImageNG operator+(int valeurajouter, const ImageNG& img) 
{
    return img + valeurajouter;
}


ImageNG ImageNG::operator-(int valeurretirer) const
{
    ImageNG resultat(*this); // on crée un objet temporaire à partir de
                           // l’objet courant car celui-ci ne doit pas
                          // être modifié !

    for (int i = 0; i < d.getHauteur(); ++i)//tu additionnes toutes la matrice avec cette valeurs 
    {
        for (int j = 0; j < d.getLargeur(); ++j)
        {
            resultat.matrice[i][j] -= valeurretirer;

            
            if (resultat.matrice[i][j] > 255)//verif la val 255
            {
                resultat.matrice[i][j] = 255;
            }
            else if (resultat.matrice[i][j] < 0)//sinon si au cas ou le prof fait un test tordu avec une addition d'une val negative
            {
              resultat.matrice[i][j] = 0;
            }
                
        }
    }

    return resultat;
}

ImageNG ImageNG::operator++()//i++  // pré-incrémentation
{
 ImageNG temp(*this);
 (*this) = (*this) + 20;
 return (*this);
}


ImageNG ImageNG::operator++(int)//++i  // post-incrémentation
// on fait un int qui sert a rien pour que le compilateur puisse differencier les deux type d'incrementation ++
{
 ImageNG temp(*this); 
 (*this) = (*this) + 20;
 return temp;
}



ImageNG ImageNG::operator--()//i--  // pré-incrémentation
{
 ImageNG temp(*this);
 (*this) = (*this) - 20;
 return (*this);
}


ImageNG ImageNG::operator--(int)//--i  // post-incrémentation
// on fait un int qui sert a rien pour que le compilateur puisse differencier les deux type d'incrementation ++
{
 ImageNG temp(*this); 
 (*this) = (*this) - 20;
 return temp;
}



ImageNG ImageNG::operator-(const ImageNG& image) const// deux class - class
{
    ImageNG resultat(*this);

    for (int i = 0; i < d.getHauteur(); ++i)
    {
        for (int j = 0; j < d.getLargeur(); ++j)
        {
            resultat.matrice[i][j] -= image.matrice[i][j];

            if (resultat.matrice[i][j] < 0)// si negative
            {
                resultat.matrice[i][j] = 0;
            }
        }
    }

    return resultat;
}


//////////Operateur de comparaison////////////////////////////

bool operator==(ImageNG const& objet1, ImageNG const& objet2)
{
    for (int i = 0; i < objet1.d.getHauteur(); ++i)//c'est tirer par les cheveux
    {
        for (int j = 0; j < objet1.d.getLargeur(); ++j)
        {


            if (objet1.matrice[i][j] != objet2.matrice[i][j])
            {
                return false;
            }
        }
    }

    return true;  
}


bool operator>(ImageNG const& objet1, ImageNG const& objet2)
{
    for (int i = 0; i < objet1.d.getHauteur(); ++i)
    {
        for (int j = 0; j < objet1.d.getLargeur(); ++j)
        {


            if (objet1.matrice[i][j] < objet2.matrice[i][j])
            {
                return false;
            }
        }
    }

    return true;  
}



bool operator<(ImageNG const& objet1, ImageNG const& objet2)
{
    for (int i = 0; i < objet1.d.getHauteur(); ++i)
    {
        for (int j = 0; j < objet1.d.getLargeur(); ++j)
        {


            if (objet1.matrice[i][j] > objet2.matrice[i][j])
            {
                return false;
            }
        }
    }
    return true;  
}