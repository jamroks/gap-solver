/* fonction de ponderation : capacite résiduelle (agents) */
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
capacity_left(t_gap_instance *inst, t_gap_solution *sol, t_gap_solver_registry *reg, t_elt elt)
{
if (reg->verbosity == TRUE) printf(" (via capacity_left !) ") ;
return(sol->capacity_left[elt]+MIN_VALUE) ;
}
