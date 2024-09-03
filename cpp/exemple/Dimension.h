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
	Dimension(); 
	~Dimension();
	Dimension(int ,int); //const init
	Dimension(const Dimension& d); //const copie


	void setLargeur(int);
	void setHauteur(int);
	int getLargeur()const;
	int getHauteur()const;
	void Affiche() const;

	static const Dimension VGA;
	static const Dimension HD;
	static const Dimension FULL_HD;

	friend ostream& operator<<(ostream& s, const Dimension& dim);
	friend istream& operator>>(istream& s, Dimension& dim);

	bool operator==(const Dimension&)const;
	bool operator!=(const Dimension&)const;
};

#endif