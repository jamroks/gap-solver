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
alloc_gap_instance (t_gap_instance * instance, int agent_count, int job_count)
{
  int i;
  instance->agent_count = agent_count ;
  instance->job_count = job_count ;
  instance->capacity = (t_cost *) calloc (sizeof (t_cost), agent_count) ;
  if ( ! instance->capacity)
    return 0 ;
  instance->cost = (t_cost **) calloc (sizeof (t_cost *), agent_count) ;
  if ( ! instance->cost)
    return 0 ;
  instance->gain = (t_gain **) calloc (sizeof (t_gain *), agent_count) ;
  if ( ! instance->gain)
    return 0 ;
  for (i = 0 ; i < agent_count; i ++)
    {
      instance->cost[i] = (t_cost *) calloc (sizeof (t_cost), job_count) ;
      if ( ! instance->cost[i])
        return 0;
      instance->gain[i] = (t_gain *) calloc (sizeof (t_gain), job_count) ;
      if ( ! instance->gain[i])
        return 0;
    }
  return 1;
}

/**
 * Free memory allocated to the nested objects.
 */
short
free_gap_instance (t_gap_instance * instance)
{
  int i;
  free (instance->capacity) ;
  for (i = 0 ; i < instance->agent_count ; i ++)
    {
      free (instance->cost[i]) ;
      free (instance->gain[i]) ;
    }
  free (instance->cost) ;
  free (instance->gain) ;
  return;
}
