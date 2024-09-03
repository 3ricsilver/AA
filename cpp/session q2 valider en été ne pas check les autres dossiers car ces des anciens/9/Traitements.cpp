
#include "Traitements.h"

#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <algorithm>

/* methodes d'instance*/


ImageB Traitements::Seuillage(const ImageNG& imageIn, int seuil)
{
	Dimension dimension=imageIn.getDimension();
	ImageB image2;
	char buffer[100]; 
	image2.setId(imageIn.getId());
	image2.setNom(imageIn.getNom());
	strcpy(buffer, (char*)imageIn.getNom());
	strcat(buffer, "  seuil-");
	sprintf(buffer + strlen(buffer), "%d", seuil);

	image2.setNom(buffer);
	image2.setDimension(imageIn.getDimension());
	for(int x=0; x<dimension.getLargeur(); x++ )
	{	
		for(int y=0; y<dimension.getHauteur();y++)
		{
			
			if(imageIn.getPixel(x,y)< seuil)
			{
				image2.setPixel(x,y,false);

			}
			else
				
				image2.setPixel(x,y,true);
		}
	}
	return image2;
}

ImageNG Traitements::FiltreMoyenneur(const ImageNG& imageIn, int taille)
{
	if(taille%2==0|| taille<3)
		return imageIn;

	int largeur= imageIn.getDimension().getLargeur();
	int hauteur= imageIn.getDimension().getHauteur();

	string ancienNom = string(imageIn.getNom());
	string nouveauNom= ancienNom+"-moyenne" + to_string(taille);
	
	ImageNG imageOut(imageIn.getId(),nouveauNom.c_str(),imageIn.getDimension());

	for(int x=0; x<largeur; x++)
	{
		for(int y=0; y<hauteur;y++)
		{
			int sommePixels=0;
			int nombrePixels=0;
			

			for(int i=-taille/2; i<=taille/2; i++)
				for(int j=-taille/2;j<=taille/2;j++)
				{
					int dx=x+i;
					int dy= y+j;
					if(dx>=0 &&dx< largeur && dy>=0 &&dy<hauteur)
					{
						sommePixels=sommePixels+ imageIn.getPixel(dx,dy);
						nombrePixels++;
					}
				}

			int moyenne= sommePixels/nombrePixels;
			imageOut.setPixel(x,y,moyenne);
		}
	}
	return imageOut;

}
ImageNG Traitements::FiltreMedian(const ImageNG& imageIn, int taille)
{	
	if(taille%2==0|| taille<3)
		return imageIn;

	int largeur= imageIn.getDimension().getLargeur();
	int hauteur= imageIn.getDimension().getHauteur();

	string ancienNom = string(imageIn.getNom());
	string nouveauNom= ancienNom+"-mediane" + to_string(taille);
	
	ImageNG imageOut(imageIn.getId(),nouveauNom.c_str(),imageIn.getDimension());

	for(int x=0; x<largeur; x++)
	{
		for(int y=0; y<hauteur;y++)
		{
			
			vector<int> VecPixels;
			for(int i=-taille/2; i<=taille/2; i++)
				for(int j=-taille/2;j<=taille/2;j++)
				{
					int dx=x+i;
					int dy= y+j;
					
					
					if(dx>=0 &&dx< largeur && dy>=0 &&dy<hauteur)
					{
						VecPixels.push_back(imageIn.getPixel(dx,dy));
					}

				}

			sort(VecPixels.begin(),VecPixels.end());
			int mediane=VecPixels[VecPixels.size()/2];
			
			imageOut.setPixel(x,y,mediane);
		}
	}
	return imageOut;

}

ImageNG Traitements::Erosion(const ImageNG& imageIn, int taille)
{	
	if(taille%2==0|| taille<3)
		return imageIn;

	int largeur= imageIn.getDimension().getLargeur();
	int hauteur= imageIn.getDimension().getHauteur();

	string ancienNom = string(imageIn.getNom());
	string nouveauNom= ancienNom+"-errosion" ;
	
	ImageNG imageOut(imageIn.getId(),nouveauNom.c_str(),imageIn.getDimension());

	for(int x=0; x<largeur; x++)
	{
		for(int y=0; y<hauteur;y++)
		{
			
			int min=255;
			for(int i=-taille/2; i<=taille/2; i++)
				for(int j=-taille/2;j<=taille/2;j++)
				{
					int dx=x+i;
					int dy= y+j;
					
					
					if(dx>=0 &&dx< largeur && dy>=0 &&dy<hauteur)
					{
						if(min>imageIn.getPixel(dx,dy))
							min=imageIn.getPixel(dx,dy);
					}

				}

			
			
			imageOut.setPixel(x,y,min);
		}
	}
	return imageOut;

}

ImageNG Traitements::Dilatation(const ImageNG& imageIn, int taille)
{	
	if(taille%2==0|| taille<3)
		return imageIn;

	int largeur= imageIn.getDimension().getLargeur();
	int hauteur= imageIn.getDimension().getHauteur();

	string ancienNom = string(imageIn.getNom());
	string nouveauNom= ancienNom+"-dilatation" ;
	
	ImageNG imageOut(imageIn.getId(),nouveauNom.c_str(),imageIn.getDimension());

	for(int x=0; x<largeur; x++)
	{
		for(int y=0; y<hauteur;y++)
		{
			
			int max=0;
			for(int i=-taille/2; i<=taille/2; i++)
				for(int j=-taille/2;j<=taille/2;j++)
				{
					int dx=x+i;
					int dy= y+j;
					
					
					if(dx>=0 &&dx< largeur && dy>=0 &&dy<hauteur)
					{
						if(max<imageIn.getPixel(dx,dy))
							max=imageIn.getPixel(dx,dy);
					}

				}

			
			
			
			imageOut.setPixel(x,y,max);
		}
	}
	return imageOut;

}


ImageNG Traitements::Negatif(const ImageNG& imageIn)
{
	int largeur= imageIn.getDimension().getLargeur();
	int hauteur= imageIn.getDimension().getHauteur();
	int nvg;
	string ancienNom = string(imageIn.getNom());
	string nouveauNom= ancienNom+"negatif";
	ImageNG imageOut(imageIn.getId(),nouveauNom.c_str(),imageIn.getDimension());
	for(int x=0; x<largeur; x++)
	{
		for(int y=0; y<hauteur;y++)
		{
			nvg=imageIn.getPixel(x,y);
			imageOut.setPixel(x,y,255-nvg);
		}
	}
	return imageOut;
}