#include "Couleur.h"
using namespace std;


// Initialisation des couleurs principales
const Couleur Couleur::ROUGE(255, 0, 0);
const Couleur Couleur::VERT(0, 255, 0);
const Couleur Couleur::BLEU(0, 0, 255);
const Couleur Couleur::BLANC(255, 255, 255);
const Couleur Couleur::NOIR(0, 0, 0);

// Constructeur par défaut
Couleur::Couleur() : rouge(0), vert(0), bleu(0) {}

// Constructeur avec paramètres
Couleur::Couleur(int r, int v, int b) : rouge(r), vert(v), bleu(b) {}

// Constructeur de copie
Couleur::Couleur(const Couleur &c) : rouge(c.rouge), vert(c.vert), bleu(c.bleu) {}

// Accesseurs
int Couleur::getRouge() const 
{
    return rouge;
}

int Couleur::getVert() const 
{
    return vert;
}

int Couleur::getBleu() const 
{
    return bleu;
}

// Mutateurs
void Couleur::setRouge(int r) 
{
    rouge = r;
}

void Couleur::setVert(int v) 
{
    vert = v;
}

void Couleur::setBleu(int b) 
{
    bleu = b;
}

// Opérateur << pour l'affichage
std::ostream& operator<<(std::ostream &out, const Couleur &c) 
{
    out << "Rouge: " << c.rouge << ", Vert: " << c.vert << ", Bleu: " << c.bleu;
    return out;
}

void Couleur :: Affiche()const
{
    cout <<"Bleu : " << bleu << endl;
    cout <<"Rouge : " << rouge << endl;
    cout <<"Vert : " << vert << endl;

}