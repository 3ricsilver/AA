#ifndef DIMENSIONNG_H //si pas definit on le definit sinon osef car on va boucler
#define DIMENSIONNG_H


class Dimension
{
    private:
      int Hauteur;
      int Largeur;


    public:
      Dimension();
      Dimension(int Hauteur,int Largeur);
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
};


#endif