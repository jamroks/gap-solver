/* fonction de ponderation : capacite globale (agents) */
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
capacity(t_gap_instance *inst, t_gap_solution *sol, t_gap_solver_registry *reg, t_elt elt)
{
printf(" (via capacity pour %d !) \n",elt) ;
return(inst->capacity[elt]) ;
}
