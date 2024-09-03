/*#include "ImageRGB.h"
#include "MyQT.h"
#include <iostream>
using namespace std;

ImageRGB :: ImageRGB(): Image()
{
  for(int i = 0; i< dimension.getLargeur(); i++)
    for(int j = 0; j < dimension.getHauteur(); j++)
      matrice[i][j];
  cout << "--Constructeur par défaut ImageRGB" << endl;
}

ImageRGB :: ImageRGB(int id, const char *N): Image(id, N)
{
  for(int i = 0; i< dimension.getLargeur(); i++)
    for(int j = 0; j < dimension.getHauteur(); j++)
      matrice[i][j];
  cout << "-- Constructeur ImageRGB avec comme argument Id: " << id << ", Nom: " << nom << std::endl;
}

ImageRGB :: ImageRGB (const ImageRGB &imagergb): Image(imagergb)
{
  setDimension(imagergb.getDimension());

  for(int i = 0; i< dimension.getLargeur(); i++)
    for(int j = 0; j < dimension.getHauteur(); j++)
      matrice[i][j] = imagergb.matrice[i][j];

  cout << "--Constructeur par copie ImageRGB" << endl;
}

ImageRGB :: ImageRGB (int id, const char *N, const Dimension &dim) : Image(id, N, dim)
{
  for(int i = 0; i< dimension.getLargeur(); i++)
    for(int j = 0; j < dimension.getHauteur(); j++)
      matrice[i][j];
  cout << "-- Constructeur ImageRGB avec comme argument Id: " << id << ", Nom: " << N <<",Dimension:"<< dim <<std::endl;
}

ImageRGB :: ImageRGB (const char *fichier)
{
  nom = NULL;
  setNom(fichier);
  setId(0);
  MyQT::ImportFromFile(*this, fichier);
  cout << "--Constructeur par fichier ImageRGB" << endl;

}

ImageRGB :: ~ImageRGB()
{
  cout << "Destructeur ImageRGB ps:il fait rien mais c drole" << endl;

}



/////////////////////

void ImageRGB :: Affiche()const
{
  cout << "id : " <<id<< endl;
    cout << "nom : "<<nom<< endl;
    dimension.Affiche();
}

void ImageRGB :: Dessine()const
{
  MyQT::ViewImage(*this);
}

void ImageRGB :: setBackground(const Couleur &valeur)
{
  for(int i = 0; i < L_MAX; i++)
    for(int j = 0; j < H_MAX; j++)
      matrice[i][j] = valeur;
}

void ImageRGB :: setPixel(int x, int y, const Couleur &valeur)
{
  if (x < 0 || x > 256)
    return;

  if (y < 0 || y > 256)
    return;

  matrice[x][y] = valeur;
}

Couleur ImageRGB :: getPixel(int x, int y)const
{
  return matrice[x][y];
}

ImageRGB &ImageRGB :: operator =(const ImageRGB &imagergb)
{
  setNom(imagergb.nom);
  setId(imagergb.id);
  dimension.setLargeur(imagergb.getDimension().getLargeur());
  dimension.setHauteur(imagergb.getDimension().getHauteur());

  for(int i = 0; i < dimension.getLargeur(); i++)
    for(int j = 0; j < dimension.getHauteur(); j++)
      matrice[i][j] = imagergb.matrice[i][j];

  return *this;
}

ostream &operator <<(std :: ostream &out, const ImageRGB &imagergb)
{
  out <<"Nom : " << imagergb.getNom() << std :: endl;
  out <<"ID : " << imagergb.getId() << std :: endl;
  out <<"Largeur : " <<imagergb.dimension.getLargeur() << std :: endl;
  out <<"Hauteur : " <<imagergb.dimension.getHauteur() << std :: endl;
  return out;
}

void ImageRGB :: exportToFile(const char *fichier, const char *format)
{
  MyQT::ExportToFile (*this, fichier, format);
}

void ImageRGB :: importFromFile(const char *fichier)
{
  MyQT::ImportFromFile(*this, fichier);
}


*/


//////////version avec alo dynamque par chatgpt 


#include "ImageRGB.h"
#include "MyQT.h"
#include <iostream>
#include <cstring>

using namespace std;

