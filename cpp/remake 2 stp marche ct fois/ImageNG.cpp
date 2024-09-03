
#include "ImageNG.h"
#include <stdlib.h>
#include <iostream>
#include "MyQT.h"
#include<cstring>

//partie 2test//
///home/student/AA/LaboCpp2023_Enonce/MyQT.h
using namespace std;

  //constructeur par defaut////////////////////////////////////
  ImageNG::ImageNG(): Image()
  {
    setBackground(0);
  }

  //constructeur par initiation/////////////////////
  ImageNG::ImageNG(int i,const char *n): Image(i,n)
  {
    setBackground(0);
  }

  ImageNG::ImageNG(int i,const char *n,const Dimension &d): Image(i,n,d)
  {
    setBackground(0);
  }



  //image//
  ImageNG::ImageNG(const char* fichier): Image(fichier)
  {
    importFromFile(fichier);
  }

  // constructeur de copie /////////////////
  ImageNG::ImageNG(const ImageNG& image): Image(image)
  {
    for(int i=0;i<dimension.getLargeur();i++)
    {
      for(int j=0;j<dimension.getHauteur();j++)
      {
        matrice[i][j]=image.matrice[i][j];
      }
    }
  }
  //le destructeur////////////////////
  ImageNG::~ImageNG()
  {
    cout << "Destructeur  ImageNG je fais rien mais c pour debug" << endl;
  }



 ///////////setter///////////////////

////test 3 //////////////
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
  // for(int i=0;i<d.getLargeur();i++)
  // {
  //   for (int j = 0; j <d.getHauteur(); j++)
  //   {
  //     matrice[i][j]=val;
  //   }
  // }
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

void ImageNG ::Affiche() const
{
    cout << "id : " <<id<< endl;
    cout << "nom : "<<nom<< endl;
    dimension.Affiche();
}

/////////////test4///////////////////


int ImageNG::getLuminance() const
{
  int somme = 0;
  for (int i = 0; i < dimension.getLargeur(); i++) 
  {
    for (int j = 0; j < dimension.getHauteur(); j++) 
    {
      somme = somme + matrice[j][i]; 
    }
  }
  // Calule la moyenne
  int luminance = somme / (dimension.getLargeur() * dimension.getHauteur());
  return luminance;
}


int ImageNG::getMinimum() const
{
  int minimum = matrice[0][0];
  for (int i = 0; i < dimension.getLargeur(); i++) {
    for (int j = 0; j < dimension.getHauteur(); j++) {
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
  for (int i = 0; i < dimension.getLargeur(); i++) {
    for (int j = 0; j < dimension.getHauteur(); j++) {
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
        dimension = valeur.dimension;

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


// ostream& operator<<(std::ostream& os, const ImageNG& img)
// {
//   os << "Identifiant: " << img.id << ", Nom: " << img.nom << ", Dimension: " << img.d << ", Luminance: " << img.getLuminance() const << ", Contraste: " << img.getContraste() const;
//   return os;
// } 


//pourquoi ca ne compilait pas avec les const

ostream& operator<<(std::ostream& os, const ImageNG& img)
{
  os << "Identifiant: " << img.id << ", Nom: " << img.nom << ", Dimension: " << img.dimension << ", Luminance: " << img.getLuminance() << ", Contraste: " << img.getContraste();
  return os;
}



// istream& operator>>(std::istream& is, ImageNG& img)
// {
//   is >> img.id >> img.nom >> img.d >> img.matrice;
//   return is;
// }
// fallait juste faire <<

  // os << "Identifiant: " << img.id << ", Nom: " << img.nom << ", Dimension: " << img.d << ", Luminance: " << getLuminance() << ", Contraste: " << getContraste();




ImageNG ImageNG::operator+ (int valeurajouter) const
{
    ImageNG resultat(*this); // on crée un objet temporaire à partir de
                           // l’objet courant car celui-ci ne doit pas
                          // être modifié !

    for (int i = 0; i < dimension.getLargeur(); ++i)//tu additionnes toutes la matrice avec cette valeurs 
    {
        for (int j = 0; j < dimension.getHauteur(); ++j)
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

    for (int i = 0; i < dimension.getLargeur(); ++i)//tu additionnes toutes la matrice avec cette valeurs 
    {
        for (int j = 0; j < dimension.getHauteur(); ++j)
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

    for (int i = 0; i < dimension.getLargeur(); ++i)
    {
        for (int j = 0; j < dimension.getHauteur(); ++j)
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
    for (int i = 0; i < objet1.dimension.getLargeur(); ++i)//c'est tirer par les cheveux
    {
        for (int j = 0; j < objet1.dimension.getHauteur(); ++j)
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
    for (int i = 0; i < objet1.dimension.getLargeur(); ++i)
    {
        for (int j = 0; j < objet1.dimension.getHauteur(); ++j)
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
    for (int i = 0; i < objet1.dimension.getLargeur(); ++i)
    {
        for (int j = 0; j < objet1.dimension.getHauteur(); ++j)
        {


            if (objet1.matrice[i][j] > objet2.matrice[i][j])
            {
                return false;
            }
        }
    }

    return true;  
}