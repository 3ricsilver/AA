#ifndef DIMENSION_H
#define DIMENSION_H

#include <stdlib.h>
#include <iostream>

using namespace std;

class Dimension
{
private:
	int largeur;
	int hauteur;


public:
	/*constructeur | destructeur*/
	Dimension(); 
	~Dimension();
	Dimension(int largeur,int hauteur); //const init
	Dimension(const Dimension& d); //const copie

	/*Get | Set */
	void setLargeur(int l);
	void setHauteur(int h);
	int getLargeur()const;
	int getHauteur()const;

	/*Méthode*/
	void Affiche() const;

	/*Surchage*/
	friend ostream& operator<<(ostream& s, const Dimension& dim);
	friend istream& operator>>(istream& s, Dimension& dim);

	bool operator==(const Dimension&)const;
	bool operator!=(const Dimension&)const;


	static const Dimension VGA;
	static const Dimension HD;
	static const Dimension FULL_HD;
};

#endif