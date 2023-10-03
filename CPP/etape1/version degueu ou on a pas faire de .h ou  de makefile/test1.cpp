#include <stdlib.h>
#include <iostream>

#include<cstring>


using namespace std;
class ImageNG
{
  private:
  int id;
  char *nom;
  public:

  ImageNG()//constructeur par defaut
  {
    nom = NULL;//pour pas avoir un probleme de memorie on mallovc
    setNom("default");
    setId(1);
  }
  ImageNG(int i,const char *n)//constructeur par initiation
  {
    nom=NULL;
    setNom(n);
    setId(i);
  }


  ImageNG(const ImageNG& i)// constructeur de copie 
  {
    nom=NULL;
    setNom(i.getNom());
    setId(i.getId());
  }
  ~ImageNG()//le destructeur
  {
    if(nom)
      delete nom;
  }




void setId(int val)
{
  if(val<0)
    return;
  id=val;
}

void setNom(const char *n)
{
  if(nom)
    delete nom;
  nom=new char [strlen(n)+1];
  strcpy(nom,n);
}

int getId() const
{
  return id;
}

const char *getNom() const
{
  return nom;
}

void Affiche() const
{
  cout <<"nom:"<<nom<<" id:"<<id<<endl;
}
};


int main()
{

  cout << endl << "(1) ***** Test constructeur par defaut + Affiche *******************************************" << endl;
  {
    ImageNG image;
    image.Affiche();
  } // La presence des accolades assure que le destructeur de ImageNG sera appele --> a tracer !

  cout << endl << "(2) ***** Test des setters et getters ******************************************************" << endl;
  {
    ImageNG image;
    image.Affiche();
    image.setId(3);
    image.setNom("joconde");
    image.Affiche();
    cout << "Nom = " << image.getNom() << endl;
    cout << "Id  = " << image.getId() << endl;
  }

  cout << endl << "(3) ***** Test du constructeur d'initialisation ********************************************" << endl;
  {
    ImageNG image(6,"boat");
    image.Affiche();
  }

  cout << endl << "(4) ***** Test du constructeur de copie ****************************************************" << endl;
  {
    ImageNG image1(2,"joconde");
    cout << "image1 (AVANT) :" << endl;
    image1.Affiche();
    {   
      ImageNG image2(image1);
      cout << "image2 :" << endl;
      image2.Affiche();
      cout << "--> on modifie la copie" << endl;
      image2.setNom("superman");
      image2.Affiche();
      cout << "--> on detruit la copie" << endl;
    } // de nouveau, les {} assurent que image2 sera detruit avant la suite
    cout << "image1 (APRES) :" << endl;
    image1.Affiche();
  }

  cout << endl << "(5) ***** Test d'allocation dynamique ******************************************************" << endl;
  { // Vous n'avez rien à faire... juste comprendre et savoir expliquer!!!
    ImageNG *i = new ImageNG();
    i->Affiche();
    delete i;
    i = new ImageNG(12,"fleur");
    i->setNom("rose");
    i->Affiche();
    delete i;
  }

  return 0;
}


