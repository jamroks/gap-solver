/* fonction de calcul de la solution suivante dans un voisinage de la solution précédente */
/*
 * attention je construis la fonction au fur et à mesure en ajoutant des paramètres ..
 * 
*/
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "../header/type.h"
/* ============================ */
#include "../header/function.h"
/* ============================ */
short 
stochastic_next_solution (t_gap_solution *gap_next , t_gap_instance *gap_inst , t_gap_solution *gap_cur , 
                          t_gap_solver_registry *registry) 
{
t_list values_list ;
int agt_1 , agt_2 , job , job2 ;
int ind ;
int try_count=0 ;
t_bool new_found=FALSE ;
t_method method=registry->method ;
if (registry->verbosity == TRUE) printf("=> début de calcul de voisinage %d ...\n" , registry->transfert_count) ;
/* copie de la solution de départ vers la solution suivante , avant modification */
if (registry->verbosity == TRUE) printf("=> clonage\n") ;
  clone_gap_solution (gap_next , gap_cur) ;
  // memcpy(gap_next , gap_cur , sizeof(t_gap_solution)) ;
/* Sélection de la structure de voisinage */ 
if (registry->verbosity == TRUE) printf("=> bouclage\n") ;
while ((new_found == FALSE) && (try_count < registry->max_try_count))
{
try_count++ ;
switch (method) 
  {
  case TRANSFERT :/* selon un transfert d'une tâche entre deux agents */
      {
      if (registry->verbosity == TRUE) printf("\tméthode par transfert ...\n") ;
      /* constituer la liste pondérée des agents */
      values_list=agent_list(gap_inst) ;
      /* tirer au sort un élément dans la liste */
      if (values_list.nb_elt == 0)
        { 
        /* pas de tâche possible : saturation de agt_2 */
        if (registry->verbosity == TRUE) printf("aucun agent 1\n") ;
        unavailable(NO_AGT) ;
        registry->unavailable_count++ ;
        method=SWAP ;
        break ;
        } ;      
      if (registry->verbosity == TRUE) printf("\t\ttirage au sort un agent\n") ;
      agt_1 = take_choice(gap_inst , gap_cur , registry , &values_list , registry->agtponderate) ;
      if (registry->verbosity == TRUE) printf("\tagent origine ... %d\t" , agt_1) ;
      /* enlever agt_1 de la liste */
      if (registry->verbosity == TRUE) printf("\tretrait de l'agent ...\n") ;
      subtract_elt_from_list(&values_list , agt_1) ;
      if (values_list.nb_elt == 0)
        { 
        // pas d'agent disponible ?
        if (registry->verbosity == TRUE) printf("aucun agent 2\n") ;
        unavailable(NO_AGT) ;
        registry->unavailable_count++ ;
        break ;
        } ;      
      /* tirer au sort un autre agent dans la liste */
      agt_2 = take_choice(gap_inst , gap_cur , registry , &values_list , registry->agtponderate) ;
      if (registry->verbosity == TRUE) printf("\tagent cible ... %d\t" , agt_2) ;
      /* idem pour choisir une tâche admissible de agt_1 vers agt_2 */
      values_list=job_agt_list(gap_inst , gap_cur , agt_1 , agt_2) ;
      if (values_list.nb_elt == 0)
        { 
        // pas de tâche possible : saturation de agt_2 
        if (registry->verbosity == TRUE) printf("\n mal barré\n") ;
        unavailable(NO_JOB) ;
        /* CAS A VOIR : VOISINAGE VIDE ! */
        registry->unavailable_count++ ;
        method=SWAP ;
        break ;
        }
      else
        {
        /* tirer au sort un élément dans la liste ou montée */
        if (registry->verbosity == TRUE) printf("\n\ttirage au sort d'une tâche parmi %d...\n",values_list.nb_elt) ;
        if (MONTEE) 
           {
           /* choisir la tâche qui rapporte le plus  */
//for (ind=0 ; ind < values_list.nb_elt ; ind++)
//  printf("[%d]->%d\n",ind,values_list.list[ind]) ;
           job = increasing(gap_inst , gap_cur , registry , agt_1 , agt_2 , &values_list) ;
           }
        else
           {
           job = take_choice(gap_inst , gap_cur , registry , &values_list , registry->jobponderate) ;
           } ;
        if (registry->verbosity == TRUE) printf("\t tache n°%d.\n" , job) ;
        /* transférer la tâche de agt_1 vers agt_2 */
        if (registry->verbosity == TRUE) printf("\nTRANS:: agt=%d(%d)  pour job=%d(%d) // agt =%d(%d) cout=%d\n",
             agt_1,gap_next->capacity_left[agt_1], job, gap_inst->cost[agt_1][job], 
             agt_2,gap_next->capacity_left[agt_2], gap_inst->cost[agt_2][job]) ; 
        gap_next->assignment[agt_1][job]=0 ;
        gap_next->assignment[agt_2][job]=1 ;
        gap_next->capacity_left[agt_1]+=gap_inst->cost[agt_1][job] ;
        gap_next->capacity_left[agt_2]-=gap_inst->cost[agt_2][job] ;
        if (gap_next->capacity_left[agt_1] < 0) 
          {
          printf("negatif 01\n") ;
          } ;
        if (gap_next->capacity_left[agt_2] < 0) 
          {
          printf("negatif 02\n") ;
          } ;
        new_found=TRUE ;
        registry->transfert_count++ ;
        } ;      
      if (registry->verbosity == TRUE) printf("\tfin de méthode par transfert ...\n") ;
      } ;
      break ;
  case SWAP :  /* selon un transfert d'une tâche entre deux agents */
      {
      if (registry->verbosity == TRUE) printf("\tméthode par SWAP ...\n") ;
      /* constituer la liste pondérée des agents */
      values_list=agent_list(gap_inst) ;
      /* tirer au sort un élément dans la liste */
      if (values_list.nb_elt == 0)
        { 
        /* pas de tâche possible : saturation de agt_2 */
        if (registry->verbosity == TRUE) printf("aucun agent 1\n") ;
        unavailable(NO_AGT) ;
        registry->unavailable_count++ ;
        method=SWAP ;
        break ;
        } ;      
      agt_1 = take_choice(gap_inst , gap_cur , registry , &values_list , registry->agtponderate) ;
      if (registry->verbosity == TRUE) printf("\tagent origine ... %d\t" , agt_1) ;
      /* enlever agt_1 de la liste */
      if (registry->verbosity == TRUE) printf("\tretrait de l'agent ...\n") ;
      subtract_elt_from_list(&values_list , agt_1) ;
      if (values_list.nb_elt == 0)
        { 
        // pas d'agent disponible ?
      if (registry->verbosity == TRUE) printf("aucun agent 2\n") ;
        unavailable(NO_AGT) ;
        registry->unavailable_count++ ;
        break ;
        } ;      
      /* tirer au sort un autre agent dans la liste */
      agt_2 = take_choice(gap_inst , gap_cur , registry , &values_list , registry->agtponderate) ;
      if (registry->verbosity == TRUE) printf("\tagent cible ... %d\t" , agt_2) ;
      /* idem pour choisir une tâche chez agent 1 */
      if (agt_1 == agt_2) printf("bug negatif agent swap\n") ;
      values_list=job_swap0_list(gap_inst , gap_cur , agt_1 , agt_2) ; //agt2 ne sert à rien
      if (values_list.nb_elt == 0)
        { 
        // pas de tache ?
        if (registry->verbosity == TRUE) printf("\n mal barré20\n") ;
        unavailable(NO_JOB) ;
        /* CAS A VOIR : VOISINAGE VIDE ! */
        registry->unavailable_count++ ;
        method=SWAP ;
        break ;
        };
      /* tirer au sort une tache à échanger */
      job = take_choice(gap_inst , gap_cur , registry , &values_list , registry->jobponderate) ;
      if (registry->verbosity == TRUE) printf("\t tache n°%d.\n" , job) ;
      /* idem pour choisir une tâche admissible chez agent 2 */
      values_list=job_swap_list(gap_inst , gap_cur , agt_1 , agt_2 , job) ;
      if (values_list.nb_elt == 0)
        { 
        // pas de tâche possible : agent sans tache
        if (registry->verbosity == TRUE) printf("\n mal barré21\n") ;
        unavailable(NO_JOB) ;
        /* CAS A VOIR : VOISINAGE VIDE ! */
        registry->unavailable_count++ ;
        method=SWAP ;
        break ;
        };
      /* tirer au sort une seconde tache à échanger */
      if (registry->verbosity == TRUE) printf("\ttirage au sort d'une tâche ...\n") ;
      job2 = take_choice(gap_inst , gap_cur , registry , &values_list , registry->jobponderate) ;
      if (registry->verbosity == TRUE) printf("\t tache n°%d.\n" , job) ;
      /* faire l'échange la tâche de agt_1 et agt_2 */
      if (registry->verbosity == TRUE) printf("\nSWAP:: agt=%d(%d)  pour job=%d(%d) // agt =%d(%d) pour job=%d(%d)\n",
          agt_1,gap_next->capacity_left[agt_1], job, gap_inst->cost[agt_1][job], 
          agt_2,gap_next->capacity_left[agt_2], job2, gap_inst->cost[agt_2][job2]) ; 
      gap_next->assignment[agt_1][job]=0 ;
      gap_next->assignment[agt_1][job2]=1 ;
      gap_next->assignment[agt_2][job2]=0 ;
      gap_next->assignment[agt_2][job]=1 ;
      gap_next->capacity_left[agt_1]+=gap_inst->cost[agt_1][job] ;
      gap_next->capacity_left[agt_2]-=gap_inst->cost[agt_2][job] ;
      gap_next->capacity_left[agt_1]-=gap_inst->cost[agt_1][job2] ;
      gap_next->capacity_left[agt_2]+=gap_inst->cost[agt_2][job2] ;
      if (gap_next->capacity_left[agt_1] < 0) 
        {
        printf("negatif 1\n") ;
        printf("\nSWAP:: agt=%d(%d)  pour job=%d(%d) // agt =%d(%d) pour job=%d(%d)\n",
               agt_1,gap_next->capacity_left[agt_1], job, gap_inst->cost[agt_1][job], 
               agt_2,gap_next->capacity_left[agt_2], job2, gap_inst->cost[agt_2][job2]) ; 
        } ;
      if (gap_next->capacity_left[agt_2] < 0) 
        {
        printf("negatif 2\n") ;
        printf("\nSWAP:: agt=%d(%d)  pour job=%d(%d) // agt =%d(%d) pour job=%d(%d)\n",
             agt_1,gap_next->capacity_left[agt_1], job, gap_inst->cost[agt_1][job], 
             agt_2,gap_next->capacity_left[agt_2], job2, gap_inst->cost[agt_2][job2]) ; 
        } ;
      new_found=TRUE ;
      registry->swap_count++ ;
      if (registry->verbosity == TRUE) printf("\tfin de méthode par transfert ...\n") ;
      } ;
      break ;
  case ROTATION :  /* selon un transfert d'une tâche entre plusieurs agents */
      {
      } ;
      break ;
  default :  /* cas d'un bug */
    {
    printf("bug n°1") ;
    exit(0) ;
    } ;
    break ;
  } ;
} ; // fin de boucle sur récidive en cas de blocage
if (try_count == registry->max_try_count)
	registry->max_try_count_failure++ ;
return 0 ;
if (registry->verbosity == TRUE) printf("fin voisinage.\n") ;
}