ImageRGB::ImageRGB() : Image()
{
    initMatrice(L_MAX, H_MAX);
    cout << "--Constructeur par défaut ImageRGB" << endl;
}

ImageRGB::ImageRGB(int Id, const char *nom) : Image(Id, nom)
{
    initMatrice(L_MAX, H_MAX);
    cout << "-- Constructeur ImageRGB avec comme argument Id: " << Id << ", Nom: " << nom << std::endl;
}

ImageRGB::ImageRGB(const ImageRGB &imagergb) : Image(imagergb)
{
    initMatrice(imagergb.dimension.getLargeur(), imagergb.dimension.getHauteur());

    for (int i = 0; i < dimension.getLargeur(); i++)
        for (int j = 0; j < dimension.getHauteur(); j++)
            matrice[i][j] = imagergb.matrice[i][j];

    cout << "--Constructeur par copie ImageRGB" << endl;
}

ImageRGB::ImageRGB(int Id, const char *Nom, const Dimension &d) : Image(Id, Nom, d)
{
    initMatrice(d.getLargeur(), d.getHauteur());
    cout << "-- Constructeur ImageRGB avec comme argument Id: " << Id << ", Nom: " << Nom << ", Dimension: " << d.getLargeur() << "x" << d.getHauteur() << std::endl;
}

ImageRGB::ImageRGB(const char *fichier) : Image()
{
    nom = NULL;
    setNom(fichier);
    setId(0);
    initMatrice(L_MAX, H_MAX);
    MyQT::ImportFromFile(*this, fichier);
    cout << "--Constructeur par fichier ImageRGB" << endl;
}

ImageRGB::~ImageRGB()
{
    deleteMatrice();
    cout << "Destructeur ImageRGB" << endl;
}

void ImageRGB::initMatrice(int largeur, int hauteur)
{
    matrice = new Couleur*[largeur];
    for (int i = 0; i < largeur; i++)
    {
        matrice[i] = new Couleur[hauteur];
    }
}

void ImageRGB::deleteMatrice()
{
    for (int i = 0; i < dimension.getLargeur(); i++)
    {
        delete[] matrice[i];
    }
    delete[] matrice;
}

void ImageRGB::Affiche() const
{
    cout << "id : " << id << endl;
    cout << "nom : " << nom << endl;
    dimension.Affiche();
}

void ImageRGB::Dessine() const
{
    MyQT::ViewImage(*this);
}

void ImageRGB::setBackground(const Couleur &valeur)
{
    for (int i = 0; i < dimension.getLargeur(); i++)
        for (int j = 0; j < dimension.getHauteur(); j++)
            matrice[i][j] = valeur;
}

void ImageRGB::setPixel(int x, int y, const Couleur &valeur)
{
    if (x < 0 || x >= dimension.getLargeur() || y < 0 || y >= dimension.getHauteur())
        return;
    matrice[x][y] = valeur;
}

Couleur ImageRGB::getPixel(int x, int y) const
{
    if (x < 0 || x >= dimension.getLargeur() || y < 0 || y >= dimension.getHauteur())
        return Couleur(); // Retourne une couleur par défaut si les coordonnées sont invalides
    return matrice[x][y];
}

ImageRGB &ImageRGB::operator=(const ImageRGB &imagergb)
{
    if (this != &imagergb)
    {
        setNom(imagergb.nom);
        setId(imagergb.id);
        setDimension(imagergb.getDimension());

        for (int i = 0; i < dimension.getLargeur(); i++)
            for (int j = 0; j < dimension.getHauteur(); j++)
                matrice[i][j] = imagergb.matrice[i][j];
    }
    return *this;
}

ostream &operator<<(std::ostream &out, const ImageRGB &imagergb)
{
    out << "Nom : " << imagergb.getNom() << std::endl;
    out << "ID : " << imagergb.getId() << std::endl;
    out << "Largeur : " << imagergb.getDimension().getLargeur() << std::endl;
    out << "Hauteur : " << imagergb.getDimension().getHauteur() << std::endl;
    return out;
}

void ImageRGB::exportToFile(const char *fichier, const char *format)
{
    MyQT::ExportToFile(*this, fichier, format);
}

void ImageRGB::importFromFile(const char *fichier)
{
    MyQT::ImportFromFile(*this, fichier);
}
