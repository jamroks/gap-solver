
/* fonction déterminant la meilleur tâche à transférer entre 2 agents */
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "../header/type.h"
/* ============================ */
/* 
 * INCOMPLET
*/
t_job
increasing(t_gap_instance *inst, t_gap_solution *sol, t_gap_solver_registry *reg, t_agent agt_1 , t_agent agt_2 , t_list *list_of_values) 
{
int job=NO_VALUE ;
int n_elt ;
t_job best_job=NO_VALUE ;
t_gain value ;
t_gain best_value=0 ;

//printf("Montée sur %d élts  de %d à %d \n",list_of_values->nb_elt,agt_1,agt_2) ;
for (n_elt=0; n_elt < list_of_values->nb_elt; n_elt++)
  {
  job=list_of_values->list[n_elt] ;
//printf("\njob n° %d\t",job); 
  value = inst->gain[agt_2][job] - inst->gain[agt_1][job] ;
//printf("value %d - %d = %d\t",inst->gain[agt_2][job] ,inst->gain[agt_1][job] , value);
  if (reg->problem_type == MAXIMIZATION)
    {
//printf("en maxi ") ;
    if ((best_job == NO_VALUE) || (value >= best_value))
      {
      best_job = job ;
      best_value = value ;
//printf("affectation MAXI\n") ;
      } ;
    }
  else
    {
    if (reg->problem_type == MINIMIZATION)
      {
//printf("en mini %d  ",job) ;
      if ((best_job == NO_VALUE) || (value <= best_value))
        {
        best_job = job ;
        best_value = value ;
//printf("affectation MINI\n") ;
        } ;
      } ;
    } ;
  } ;

//best_job=list_of_values->list[0] ;
if (reg->verbosity == TRUE) printf("\nmontée/descente sur %d élts :: %d - %d meilleur=%d job=%d\n",
        list_of_values->nb_elt, inst->gain[agt_2][best_job],inst->gain[agt_1][best_job], best_value, best_job) ;
if (best_job == NO_VALUE) printf("NO_VALUE !\n") ;	
//printf("fin de Montée ->%d\n",best_job) ;
return (t_job) best_job ;
}
