#ifndef IMAGENG_H
#define IMAGENG_H

#include "Image.h"
#include "Dimension.h"
#include <iostream>

class ImageNG : public Image
{
public:


    ImageNG();
    ImageNG(int i, const char* n);
    ImageNG(int i, const char* n, const Dimension& d);
    ImageNG(const char* fichier);
    ImageNG(const ImageNG& i);
    ~ImageNG();

    // Méthodes spécifiques
    void setPixel(int x, int y, int val);
    int getPixel(int x, int y) const;
    void setBackground(int val);
    int getLuminance() const;
    int getMinimum() const;
    int getMaximum() const;
    float getContraste() const;

    // Opérateurs
    ImageNG& operator=(const ImageNG& valeur);
    friend std::ostream& operator<<(std::ostream& s, const ImageNG& valeur);
    ImageNG operator+(int valeurajouter) const;
    friend ImageNG operator+(int valeurajouter, const ImageNG& img);
    ImageNG operator-(int valeurretirer) const;
    ImageNG operator++(); // pré-incrémentation
    ImageNG operator++(int); // post-incrémentation
    ImageNG operator--(); // pré-décrémentation
    ImageNG operator--(int); // post-décrémentation
    ImageNG operator-(const ImageNG& image) const;

    // Opérateurs de comparaison
    friend bool operator==(const ImageNG& objet1, const ImageNG& objet2);
    friend bool operator>(const ImageNG& objet1, const ImageNG& objet2);
    friend bool operator<(const ImageNG& objet1, const ImageNG& objet2);

    // Méthodes virtuelles héritées
    void Affiche() const;
    void Dessine() const;
    void exportToFile(const char* fichier, const char* format);
    void importFromFile(const char* fichier);



private:
    int matrice[L_MAX][H_MAX];
};

#endif // IMAGENG_H
