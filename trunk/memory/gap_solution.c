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
alloc_gap_solution (t_gap_solution * solution, int agent_count, int job_count)
{
  int i, j;
  solution->agent_count = agent_count ;
  solution->job_count = job_count ;
  solution->capacity_left = (t_cost *) calloc (sizeof (t_cost *), agent_count) ;
  if ( ! solution->capacity_left)
    return 0 ;
  solution->assignment = (t_bool **) calloc (sizeof (t_bool *), agent_count) ;
  if ( ! solution->assignment)
    return 0 ;
  for (i = 0 ; i < agent_count ; i ++)
    {
      solution->assignment[i] = (t_bool *) calloc (sizeof (t_cost), job_count) ;
      if ( ! solution->assignment[i])
        return 0;
      for (j = 0; j < job_count; j++)
        solution->assignment[i][j] = 0;
    }
}

short
free_gap_solution (t_gap_solution * solution)
{
  int i ;
  free (solution->capacity_left) ;
  for (i = 0; i < solution->agent_count; i ++)
    free (solution->assignment[i]) ;
  free (solution->assignment) ;
  return 1 ;
}

short
clone_gap_solution (
  t_gap_solution * destination,
  t_gap_solution * source
)
{
  int agent, job;
  if ( ! alloc_gap_solution (destination, source->agent_count, source->job_count))
    return 0 ;
  destination->value = source->value;
  for (agent = 0 ; agent < source->agent_count ; agent ++)
    {
      destination->capacity_left[agent] = source->capacity_left[agent];
      for (job = 0 ; job < source->job_count ; job ++)
        {
          destination->assignment[agent][job] = source->assignment[agent][job];
        }
    }
}
