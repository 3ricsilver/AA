#include "ImageNG.h"
#include "MyQT.h"
#include <iostream>


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

ImageNG :: ~ImageNG()
{
  
  // if(nom)
  // {
  //   delete nom;
  // } ca crash sinon ne pas decommenter
}




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

int ImageNG :: getPixel(int x, int y) const
{
  int Largeur = dimension.getLargeur();
  int Hauteur = dimension.getHauteur();

  if ((x < 0 || x >= Largeur) && (y < 0 || y >= Hauteur))
  {
    throw XYException("\nErreur de la Largeur et de la Longueur !\n", x, y);
  }

  if (x < 0 || x >= Largeur)
  {
    throw XYException("\nErreur la Longueur !\n", x);
    
  }

  if (y < 0 || y >= Hauteur)
  {
    throw XYException("\nErreur de la Largeur !\n", y);
  }

  return matrice[x][y];
}



void ImageNG :: setPixel(int x, int y, int val)
{
  if ((x < 0 || x >= L_MAX) && (y < 0 || y >= H_MAX))
  {
    throw XYException("\nErreur de la Largeur et de la Longueur !\n", x, y);
  }

  if (x < 0 || x >= L_MAX)
  {
    throw XYException("\nErreur la Longueur !\n", x);
    
  }

  if (y < 0 || y >= H_MAX)
  {
    throw XYException("\nErreur de la Largeur !\n", y);
  }
  matrice[x][y] = val;
}



void ImageNG :: setBackground(int val)
{
    if(val < 0 || val > 255)
    {
      throw RGBException ("\nErreur Niveau de gris !\n", val);
    }
    else
    {
      for(int i = 0; i< L_MAX; i++)
      {
        for (int j = 0; j< H_MAX; j++)
        {
          matrice[i][j]= val;
        }
      }

    }
}

int ImageNG :: getLuminance()const
{
  int Somme = 0;
  for(int i = 0; i<dimension.getLargeur(); i++)
  {
    for(int j = 0; j<dimension.getHauteur(); j++)
      Somme = Somme +matrice[i][j];
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

ImageNG& ImageNG:: operator= (const ImageNG &image)
{
  setNom(image.nom);
  setId(image.id);
  dimension.setLargeur(image.dimension.getLargeur());
  dimension.setHauteur(image.dimension.getHauteur());

  for (int i = 0; i < dimension.getLargeur(); i++)
  {
    for (int j = 0; j < dimension.getHauteur(); j++)
      matrice[i][j] = image.matrice[i][j];
  }

  return *this;
}



////Surcharge////////////:


std::ostream& operator<< (std::ostream &out,const ImageNG &image)
{

  out <<"Nom : " << image.getNom() << std :: endl;
  out <<"ID : " << image.getId() << std :: endl;
  out <<"Largeur : " <<image.dimension.getLargeur() << std :: endl;
  out <<"Hauteur : " <<image.dimension.getHauteur() << std :: endl;
  return out;
}




ImageNG ImageNG :: operator+(int val)
{
  ImageNG Somme(*this);

  for(int i = 0; i < Somme.dimension.getLargeur(); i++)
  {
    for(int j = 0; j < Somme.dimension.getHauteur(); j++)
    {
      Somme.matrice[i][j] = Somme.matrice[i][j] + val;

      if (Somme.matrice[i][j] > 255)
        Somme.matrice[i][j] = 255;

      if (Somme.matrice[i][j] < 0)
        Somme.matrice[i][j] = 0;
    }
  }

  return Somme;
}




ImageNG operator+(int val, ImageNG image)
{
  return image + val;
}




ImageNG ImageNG :: operator-(int val)//si plus haut que 255 ont le remet a 255 idem pour negative on remet a 0
{
  ImageNG Resultat(*this);

  for(int i = 0; i < Resultat.dimension.getLargeur(); i++)
  {
    for(int j = 0; j < Resultat.dimension.getHauteur(); j++)
    {
      Resultat.matrice[i][j] = Resultat.matrice[i][j] - val;
      if (Resultat.matrice[i][j] > 255)
      {
        throw XYException("\nErreur de Resultat\n", matrice[i][j]);
        Resultat.matrice[i][j] = 255;
      }

      if (Resultat.matrice[i][j] < 0)
      {
        throw XYException("\nErreur de Resultat\n", matrice[i][j]);
        Resultat.matrice[i][j] = 0;
      }

    }
  }

  return Resultat;
}





ImageNG operator-(int val, ImageNG image)
{

  return image - val;
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
    throw XYException ("\nLes Deux dimension sont de differents taille !\n", 'd');
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
  if(dimension != image.getDimension())
  {
    throw XYException ("\nLes Deux dimension sont de differents taille !\n", 'd');
  }

  for (int i = 0; i < dimension.getLargeur(); i++)
  {
    for (int j = 0; j < dimension.getHauteur(); j++)
    {
      if (matrice[i][j] >= image.matrice[i][j]) 
      {
        return false;
      }
    }
  }
  return true;
}




bool ImageNG :: operator>(const ImageNG &image)
{
  if(dimension != image.getDimension())
  {
    throw XYException ("\nLes Deux dimension sont de differents taille !\n", 'd');
  }

  for (int i = 0; i < dimension.getLargeur(); i++)
  {
    for (int j = 0; j < dimension.getHauteur(); j++)
    {
      if (matrice[i][j] <= image.matrice[i][j]) 
      {
        return false;
      }
    }
  }
  return true;
}
