#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
using namespace std;


#ifndef DIMENSION_H
#define DIMENSION_H

class Dimension
{

	private:
	 	int Largeur;
	 	int Hauteur;

	public:



		//constructeur//
	 	Dimension();
	 	Dimension(int largeur, int hauteur)noexcept (false);
	 	Dimension (const Dimension &d);

	 	///////////////

	 	void setLargeur(int Val)noexcept(false);//CA DIT QUE LA FONCTION PEUT LANCER UNE EXCEPTION
	 	int getLargeur()const;
	 	void setHauteur(int Val)noexcept (false);
	 	int getHauteur()const;
	 	void Affiche() const;
	 	
	 	//surcharge//

	 	friend std::ostream& operator<<(std::ostream& out,const Dimension &d);
	 	friend std::istream& operator>> (std::istream& in, Dimension &d)noexcept (false);
	 	bool operator==(const Dimension &d);
    	bool operator!=(const Dimension &d);
	 	
    	//hardcoder//
    	static  const Dimension VGA;
	 	static const Dimension HD;
	 	static const Dimension FULL_HD;


};


#endif