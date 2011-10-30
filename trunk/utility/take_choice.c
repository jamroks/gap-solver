
/* fonction de tirage au sort d'un élément dans la liste */
/* renvoit le rang le n° de l'élément tiré au sort : entre 1 et nb_elt */
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "../header/common.h"
/* ============================ */
/* INCOMPLET
*/
#define max(a,b) (a<=b?b:a)
t_elt 
take_choice(t_gap_instance *inst, t_gap_solution *sol, t_gap_solver_registry *reg,
            t_list *list_of_elt,int (*ponderate)())
{
int n_elt , sum=0 ;
int rnd_value ;
t_elt elt ;
t_list ponderate_list ;
if (list_of_elt->nb_elt <=0) printf("take choice : ZERO\n") ;
if (reg->verbosity == TRUE) printf("\t\ttake_choice ...%d élts\n",list_of_elt->nb_elt) ;
// calculer la ponderation pour chaque élément de la liste
for (n_elt=0; n_elt < list_of_elt->nb_elt; n_elt++)
  {
  if (reg->verbosity == TRUE) printf("\t\t[%d]",n_elt) ;
  elt = list_of_elt->list[n_elt] ;
  sum+=ponderate(inst , sol , reg , elt) ;
  ponderate_list.list[n_elt]=sum ;  
  if (reg->verbosity == TRUE) printf(" objet n°%d  pondération cumulée=%d\n",elt,ponderate_list.list[n_elt]) ;
  } ;
ponderate_list.nb_elt=list_of_elt->nb_elt ;
// une valeur aléatoire 
// ici pondérée : valeurs cumulées
if (reg->verbosity == TRUE) printf("\t\taléatoire") ;
n_elt=list_of_elt->nb_elt ;
if (reg->verbosity == TRUE) printf("\t avec %d élts\n",n_elt) ;
  if (ponderate_list.list[n_elt-1] == 0) 
  { 
  rnd_value = rand() % n_elt ;
  if (reg->verbosity == TRUE) printf("\t\tlinéaire ...%d",rnd_value) ;
  n_elt=rnd_value ;
  }
  else
  {
  rnd_value = (rand() % ponderate_list.list[n_elt-1]) + 1 ;
  if (reg->verbosity == TRUE) printf("\t\tpondérée ...%d sur %d",rnd_value,ponderate_list.list[n_elt-1]) ;
  n_elt=0;
  while (rnd_value > ponderate_list.list[n_elt])
    { n_elt++ ; } ;
  } ;
if (reg->verbosity == TRUE) printf("\t\tvaleur aléatoire position=%d \n",n_elt) ;
return (t_elt) list_of_elt->list[n_elt] ;
}
