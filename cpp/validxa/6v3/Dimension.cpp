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

	//setter && getter//

	void Dimension :: setLargeur (int Val) 
	{
		if (Val <= 0)
		{
			throw XYException("\nErreur de Largeur !\n", Val);
		}
		else
		{
 			Largeur = Val;
		}

	}


	void Dimension :: setHauteur (int Val) 
	{
		if(Val <=0)
		{
			throw XYException("\nErreur de Hauteur !\n", Val);			
		}
		else
		{
 			Hauteur = Val;
		}
	}

	int Dimension :: getHauteur()const
	{
		if(Hauteur <= 0 || Hauteur >= 700)
		{
			throw XYException("\nErreur de Hauteur !\n", Hauteur);
		}
		else
		{
			return Hauteur;
		}
	}

	int Dimension :: getLargeur()const
	{
		if(Largeur <= 0 || Largeur >= 700)
		{
			throw XYException("\nErreur de Largeur !\n", Hauteur);
		}
		else
		{
			return Largeur;
		}
	}


	//Méthode//

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
		int temp1, temp2;

		cout << "Entrer la Largeur : ";
		cin >> temp1;

		cout << "Entrer la Hauteur : ";
		cin >> temp2;


		if(temp1 < 0 || temp1 > 700)
		{
			throw XYException("\nErreur de Largeur !\n", temp1);
		}

		if(temp2 < 0 || temp2 > 700)
		{
			throw XYException("\nErreur de Hauteur !\n", temp2);
		}

		d.setLargeur(temp1);
		d.setHauteur(temp2);

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