#ifndef COULEUR_H
#define COULEUR_H

#include <iostream>

class Couleur {
private:
    int rouge;
    int vert;
    int bleu;

public:
    // Constructeur par défaut
    Couleur();
    // Constructeur avec paramètres
    Couleur(int r, int v, int b);
    // Constructeur de copie
    Couleur(const Couleur &c);

    // Accesseurs
    int getRouge() const;
    int getVert() const;
    int getBleu() const;

    // Mutateurs
    void setRouge(int r);
    void setVert(int v);
    void setBleu(int b);

    // Opérateur << pour l'affichage
    friend std::ostream& operator<<(std::ostream &out, const Couleur &c);

    void Affiche()const;

    // Couleurs principales
    static const Couleur ROUGE;
    static const Couleur VERT;
    static const Couleur BLEU;
    static const Couleur BLANC;
    static const Couleur NOIR;
};

#endif // COULEUR_H
