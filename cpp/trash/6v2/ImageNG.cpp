#include "ImageNG.h"
#include "MyQT.h"
#include <iostream>
#include "XYException.h"
#include "RGBException.h"
  //constructeur..

ImageNG :: ImageNG() : Image()
{
    setBackground(0);
}

ImageNG ::ImageNG (int Id, const char *Nom): Image()
{
    
    setBackground(0);

}

ImageNG ::ImageNG (int Id, const char *Nom,const Dimension& d)
{
  
    nom = NULL;
    setNom (Nom);
    setId (Id);
    setDimension(d);
    setBackground(0);
}

ImageNG ::ImageNG (const char* fichier)
{
  nom = NULL;
  setNom(fichier);
  setId(0);
  MyQT::ImportFromFile(*this, fichier);
}

ImageNG ::ImageNG (const ImageNG &image) : Image(image)
{
  
  setDimension (image.getDimension());

  for(int i = 0; i< dimension.getLargeur(); i++)
  {
    for (int j = 0; j< dimension.getHauteur(); j++)
    {
      matrice[i][j]= image.matrice[i][j];
    }
  }


}

/*Destructeur*/

ImageNG :: ~ImageNG()
{
  
  // if(nom)
  // {
  //   delete nom;
  // } c'est ca qui faitt crash ne pas decomanter -1
}


/*methode*/


void ImageNG ::Affiche() const
{
    cout << "id : " <<id<< endl;
    cout << "nom : "<<nom<< endl;
    dimension.Affiche();
}

void ImageNG::exportToFile(const char* fichier,const char* format)
{
  MyQT::ExportToFile (*this, fichier, format);
}


void ImageNG::Dessine() const
{

  MyQT::ViewImage(*this);

}

void ImageNG :: importFromFile(const char* fichier)
{
  MyQT::ImportFromFile(*this, fichier);
}



    /*getter setter*/


int ImageNG :: getPixel(int x, int y) const
{
  int Largeur = dimension.getLargeur();
  int Hauteur = dimension.getHauteur();

  
  if((x < 0 || x >= Largeur) && (y < 0 || y >= Hauteur))
  {
    throw XYException ('d',"\nErreur de la valeur de Dimension");
  }

  if(x < 0 || x >= Largeur)
  {
    throw XYException ('x',"\nnErreur de la valeur de Largeur");
  } 

  if(y < 0 || y >= Hauteur)
  {
    throw XYException ('y',"\nnErreur de la valeur de Hauteur");
  } 
  return matrice[x][y];
}

void ImageNG :: setPixel(int x, int y, int val)
{
  if((x < 0 || x >= L_MAX) && (y < 0 || y >= H_MAX))
  {
    throw XYException ('d',"\nErreur de la valeur de Dimension");
  }

  if(x < 0 || x >= L_MAX)
  {
    throw XYException ('x',"\n Erreur de la valeur de Largeur");
  } 

  if(y < 0 || y >= H_MAX)
  {
    throw XYException ('y',"\n Erreur de la valeur de Hauteur");
  } 

  matrice[x][y] = val;
} 


void ImageNG :: setBackground(int val)
{
  if (val < 0 || val>255)
  {
    // cout << "je suis passer par le set background avec une valeur incorecte debuf" << endl;
    throw RGBException(val, "La valeur du niveau de gris est incorrecte il doit etre entre 0 et 255!\n");
  }

  for(int i = 0; i< L_MAX; i++)
  {
    for (int j = 0; j< H_MAX; j++)
    {
      matrice[i][j]= val;
    }
  }
}

int ImageNG :: getLuminance()const
{
  int Somme = 0;
  for(int i = 0; i<dimension.getLargeur(); i++)
  {
    for(int j = 0; j<dimension.getHauteur(); j++)
    {
      Somme = Somme +matrice[i][j];
    }
  }

  return Somme = Somme / (dimension.getLargeur() * dimension.getHauteur());
}

int ImageNG :: getMinimum()const
{
  int Min = 255;
  for(int i = 0; i<dimension.getLargeur(); i++)
  {
    for(int j = 0; j<dimension.getHauteur(); j++)
    {
      if (Min>matrice[i][j])
        Min = matrice[i][j];
    }

  }
  return Min;
 
} 

int ImageNG :: getMaximum()const
{
  int Max = 0;
  for(int i = 0; i<dimension.getLargeur(); i++)
  {
    for(int j = 0; j<dimension.getHauteur(); j++)
    {
      if(Max<matrice[i][j])
        Max = matrice[i][j];
    }
  }
  
  return Max;
}

float ImageNG :: getContraste()const
{
    return (float)(getMaximum() - getMinimum()) / (float)(getMaximum() + getMinimum());
}


/*Surcharge*/


