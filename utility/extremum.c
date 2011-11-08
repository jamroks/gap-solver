
/* fonction de calcul des extrema */
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "../header/type.h"
/* ============================ */
void
extremum(t_gap_solution *gap_sol , t_gap_instance *gap_inst, t_gap_solver_registry *reg )
{
  t_list list_agents ;
  t_agent agt ;
  t_job job ;
  t_cost gain=0 ;
  t_cost minimum[MAX_JOB] ;
  t_cost maximum[MAX_JOB] ;
  t_job agent[MAX_JOB] ;
  if (reg->verbose == TRUE) printf("\n >>>>>>> extremum  <<<<<<<<<<<<\n") ;
  for (job=0; job < gap_inst->job_count ; job++)
    {
      minimum[job]= 99999 ;
      maximum[job]= -1 ;
      agent[job]= 0 ;
      for (agt=0; agt < gap_inst->agent_count ; agt++)
        {
          gap_sol->assignment[agt][job] = 0 ;
          if (reg->problem_type == MAXIMIZATION)
            {
              if  (gap_inst->gain[agt][job] > maximum[job])
                {
                  maximum[job] = gap_inst->gain[agt][job] ;
                  agent[job] = agt ;
                } ;
            }
          else
            {
              if (gap_inst->gain[agt][job] < minimum[job])
                {
                  minimum[job] = gap_inst->gain[agt][job] ;
                  agent[job] = agt ;
                } ;
            } ;
        } ;
    } ;
  if (reg->verbose == TRUE)
    {
       printf("\n============================================\n") ;
    if (reg->problem_type == MINIMIZATION)
      {
        printf("\nminimum :") ;
        for (job=0; job < gap_inst->job_count ; job++)
        printf(" ; %d ", minimum[job]) ;
      }
    else
      {
        printf("\nmaximum :") ;
        for (job=0; job < gap_inst->job_count ; job++)
          printf(" ; %d ", maximum[job]) ;
      } ;
    printf("\n\naffectation :") ;
  } ;
  for (job=0; job < gap_inst->job_count ; job++)
    {
      if (reg->verbose == TRUE) printf(" ; %d->%d ", job, agent[job]) ;
      gap_sol->assignment[agent[job]][job] = 1 ;
    } ;
  if (reg->verbose == TRUE)  printf("\n============================================\n") ;


}
