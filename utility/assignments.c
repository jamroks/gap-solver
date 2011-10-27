/* fonction de ponderation : nombre de tâches assignées (agent) */
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "../header/type.h"
/* ============================ */
int 
assignments(t_gap_instance inst, t_gap_solution sol, equity_gap_solver_registry reg, t_elt elt)
{
int assignments=0 ;
t_job job ;
  for (job = 0 ; job < instance->job_count ; job++)
    {
    if (solution->assignment[elt][job] == 1)
      assignments ++ ;
    }
return(assignments) ;
}
