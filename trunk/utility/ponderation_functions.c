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
/* fonction de ponderation : egalité */
int 
_uniform(t_gap_instance *inst, t_gap_solution *sol, t_gap_solver_registry *reg, t_elt elt)
{
//printf(" (via uniform !) ") ;
return(0) ;
}

/* fonction de ponderation : capacite globale (agents) */
t_cost 
_capacity(t_gap_instance *inst, t_gap_solution *sol, t_gap_solver_registry *reg, t_elt elt)
{
printf(" (via capacity pour %d !) \n",elt) ;
return(inst->capacity[elt]) ;
}

/* fonction de ponderation : capacite résiduelle (agents) */
t_cost 
_capacity_left(t_gap_instance *inst, t_gap_solution *sol, t_gap_solver_registry *reg, t_elt elt)
{
if (reg->verbosity == TRUE) printf(" (via capacity_left !) ") ;
return(sol->capacity_left[elt]+MIN_VALUE) ;
}

