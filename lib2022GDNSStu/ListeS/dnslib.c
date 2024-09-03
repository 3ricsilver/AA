#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "dnslib.h"

typedef struct item
{
struct item *next;
void *data;
} item_s;

struct sll
{
item_s *p_start;
item_s *list;
item_s *save;
};

void sll_save(struct sll *p_l )
{
 p_l->save = p_l->list ;
}

void sll_restore(struct sll *p_l )
{
 p_l->list = p_l->save   ;
}

sll_s *sll_new (void)
{
 // VERSION 2022
sll_s *p_sll = malloc (sizeof *p_sll);
if (p_sll)
	{
	item_s *p_l = malloc (sizeof *p_l);
	if (p_l)
		{
		p_l->data = NULL;
		p_l->next = NULL;
		p_sll->p_start = p_l;
		p_sll->list = NULL;
		}
	else
		{
		fprintf (stderr, "Memoire insufisante\n");
		exit (EXIT_FAILURE);
		}
	}
else
	{
	fprintf (stderr, "Memoire insufisante\n");
	exit (EXIT_FAILURE);
	}
return p_sll;
}


void sll_insert (sll_s * p_sll, void *data)
{
if (p_sll)
{
item_s *p_l = p_sll->list;
item_s *p_n = NULL;
p_n = malloc (sizeof (*p_n));
if (p_n)
   {
    p_n->data = data;
    if (p_l == NULL) // Premier élément
       {
        p_sll->p_start->next = p_n;
        p_n->next = NULL;
       }
    else
       {
        p_n->next = p_l->next;
        p_l->next = p_n;
       }
    p_sll->list = p_n;
   }
else
	{
	 fprintf (stderr, "Memoire insuffisante\n");
	 exit (EXIT_FAILURE);
	}
}
}
void sll_removeNext (sll_s * p_sll) // FIXED
{
if (p_sll && p_sll->list)
{
item_s *p_l = p_sll->list;
item_s *p_n = NULL;
p_n = p_l->next;
if (p_n) // ENCOREPLUS d'un ELEMENT DANS LA LISTE
   {
    p_l->next = p_n->next;
    free (p_n);
    sll_last( p_sll) ; // On repointe sur le dernier
   }
}
}


void sll_removeFirst (sll_s * p_sll)
{
if (p_sll)
{
p_sll->list = p_sll->p_start;
sll_removeNext (p_sll);
}
}
void sll_next (sll_s * p_sll)
{
if (p_sll && p_sll->list)
{
p_sll->list = p_sll->list->next;
}
}
void *sll_data (sll_s * p_sll)
{
return ((p_sll && p_sll->list) ? p_sll->list->data : NULL);
}
void sll_first (sll_s * p_sll)
{
if (p_sll)
{
p_sll->list = p_sll->p_start->next;
}
}

void sll_last (sll_s * p_sll){
    if (p_sll){
     p_sll->list = p_sll->p_start ; // On pointe sur le premier

        while (p_sll->list->next != NULL){
        sll_next (p_sll);
        }
    }
}

size_t sll_sizeof (sll_s * p_sll){
size_t n = 0;
item_s *tempo ;
tempo = p_sll->list ;

if (p_sll){
    sll_first (p_sll);

    while (p_sll->list != NULL){
        n++;
        sll_next (p_sll);
    }
}
p_sll->list = tempo ;
return n;
}


void sll_delete (sll_s ** pp_sll)
{
if (pp_sll && *pp_sll)
{
sll_first (*pp_sll);
while ((*pp_sll)->list->next != NULL)
{
sll_removeNext (*pp_sll);
}
sll_removeFirst (*pp_sll);
free ((*pp_sll)->list);
(*pp_sll)->list = NULL;
free (*pp_sll), *pp_sll = NULL;
}
}


char* SuffixeDe(char *Suffixe, char* Chaine)
{
int LongSuffixe,LongChaine ;
// on compare les chaines Ã partir de la fin
LongSuffixe=strlen(Suffixe) ;
LongChaine=strlen(Chaine) ;
if (LongSuffixe == 0 || LongChaine == 0 )
return NULL ;
Suffixe= Suffixe + LongSuffixe-1 ;
Chaine= Chaine + LongChaine-1 ;
while ( LongChaine && LongSuffixe && *Suffixe==*Chaine )
{
LongSuffixe-- ;
LongChaine-- ;
Suffixe-- ;
Chaine-- ;
}
if (LongSuffixe)
return NULL ;
else
return (Chaine+1) ;
}

char* SepareHoteDomaine(char *FQDN, char** Domaine)
{
 char *Start  ;
 int TrouvePoint  ;

 Start = FQDN ;
 TrouvePoint=0 ;
 while(*FQDN )
 {
   if ( (*FQDN) == '.' )
   {
        *FQDN = 0 ;
	*Domaine = ++FQDN ;
	TrouvePoint = 1 ;
	break ;
   }
  FQDN++ ;
 }
 if (!TrouvePoint)
    return 0 ;
 else
    return Start ;
}

void EnleveGL( char *Chaine)
{
  char *DebutCopie,*DebutChaine, *Copie ;
  DebutCopie = (char *) malloc(strlen(Chaine)+1) ;
  DebutChaine = Chaine ;
  Copie = DebutCopie ;
  while(*Chaine!=0)
  {
   if ( *Chaine=='"' )
      Chaine++ ; /* on ne recopie pas les guillements */
   else
   {
      *Copie++ = *Chaine++ ;
   }
  }
  *Copie=0 ;
  strcpy(DebutChaine,DebutCopie) ;
//  printf("EnleveGL#%s#\n",DebutChaine) ;
  return ;
}

void Enleve1013(char *Chaine)
{
 while(*Chaine != 0)
 {
  if ( (*Chaine== 10) || (*Chaine==13) )
     {
       *Chaine = 0 ;
       return ;
     }
  Chaine++ ;
 }
}



int 	Ipv4ToArray(char *strsource,int Membre[4])
{
 char   dt[4] ;
 int	NumeroMembre,NombreDigits ;
 int	i,s,lg ;
 char   str[16] ; /* pour ne pas alterer l'original */
 i = 0 ;
 s = 0 ;
 NumeroMembre = 0 ;
 NombreDigits = 0 ;
 memset(Membre,0,sizeof (int) * 4) ;
 lg = strlen(strsource) ;
 strncpy(str,strsource,16) ;
 while (i<=lg)  /* Il faut traiter aussi le 0 de fin de chaine */
 {
  if (isdigit(str[i]))
    NombreDigits++ ;
  else
  if (str[i]=='.' || str[i]==0 )
  {
   char tmp[4] ;
   if (NombreDigits==0 || NombreDigits > 3 )
      return -1 ;
   if (NumeroMembre>3)
      return -1 ;
   str[i] = 0 ;
   strcpy(tmp,&str[s]) ;
   Membre[NumeroMembre] = atoi(tmp) ;
   s = i+1 ;
   NumeroMembre++ ;
   NombreDigits = 0 ;
  }
  else /* Pas un chiffre ni un point, ni un z�o */
     return -1 ;
  i++ ;
 }

 return 1 ;
}
