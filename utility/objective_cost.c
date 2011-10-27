
/* fonction de listage des agents */
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "../header/type.h"
/* ============================ */
t_cost
objective_cost(t_gap_solution * gap_sol, t_gap_instance *gap_inst)
{
t_list list_agents ;
t_agent agt ;
t_job job ;
t_cost gain=0 ;
for (agt=0; agt < gap_inst->agent_count ; agt++)
  {
  for (job=0; job < gap_inst->job_count ; job++)
  gain+=gap_sol->assignment[agt][job]*gap_inst->gain[agt][job] ;
  } ;
return gain ;
}
