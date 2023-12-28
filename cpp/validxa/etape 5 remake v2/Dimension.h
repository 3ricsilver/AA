#ifndef DIMENSIONNG_H //si pas definit on le definit sinon osef car on va boucler
#define DIMENSIONNG_H
#include <iostream>


class Dimension
{
    private:
      int Hauteur;
      int Largeur;

      int compD(const Dimension& d);


    public:
      Dimension();
      Dimension(int Largeur,int Hauteur);
      Dimension(const Dimension& i);
      ~Dimension();
      void setHauteur(int val);
      void setLargeur(int val);
      int getHauteur()const;
      int getLargeur()const;

      void Affiche() const;


      static const Dimension VGA;
      static const Dimension HD;
      static const Dimension FULL_HD;
    //////operateur///////////
      friend std::ostream& operator<<(std::ostream& os, const Dimension& dim);
      friend std::istream& operator>>(std::istream& is,Dimension& dim);

      ///operateur comparaison///

      friend bool operator==(Dimension const& objet1, Dimension const& objet2);
      friend bool operator!=(Dimension const& objet1, Dimension const& objet2);

};


#endif