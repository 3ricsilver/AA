#ifndef COULEUR_H
#define COULEUR_H

#include <iostream>


using namespace std;

class Couleur
{
	private:

		int rouge, vert,bleu;


	public:
		/*constructeur | destructeur*/
		Couleur();
		Couleur(int r, int v, int b);
		~Couleur();

		/*Get | Set */
		void setRouge(int);
		void setVert(int);
		void setBleu(int);

		int getRouge()const;
		int getVert()const;
		int getBleu()const;

		/*Affichage*/
		
		friend ostream& operator<<(ostream& s, const Couleur& img);

		void Affiche()const;

		/* truc hardcoder */
		static const Couleur ROUGE;
		static const Couleur VERT;
		static const Couleur BLEU;
		static const Couleur BLANC;
		static const Couleur NOIR;
};

#endif