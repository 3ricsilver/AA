#ifndef COULEUR_H
#define COULEUR_H


#include <iostream>




////////////////////

class Couleur
{
	public:
		////constructeur///
		//par Défaut//
		Couleur();

		//le reste des constructeurw//

		Couleur(int rouge,int vert,int bleu);
		Couleur(const Couleur &couleur);

		//Destructeur CR7//
		~Couleur();
		////setter//
		void setRouge(int val);
		void setVert(int val);
		void setBleu(int val);
		////getter////
		int getBleu()const;
		int getRouge()const;
		int getVert()const;

		//Affichage//

		void Affiche() const;
		//Operateur//
		friend std::ostream& operator<<(std::ostream& s,const Couleur& valeur); 




		//Couleur//
		static const Couleur NOIR;
		static const Couleur BLEU;
		static const Couleur VERT;
		static const Couleur ROUGE;
		static const Couleur BLANC;

	private:
		
		int rouge,vert,bleu;





};

#endif