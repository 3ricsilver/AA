#include "Dimension.h"
#include <iostream>
#include "XYException.h"

//contructeur//
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
//setter et getter// // eric du futur ne  add pas une verif si au dessus de 700 car ca core dump a cause des valeurs hd et etc
	void Dimension :: setLargeur (int Val) 
	{
		if (Val < 0 )
		{
			throw XYException('x',"Valeur de la Largeur Invalide\n");
		}

		Largeur = Val;
	}

	void Dimension :: setHauteur (int Val) 
	{
		if (Val < 0 )
		{
			throw XYException('y',"Valeur de la Hauteur Invalide\n");
		}		
		Hauteur = Val;
	}

	int Dimension :: getHauteur()const
	{
		return Hauteur;
	}

	int Dimension :: getLargeur()const
	{
		return Largeur;
	}


//méthode//
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

	std::istream& operator>> (std::istream& cin, Dimension &d)
	{
		int temp1, temp2;
		cout << "Largeur x Hauteur : ";
		cin >> temp1 >> temp2;

		if((temp1 < 0 || temp1 > 700) && (temp2 < 0 || temp2 > 700))
		{

			throw XYException('d',"\nLa Largeur et La Hauteur est invalide !");
		}

		if(temp1 < 0 || temp1 > 700)
		{
			throw XYException('x',"\nLa Largeur est invalide !");
		}

		if(temp2 < 0 || temp2 > 700)
		{
			throw XYException('y',"\n La Hauteur est invalide !");
		}

		d.setLargeur(temp1);
		d.setHauteur(temp2);

		return cin;	
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