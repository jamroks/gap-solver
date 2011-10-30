
/* fonction de listage des taches pour un agent avec plafond */
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
job_agt_list(t_gap_instance *inst, t_gap_solution *gap, t_agent agt_1, t_agent agt_2)
{
t_job job ;
t_list job_list ;
//printf("\njob_agt_list %d -> %d\n",agt_1,agt_2) ;
job_list.nb_elt=0 ;
for (job=0; job < gap->job_count; job++)
  {
  if (gap->assignment[agt_1][job] == 1)
    {
    // il faut de la place ...
    if (inst->cost[agt_2][job] <= gap->capacity_left[agt_2])
       {
       // ajout de la tâche dans la liste
       job_list.list[job_list.nb_elt++]=job ;
       } ;
    } ;
  } ;
//for (job=0 ; job < job_list.nb_elt ; job++)
//   printf("[%d]->%d\n",job,job_list.list[job]) ;
//printf("\n") ;
return (t_list) job_list ;
}
