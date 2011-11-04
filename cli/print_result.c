/*
This file is part of gap_solver.

gap_solver is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

gap_solver is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with gap_solver. If not, see <http://www.gnu.org/licenses/>.
*/

#include "../header/common.h"

short 
print_result (t_gap_instance * instance, t_gap_solution * solution)
{
  int valeur ;
  int agent,job ;
  int nb_line=0 ;
  int assignments ;
  t_job_list * ll_job_elt ;
  printf (
    "%-5d\n\n%-5d\n\n%-5d\n\n",
    solution->value,
    instance->agent_count,
    instance->job_count
  );
  for (agent = 0 ; agent < instance->agent_count ; agent ++)
    {
      printf("%d\t", agent + 1) ;
      assignments = 0 ;
      ll_job_elt = solution->ll_assignment[agent] ;
      while (ll_job_elt = ll_job_elt->next)
        assignments ++ ;
      printf ("%5d / %-5d\t%5d / %-5d\n\n",
        assignments,
        instance->job_count,
        solution->capacity_left[agent],
        instance->capacity[agent]
      );
      ll_job_elt = solution->ll_assignment[agent] ;
      while (ll_job_elt = ll_job_elt->next)
        printf (
          "%5d : %-5d\t",
          ll_job_elt->job,
          instance->cost[agent][ll_job_elt->job]
        ) ;
      printf ("%s", "\n\n");

    };
  return 0 ;
}
