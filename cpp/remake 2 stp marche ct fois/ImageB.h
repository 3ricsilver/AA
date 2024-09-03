#ifndef IMAGEB_H
#define IMAGEB_H

#include "Image.h"
#include "Dimension.h"
#include "Couleur.h" // Ajout de cette ligne pour inclure Couleur
#include <iostream>

class MyQT;

class ImageB : public Image
{
public:


    static Couleur couleurTrue;
    static Couleur couleurFalse; 

    ImageB();
    ImageB(int i, const char* n);
    ImageB(int i, const char* n, const Dimension& d);
    ImageB(const char* fichier);
    ImageB(const ImageB& i);
    ~ImageB();

    // Méthodes spécifiques
    void setPixel(int x, int y, int val);
    int getPixel(int x, int y) const;
    void setBackground(int val);

    // Opérateurs
    ImageB& operator=(const ImageB& valeur);
    friend std::ostream& operator<<(std::ostream& s, const ImageB& valeur);

    // Opérateurs de comparaison
    friend bool operator==(const ImageB& objet1, const ImageB& objet2);
    friend bool operator>(const ImageB& objet1, const ImageB& objet2);
    friend bool operator<(const ImageB& objet1, const ImageB& objet2);

    // Méthodes virtuelles héritées
    void Affiche() const;
    void Dessine() const;
    void exportToFile(const char* fichier, const char* format);

private:
    bool matrice[L_MAX][H_MAX];
};

#endif // IMAGEB_H
