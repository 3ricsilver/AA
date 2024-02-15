#include "Dimension.h"
#include <iostream>



	Dimension :: Dimension()
	{
		setLargeur(400);
		setHauteur(300);
	}

	Dimension :: Dimension(int largeur, int hauteur)
	{
		setLargeur(largeur);
		setHauteur(hauteur);
	}

	Dimension :: Dimension (const Dimension &d)
	{

		setLargeur(d.getLargeur());
		setHauteur(d.getHauteur());

	}

	void Dimension :: setLargeur (int Val) 
	{
		if (Val < 0)
			exit (0);

		Largeur = Val;
	}

	int Dimension :: getLargeur()const
	{
		return Largeur;
	}

	void Dimension :: setHauteur (int Val) 
	{
		Hauteur = Val;
	}

	int Dimension :: getHauteur()const
	{
		return Hauteur;
	}

	void Dimension :: Affiche () const
	{
		cout << "Largeur : " <<Largeur<<endl;
		cout << "Hauteur : " <<Hauteur<<endl;
	}


		//surcharge//

	std::ostream& operator<<(std::ostream& out,const Dimension &d)
	{

		out<< "Largeur : " << d.getLargeur() <<std :: endl;
		out<< "Hauteur : " << d.getHauteur() <<std :: endl;
		return out;
	}

	std::istream& operator>> (std::istream& in, Dimension &d)
	{
		int temporaire_A, temporaire_B;

		in >> temporaire_A >> temporaire_B;

		d.setLargeur(temporaire_A);
		d.setHauteur(temporaire_B);

		return in;	
	}




	bool Dimension:: operator==(const Dimension &d)
	{
		return (getLargeur() == d.getLargeur()) && (getHauteur() == d.getHauteur());
	}

	bool Dimension:: operator!=(const Dimension &d)
	{
		return (getLargeur() != d.getLargeur()) || (getHauteur() != d.getHauteur());
	}



	//hardcoder//

	const Dimension Dimension :: VGA(640, 480);
	const Dimension Dimension :: HD (1280, 720);
	const Dimension Dimension :: FULL_HD(1920,1080);