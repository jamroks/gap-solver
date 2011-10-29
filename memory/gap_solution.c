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

/**
 * Allocates memory for the nested objects.
 *
 * @param agent_count	Instance agent count
 * @param job_count	Instance job count
 */
short
alloc_gap_solution (t_gap_solution * solution, int agent_count, int job_count)
{
  int agent, job ;
  solution->value = 0 ;
  solution->agent_count = agent_count ;
  solution->job_count = job_count ;
  solution->capacity_left = (t_cost *) calloc (sizeof (t_cost *), agent_count) ;
  if (NULL == solution->capacity_left)
    return 0 ;
  solution->assignment = (t_bool **) calloc (sizeof (t_bool *), agent_count) ;
  if (NULL == solution->assignment)
    return 0 ;
  solution->ll_assignment =
    (t_job_list **) calloc (sizeof (t_job_list *), job_count) ;
  if (NULL == solution->ll_assignment)
    return 0 ;
  for (agent = 0 ; agent < agent_count ; agent ++)
    {
      solution->assignment[agent] =
        (t_bool *) calloc (sizeof (t_cost), job_count) ;
      if (NULL == solution->assignment[agent])
        return 0 ;
      solution->ll_assignment[agent] = alloc_job_list_head () ;
      if (NULL == solution->ll_assignment[agent])
        return 0 ;
      for (job = 0; job < job_count; job ++)
        solution->assignment[agent][job] = 0 ;
    }
}

/**
 * Free memory allocated to the nested objects.
 */
short
free_gap_solution (t_gap_solution * solution)
{
  int agent ;
  free (solution->capacity_left) ;
  for (agent = 0 ; agent < solution->agent_count; agent ++)
  {
      free (solution->assignment[agent]) ;
      free_job_list (solution->ll_assignment[agent]) ;
      free (solution->ll_assignment) ;
  }
  free (solution->assignment) ;
  return 1 ;
}

/**
 * Recursively copy the given source.
 * Memory for nested objects will be allocated.
 *
 * @param destination	
 * @param source
 */
short
clone_gap_solution (t_gap_solution * destination, t_gap_solution * source)
{
  int agent, job;
  if ( ! alloc_gap_solution (
    destination,
    source->agent_count,
    source->job_count)
  )
    return 0 ;
  destination->value = source->value;
  for (agent = 0 ; agent < source->agent_count ; agent ++)
    {
      clone_job_list (
        destination->ll_assignment[agent],
        source->ll_assignment[agent]
      ) ;
      destination->capacity_left[agent] =
        source->capacity_left[agent] ;
      for (job = 0 ; job < source->job_count ; job ++)
        destination->assignment[agent][job] =
          source->assignment[agent][job] ;
    }
}