ImageNG& ImageNG:: operator= (const ImageNG &image)
{
  setNom(image.nom);
  setId(image.id);
  dimension.setLargeur(image.dimension.getLargeur());
  dimension.setHauteur(image.dimension.getHauteur());

  for (int i = 0; i < dimension.getLargeur(); i++)
  {
    for (int j = 0; j < dimension.getHauteur(); j++)
    {
      matrice[i][j] = image.matrice[i][j];
    }
  }

  return *this;
}

std::ostream& operator<< (std::ostream &out,const ImageNG &image)
{

  out <<"Nom : " << image.getNom() << std :: endl;
  out <<"ID : " << image.getId() << std :: endl;
  out <<"Largeur : " <<image.dimension.getLargeur() << std :: endl;
  out <<"Hauteur : " <<image.dimension.getHauteur() << std :: endl;
  return out;
}

ImageNG ImageNG :: operator+(int nbr)
{
  ImageNG Somme(*this);

  for(int i = 0; i < Somme.dimension.getLargeur(); i++)
  {
    for(int j = 0; j < Somme.dimension.getHauteur(); j++)
    {
      Somme.matrice[i][j] = Somme.matrice[i][j] + nbr;

      if (Somme.matrice[i][j] > 255)
      {
        Somme.matrice[i][j] = 255;
      }

      if (Somme.matrice[i][j] < 0)
      {
        Somme.matrice[i][j] = 0;
      }
    }
  }

  return Somme;
}

ImageNG operator+(int nbr, ImageNG image)
{
  return image + nbr;
}

ImageNG ImageNG :: operator-(int nbr)
{
  ImageNG Difference(*this);

  for(int i = 0; i < Difference.dimension.getLargeur(); i++)
  {
    for(int j = 0; j < Difference.dimension.getHauteur(); j++)
    {
      Difference.matrice[i][j] = Difference.matrice[i][j] - nbr;
      if (Difference.matrice[i][j] > 255)
      {
        Difference.matrice[i][j] = 255;
      }

      if (Difference.matrice[i][j] < 0)
      {
        Difference.matrice[i][j] = 0;
      }

    }
  }

  return Difference;
}

ImageNG operator-(int nbr, ImageNG image)
{

  return image - nbr;
}

ImageNG operator++(ImageNG image)
{
  return image++;
}

ImageNG ImageNG :: operator++(int)
{
  ImageNG temp(*this);

  temp.dimension.setLargeur(temp.dimension.getLargeur());
  temp.dimension.setHauteur(temp.dimension.getHauteur());

  for (int i = 0; i < temp.dimension.getLargeur(); i++)
  {
    for (int j = 0; j < temp.dimension.getHauteur(); j++)
    {
      temp.matrice[i][j]++;

      if(temp.matrice[i][j] > 255)
      {
        temp.matrice[i][j] = 255;
      }

      if(temp.matrice[i][j] < 0)
      {
        temp.matrice[i][j] = 0;
      }


    }
  }

  return temp;

}

ImageNG operator--(ImageNG image)
{
  return image--;
}

ImageNG ImageNG :: operator--(int)
{
  ImageNG temp(*this);

  temp.dimension.setLargeur(temp.dimension.getLargeur());
  temp.dimension.setHauteur(temp.dimension.getHauteur());

  for (int i = 0; i < temp.dimension.getLargeur(); i++)
  {
    for (int j = 0; j < temp.dimension.getHauteur(); j++)
    {
      temp.matrice[i][j]--;


    }
  }

  return temp;
}

ImageNG ImageNG:: operator-(const ImageNG &image)
{
  ImageNG Resultat(*this);

  for(int i = 0; i < dimension.getLargeur(); i++)
  {
    for(int j = 0; j < dimension.getHauteur(); j++)
    {
      Resultat.matrice[i][j] = Resultat.matrice[i][j] - image.matrice[i][j];
    }
  }


  return Resultat;
}

bool ImageNG :: operator==(const ImageNG &image)
{
  if(dimension != image.dimension)
  {
    return false;
  }

  for (int i = 0; i < dimension.getLargeur(); i++)
  {
    for (int j = 0; j < dimension.getHauteur(); j++)
    {
      if (matrice[i][j] != image.matrice[i][j])
      {
        return false;
      }
    }
  }

  return true;
}

bool ImageNG :: operator<(const ImageNG &image)
{
  int SommeThis = 0;
  int SommeCopie = 0;

  for (int i = 0; i < dimension.getLargeur(); i++)
  {
    for (int j = 0; j < dimension.getHauteur(); j++)
    {
      SommeThis = SommeThis + matrice[i][j];

      SommeCopie = SommeCopie + image.matrice[i][j];
    }
  }
    return SommeThis < SommeCopie;
}

bool ImageNG :: operator>(const ImageNG &image)
{
  int SommeThis = 0;
  int SommeCopie = 0;

  for (int i = 0; i < dimension.getLargeur(); i++)
  {
    for (int j = 0; j < dimension.getHauteur(); j++)
    {
      SommeThis = SommeThis + matrice[i][j];

      SommeCopie = SommeCopie + image.matrice[i][j];
    }
  }
    return SommeThis > SommeCopie;
}
