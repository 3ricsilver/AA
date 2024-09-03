#include "ImageB.h"
#include "Couleur.h"
#include <iostream>
#include <cstring>

#include "MyQT.h"

// Définition des couleurs statiques
Couleur ImageB::couleurTrue = Couleur(255, 255, 255); // Blanc
Couleur ImageB::couleurFalse = Couleur(0, 0, 0); // Noir

ImageB::ImageB() : Image()
{
    setBackground(false);
    std::cout << "Constructeur par défaut ImageB" << std::endl;
}

ImageB::ImageB(int i, const char* n) : Image(i, n)
{
    setBackground(false);
    std::cout << "Constructeur avec Id et Nom ImageB" << std::endl;
}

ImageB::ImageB(int i, const char* n, const Dimension& d) : Image(i, n, d)
{
    if (d.getLargeur() > L_MAX || d.getHauteur() > H_MAX)
    {
        throw std::out_of_range("Dimensions exceed maximum allowed size");
    }
    setBackground(false);
    std::cout << "Constructeur avec Id, Nom et Dimension ImageB" << std::endl;
}

ImageB::ImageB(const char* fichier) : Image(fichier)
{
    setBackground(false);
    // Implémentation fictive de l'importation du fichier pour ImageB
    std::cout << "Constructeur par fichier ImageB" << std::endl;
}

ImageB::ImageB(const ImageB& i) : Image(i)
{
    for (int x = 0; x < dimension.getLargeur(); x++)
    {
        for (int y = 0; y < dimension.getHauteur(); y++)
        {
            matrice[x][y] = i.matrice[x][y];
        }
    }
    std::cout << "Constructeur par copie ImageB" << std::endl;
}

ImageB::~ImageB()
{
    std::cout << "Destructeur ImageB" << std::endl;
}

void ImageB::setPixel(int x, int y, int val)
{
    if (x >= 0 && x < dimension.getLargeur() && y >= 0 && y < dimension.getHauteur())
    {
        matrice[x][y] = (val != 0);
    }
}

int ImageB::getPixel(int x, int y) const
{
    if (x >= 0 && x < dimension.getLargeur() && y >= 0 && y < dimension.getHauteur())
    {
        return matrice[x][y];
    }
    return 0; // Valeur par défaut si l'index est hors limites
}

void ImageB::setBackground(int val)
{
    for (int i = 0; i < dimension.getLargeur(); i++)
    {
        for (int j = 0; j < dimension.getHauteur(); j++)
        {
            matrice[i][j] = (val != 0);
        }
    }
}

void ImageB::Affiche() const
{
    std::cout << "Id: " << id << std::endl;
    std::cout << "Nom: " << nom << std::endl;
    dimension.Affiche();
}

void ImageB::Dessine() const
{
    MyQT::ViewImage(*this);
}

void ImageB::exportToFile(const char* fichier, const char* format)
{
    // Implémentation fictive de l'exportation vers un fichier pour ImageB
    std::cout << "Exportation de l'image vers le fichier: " << fichier << " au format: " << format << std::endl;
}

ImageB& ImageB::operator=(const ImageB& valeur)
{
    if (this != &valeur)
    {
        setNom(valeur.nom);
        setId(valeur.id);
        setDimension(valeur.dimension);

        for (int i = 0; i < dimension.getLargeur(); i++)
        {
            for (int j = 0; j < dimension.getHauteur(); j++)
            {
                matrice[i][j] = valeur.matrice[i][j];
            }
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& s, const ImageB& valeur)
{
    s << "Id: " << valeur.getId() << std::endl;
    s << "Nom: " << valeur.getNom() << std::endl;
    s << "Dimension: " << valeur.dimension.getLargeur() << "x" << valeur.dimension.getHauteur() << std::endl;
    return s;
}

bool operator==(const ImageB& objet1, const ImageB& objet2)
{
    if (objet1.id != objet2.id || strcmp(objet1.nom, objet2.nom) != 0 || !(objet1.dimension == objet2.dimension))
    {
        return false;
    }

    for (int i = 0; i < objet1.dimension.getLargeur(); i++)
    {
        for (int j = 0; j < objet1.dimension.getHauteur(); j++)
        {
            if (objet1.matrice[i][j] != objet2.matrice[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool operator>(const ImageB& objet1, const ImageB& objet2)
{
    // Implémentation d'une comparaison personnalisée
    return objet1.id > objet2.id;
}

bool operator<(const ImageB& objet1, const ImageB& objet2)
{
    // Implémentation d'une comparaison personnalisée
    return objet1.id < objet2.id;
}
