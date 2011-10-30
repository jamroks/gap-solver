
/* fonction de listage des taches pour un échange de job1 (venant de agt1) */
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
t_list 
job_swap_list(t_gap_instance *inst, t_gap_solution *gap, t_agent agt_1, t_agent agt_2 , t_job job_1)
{
t_job job ;
t_list job_list ;
job_list.nb_elt=0 ;
//printf("\t extraction de taches de l'agent %d pour l'agent %d\n", agt_1, agt_2) ;
for (job=0; job < gap->job_count; job++)
  {
  if (gap->assignment[agt_2][job] == 1)
    {
    // il faut de la place ...
    if ((inst->cost[agt_1][job] <= (gap->capacity_left[agt_1]+inst->cost[agt_1][job_1])) 
        && (inst->cost[agt_2][job_1] <= (gap->capacity_left[agt_2]+inst->cost[agt_2][job]))) 
       {
       // ajout de la tâche dans la liste
//       printf("ajout de %d pour un cout de %d\n",job,inst->cost[agt_2][job]) ;
       job_list.list[job_list.nb_elt++]=job ;
       } ;
    } ;
  } ;
return (t_list) job_list ;
}
