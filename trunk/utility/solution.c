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
_job_add (t_agent agent, t_job job) ;

static void
_job_remove (t_agent agent, t_job job) ;

void
solution_apply_change (
  t_gap_instance * instance,
  t_gap_solution * solution,
  t_solution_change * change
)
{
  _solution = solution ;
  _instance = instance ;
  solution->value += change->delta_value ;
  switch (change->type)
    {
      case SOLUTION_CHANGE_TRANSFER:
        _job_remove (          
          change->contents.transfer.source,
          change->contents.transfer.job
        ) ;
        _job_add (
          change->contents.transfer.destination,
          change->contents.transfer.job
       ) ;
        break ;
      case SOLUTION_CHANGE_SWAP:
        _job_remove (          
          change->contents.swap.source,
          change->contents.swap.source_swapped_job
        ) ;
        _job_add (
          change->contents.swap.source,
          change->contents.swap.destination_swapped_job
       ) ;
        _job_remove (          
          change->contents.swap.destination,
          change->contents.swap.destination_swapped_job
        ) ;
        _job_add (
          change->contents.swap.destination,
          change->contents.swap.source_swapped_job
       ) ;
        break ;
    }
}

static void
_job_add (t_agent agent, t_job job)
{
  _solution->assignment[agent][job] = 1 ;
  _solution->capacity_left[agent] -= _instance->cost[agent][job] ;
  add_job_to_job_list (_solution->ll_assignment[agent], job) ;
}

static void
_job_remove (t_agent agent, t_job job)
{
  _solution->assignment[agent][job] = 0 ;
  _solution->capacity_left[agent] += _instance->cost[agent][job] ;
  remove_job_from_job_list (_solution->ll_assignment[agent], job) ;
}
