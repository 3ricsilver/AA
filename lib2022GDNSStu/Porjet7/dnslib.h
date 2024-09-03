#ifndef H_LISTESIMPLE
#define H_LISTESIMPLE
#include <stddef.h> /* pour size_t */
typedef struct sll sll_s;

void sll_save(struct sll *p_l ) ;
void sll_restore(struct sll *p_l ) ; 

sll_s *sll_new (void);
void sll_insert (sll_s *, void *);
void sll_removeNext (sll_s *);
void sll_removeFirst (sll_s *);
void sll_next (sll_s *);
void *sll_data (sll_s *);
void sll_first (sll_s *);
void sll_last (sll_s *);
size_t sll_sizeof (sll_s *);
void sll_delete (sll_s **);

char* SuffixeDe(char *Suffixe, char* Chaine) ;
char* SepareHoteDomaine(char *FQDN, char** Domaine) ;
void EnleveGL( char *Chaine) ;
void Enleve1013(char *Chaine) ;
int 	Ipv4ToArray(char *strsource,int Membre[4]) ;



enum TypeEntree { DBDomain=1, DBAddress=2 ,Hint = 3 } ; 

struct EntreeNamedConf
{
  char nom[80] ;
  int I1,I2,I3,I4 ;
  char Fichier[80] ;
  char HV[80] ;
  enum TypeEntree Type ;
};

enum TypeIN { NS=1, A=2 , PTR=3, HV=4 } ;

struct EntreeZone
{
  char Nom[80] ;
  char Valeur[80] ;
  enum TypeIN Type ;
};

#endif /* not H_LISTESIMPLE */
