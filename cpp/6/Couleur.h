#include <iostream>
#include <cstring>
#include "Image.h"
#include "RGBException.h"
using namespace std;

#ifndef COULEUR_H
#define COULEUR_H

class Couleur 
{
	public:
		static const Couleur BLEU;
		static const Couleur ROUGE;
		static const Couleur VERT;
		static const Couleur NOIR;
		static const Couleur BLANC;

		//constructeur//
		Couleur();
		Couleur(int bleu, int rouge, int vert);
		Couleur(const Couleur &couleur);


		//getter//
		int getBleu() const;
		int getRouge() const;
		int getVert() const;

		//setter//
		void setVert(int val);
		void setRouge(int val);
		void setBleu(int val);

		//surcharge//
		friend std::ostream& operator<< (std::ostream &out,const Couleur &couleur);
		
		//methode//
		void Affiche()const;



	private:
		int Bleu;
		int Rouge;
		int Vert;


};
#endif