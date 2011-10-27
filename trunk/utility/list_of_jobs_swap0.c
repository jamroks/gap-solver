
/* fonction de listage des taches pour un agent SANS plafond */
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
list_of_jobs_swap0(t_gap_instance *inst, t_gap_solution *gap, t_agent agt_1, t_agent agt_2)
{
t_job job ;
t_list list_of_jobs ;
list_of_jobs.nb_elt=0 ;
//printf("\t extraction de taches de l'agent %d pour l'agent %d\n", agt_1, agt_2) ;
for (job=0; job < gap->job_count; job++)
  {
  if (gap->assignment[agt_1][job] == 1)
    {
    // il faut de la place ...
       // ajout de la tâche dans la liste
//       printf("ajout de %d pour un cout de %d\n",job,inst->cost[agt_2][job]) ;
       list_of_jobs.list[list_of_jobs.nb_elt++]=job ;
    } ;
  } ;
return (t_list) list_of_jobs ;
}
