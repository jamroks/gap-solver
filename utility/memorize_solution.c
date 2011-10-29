
/* fonction de memorisation d'une solution */
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "../header/common.h"
/* ============================ */
/* INCOMPLET
*/
#define max(a,b) (a<=b?b:a)
void 
memorize_solution(t_gap_instance *inst, t_gap_solution *sol, t_gap_solver_registry *reg )
{
if (reg->verbosity == TRUE) printf("\t\tmemorize_solution ...\n") ;
}
