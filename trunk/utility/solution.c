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

static t_gap_instance * _instance ;
static t_gap_solution * _solution ;

static void
_job_add (t_job job, t_agent agent) ;

static void
_job_remove (t_job job, t_agent agent) ;

/**
 * Apply the given change to the solution. 
 *
 * @param	instance
 *
 * @param	solution
 *
 * @param	change
 */
void
solution_apply_change (
  t_gap_instance * instance,
  t_gap_solution * solution,
  t_solution_change * change
)
{
  t_job_list * elt ;
  _solution = solution ;
  _instance = instance ;
  solution->value += change->delta_value ;
  switch (change->type)
    {
      case SOLUTION_CHANGE_TRANSFER:
        _job_remove (
          change->contents.transfer.job,      
          change->contents.transfer.source
        ) ;
        _job_add (
          change->contents.transfer.job,
          change->contents.transfer.destination
        ) ;
        break ;
      case SOLUTION_CHANGE_SWAP:
        _job_remove (
          change->contents.swap.source_swapped_job,
          change->contents.swap.source
        ) ;
        _job_add (
          change->contents.swap.destination_swapped_job,
          change->contents.swap.source
        ) ;
        _job_remove (
          change->contents.swap.destination_swapped_job,
          change->contents.swap.destination
        ) ;
        _job_add (
          change->contents.swap.source_swapped_job,
          change->contents.swap.destination
        ) ;
        break ;
      case SOLUTION_CHANGE_MULTI_SWAP:
        elt = change->contents.multi_swap.destination_swapped_job ;
        while (elt = elt->next)
          {

// printf ("%d ", elt->job) ;

            _job_add (
              elt->job,
              change->contents.swap.source
            ) ;
            _job_remove (
              elt->job,
              change->contents.swap.destination
            ) ;

          }

// printf ("\n") ;

        _job_remove (
          change->contents.multi_swap.source_swapped_job,
          change->contents.multi_swap.source
        ) ;
        _job_add (
          change->contents.multi_swap.source_swapped_job,
          change->contents.swap.destination
        ) ;
        break ;
    }
}

static void
_job_remove (t_job job, t_agent agent)
{
  _solution->assignment[agent][job] = 0 ;
  _solution->capacity_left[agent] += _instance->cost[agent][job] ;
  job_list_delete_job (_solution->ll_assignment[agent], job) ;
}

static void
_job_add (t_job job, t_agent agent)
{
  _solution->assignment[agent][job] = 1 ;
  _solution->capacity_left[agent] -= _instance->cost[agent][job] ;
  job_list_add_job (_solution->ll_assignment[agent], job) ;
}
