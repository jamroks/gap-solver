
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

void 
memorize_solution(t_gap_instance *inst, t_gap_solution *sol, t_gap_solver_registry *reg )
{
char fichier[80] ;
t_job job ;
t_agent agt ;
FILE *fic ;
if (reg->verbosity == TRUE) printf("\t\tmemorize_solution ...\n") ;
//fichier="resultats.txt" ;
fic=fopen("resultats.txt", "a"); 
if (fic==NULL)
  { 
  unavailable(3) ;
  } 
  else
  {
  fprintf(fic, "%s ; %d ; %d ; %d ; ",inst->name, inst->agent_count, inst->job_count, sol->value) ;
  for (agt = 0 ; agt < inst->agent_count ; agt++)
    {
    fprintf(fic," %d ;",sol->capacity_left[agt]) ;
    } ;
  fprintf(fic,"%d ;", reg->unavailable_count) ;
  fprintf(fic,"%d ;", reg->max_try_count_failure) ;
  fprintf(fic,"%d ;", reg->transfert_count) ;
  fprintf(fic,"%d ;", reg->swap_count) ;
  fprintf(fic, "\n") ;
  fclose(fic) ;
  } ;
}
