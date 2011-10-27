
/* fonction pour enlever un élément d'une liste */
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "../header/type.h"
/* ============================ */
void 
subtract_elt_from_list(t_list *list_of_values,t_elt agt_1) 
{
int n_elt=0 ;
while (list_of_values->list[n_elt] != agt_1)
  {
  n_elt++ ;
  } ;
// décalage des suivants 
while (n_elt < list_of_values->nb_elt)
  {
  list_of_values->list[n_elt] = list_of_values->list[n_elt+1] ;
  n_elt++ ;
  } ;
list_of_values->nb_elt-- ;
/*
 * for (n_elt=0;n_elt <5; n_elt++) 
 *   { printf("[%d]=%d  ",n_elt,list_of_values->list[n_elt]) ;
 *   } ;
 * printf("\n") ;
*/
}
