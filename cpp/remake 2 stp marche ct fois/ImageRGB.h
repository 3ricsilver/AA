/*#ifndef IMAGERGB_H
#define IMAGERGB_H

#include "Image.h"
#include "Dimension.h"
#include <iostream>

#include "Couleur.h"
class MyQT;

class ImageRGB : public Image
{
    private:
    Couleur matrice[L_MAX][H_MAX];

    public:

    ImageRGB(int id, const char* N);                        
    ImageRGB(const ImageRGB& image1);                       
    ImageRGB(int id, const char* N, const Dimension& dim);
    ImageRGB(const char* fichier);
    ImageRGB();
    ~ImageRGB();

    void setBackground(const Couleur& color);
    void setPixel(int x, int y, const Couleur& color);
    Couleur getPixel(int x, int y) const;

    void Affiche() const;
    void Dessine() const;

    void importFromFile(const char* fichier);
    void exportToFile(const char* fichier, const char* format);

    ImageRGB& operator=(const ImageRGB& image);
    friend std::ostream& operator<<(std::ostream& s,const ImageRGB& image);

    //maybe c ca le core dump


};

#endif 
*/

//au finale jsp pourquoi mais il y a que avec l'allocation dynamique que ca marche alors que a l'époque j'avais réusssi sans
#ifndef IMAGERGB_H
#define IMAGERGB_H

#include "Image.h"
#include "Dimension.h"
#include "Couleur.h"
#include <iostream>

class MyQT;

class ImageRGB : public Image
{
private:
    Couleur** matrice;  // Utilisation d'un pointeur de pointeurs pour la matrice

public:
    ImageRGB(int id, const char* N);
    ImageRGB(const ImageRGB& image1);
    ImageRGB(int id, const char* N, const Dimension& dim);
    ImageRGB(const char* fichier);
    ImageRGB();
    ~ImageRGB();

    void setBackground(const Couleur& color);
    void setPixel(int x, int y, const Couleur& color);
    Couleur getPixel(int x, int y) const;

    void Affiche() const;
    void Dessine() const;

    void importFromFile(const char* fichier);
    void exportToFile(const char* fichier, const char* format);

    ImageRGB& operator=(const ImageRGB& image);
    friend std::ostream& operator<<(std::ostream& s, const ImageRGB& image);

private:
    void initMatrice(int largeur, int hauteur);
    void deleteMatrice();
};

#endif
