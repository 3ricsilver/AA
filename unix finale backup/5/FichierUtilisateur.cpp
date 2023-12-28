#include "FichierUtilisateur.h"
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>


int estPresent(const char* nom)
{
  UTILISATEUR temps;
  int posi=1,fd;
  if((fd=open(FICHIER_UTILISATEURS,O_RDONLY))==-1)
  {
  return -1;//fichier est null
  }
  while((read(fd,&temps,sizeof(UTILISATEUR))) ==sizeof(UTILISATEUR))
  {
    if(strcmp(temps.nom,nom)==0)
    {
      close(fd);
      return posi;
    }
    posi++;
  }

  return 0;

}

////////////////////////////////////////////////////////////////////////////////////
int hash(const char* motDePasse)
{
  int longueurtemp;
  int hashvaleur=0;
  if(motDePasse==NULL)
  {
    return -1;//le mdp est nulle
  }
  
  //a faire
  longueurtemp=strlen(motDePasse);//obtient la longueur des phrases et est stocker dans longueur temps
  for(int i =0 ; i< longueurtemp;i++)//en gros on incremente jusqu'a la fin du mot
  {
    hashvaleur+=(i+1)*(int)(motDePasse[i]);// en gros on fait i+1 * (int)motdepasse[i] pour reconvertir les caracteres en chiffres

  }
  hashvaleur=hashvaleur%97;
  return hashvaleur;

}

////////////////////////////////////////////////////////////////////////////////////
void ajouteUtilisateur(const char* nom, const char* motDePasse)
{
  int fd;
  UTILISATEUR user;
  if((fd=open(FICHIER_UTILISATEURS,O_WRONLY|O_APPEND))==-1)
    if((fd=open(FICHIER_UTILISATEURS,O_WRONLY|O_APPEND|O_CREAT|O_EXCL,0777))==-1)// en gros on utilise ou wronly c'est équivalent fread | o_creat  cration fichier si inexistant | o_append ecriture en fin de fichier
        exit(1);//Excl renvoie -1 si peut pas créer de fichier 0777 droit maximun

  strcpy(user.nom,nom);
  user.hash = hash(motDePasse);
  write(fd,&user,sizeof(UTILISATEUR));// fichier message taille
  close(fd);
}

////////////////////////////////////////////////////////////////////////////////////
int verifieMotDePasse(int pos, const char* motDePasse)
{
  UTILISATEUR temps;
  int tmpmdp;
  int fd;
  if((fd=open(FICHIER_UTILISATEURS,O_RDONLY))==-1)//ouvre le ficher 
    return -1;

  lseek(fd, (pos-1) * sizeof(UTILISATEUR), SEEK_SET); // Se déplace à la position spécifiée //TESTER AVEC POS -1 car je suis 1 décalé
  read(fd, &temps, sizeof(UTILISATEUR));

  tmpmdp=hash(motDePasse);

  if(temps.hash == tmpmdp)
  {
    close(fd);
    return 1;
  }

  close(fd);

  return 0;

  
}

////////////////////////////////////////////////////////////////////////////////////
int listeUtilisateurs(UTILISATEUR *vecteur) // le vecteur doit etre suffisamment grand
{
  int fd;
  if ((fd = open(FICHIER_UTILISATEURS, O_RDONLY)) == -1)//on veut que lire
  {
    return -1; // Le fichier est nul donc retourne -1
  }

  int i = 0;
  while (read(fd, &vecteur[i], sizeof(UTILISATEUR)) == sizeof(UTILISATEUR))//tant qu'il peut lire un truc de la taille d'utilisateur
  {
    i++;
  }
  close(fd);
  return i;
}


/////////////////////////////////////////////////////////////////////////////////////////

void changeMotDePasse(int pos, const char* nouveauMotDePasse)
{
  UTILISATEUR temps;
  int fd;
  if((fd=open(FICHIER_UTILISATEURS,O_RDWR))==-1 && strcmp(nouveauMotDePasse,"")==0)//ouvre le ficher en mode lecture et écriture && c'est la verif que demande le prof si l'utilisateur rentre rien
  {
    exit(1);
  }

  lseek(fd, (pos-1) * sizeof(UTILISATEUR), SEEK_SET); // Se déplace à la position spécifiée //TESTER AVEC POS -1 car je suis 1 décalé

  // Mettre à jour le mot de passe
  temps.hash = hash(nouveauMotDePasse);

  // Écrire la structure mise à jour dans le fichier
  if (write(fd, &temps, sizeof(UTILISATEUR)) != sizeof(UTILISATEUR))
  {
    close(fd);
    exit(1);
  }

  close(fd);
}
