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

static int _source_agent = 0 ;
static t_gap_solution * _next_solution ;
static t_gap_instance * _instance ;
static t_gap_solver_registry * _registry ;

static void
_transfer_job (t_job job, t_agent source, t_agent destination) ;

static void
_remove_job (t_job job, t_agent agent) ;

static void
_add_job (t_job job, t_agent agent) ;

static void
_swap_jobs (t_job job1, t_agent agent1, t_agent agent2, t_job job2) ;

static void
_update_source_agent () ;

short
determinist_next_solution (
  t_gap_solution * next,
  t_gap_instance * instance,
  t_gap_solution * current,
  t_gap_solver_registry * registry
)
{
  t_job_list * job, *job1 ;
  int i, j, source, destination;
  _next_solution = next ;
  _instance = instance ;
  _registry = registry ;
  for (i = 0 ; i < instance->agent_count ; i ++)
    {
      source = (_source_agent + i) % instance->agent_count ;
      for (
        destination = 0 ;
        destination < instance->agent_count ;
        destination ++
      )
        {
          if (destination == source)
            continue ;
          job = current->ll_assignment[source] ;
          while (job = job->next)
            {
              if (instance->cost[destination][job->job]
                    <= current->capacity_left[destination])
                {
                  _transfer_job (job->job, source, destination) ;
                  _update_source_agent() ;
                  return 1 ;
                }
            }
          job = current->ll_assignment[source] ;
          while (job = job->next)
            {
              job1 = current->ll_assignment[destination] ;
              while (job1 = job1->next)
                {
                  if (
                    (instance->cost[destination][job->job] <=
                      (current->capacity_left[destination]
                        + instance->cost[destination][job1->job]))
                    &&
                    (instance->cost[source][job1->job] <=
                      (current->capacity_left[source]
                        + instance->cost[source][job->job]))
                  )
                    {
                      _swap_jobs (job->job, source, job1->job, destination) ;
                      _update_source_agent() ;
                      return 1 ;
                    }
                }
            }
        }
    }
  return 0 ;
}

static void
_transfer_job (t_job job, t_agent source, t_agent destination)
{
  _remove_job (job, source) ;
  _add_job (job, destination) ;
}

static void
_swap_jobs (t_job job1, t_agent agent1, t_agent agent2, t_job job2)
{
  _remove_job (job1, agent1) ;
  _add_job (job1, agent2) ;
  _remove_job (job2, agent2) ;
  _add_job (job2, agent1) ;
}

static void
_remove_job (t_job job, t_agent agent)
{
  remove_job_from_job_list (_next_solution->ll_assignment[agent], job) ;
  _next_solution->assignment[agent][job] = 0 ;
  _next_solution->capacity_left[agent] += _instance->cost[agent][job] ;
  _next_solution->value -= _instance->gain[agent][job] ;
}

static void
_add_job (t_job job, t_agent agent)
{
  add_job_to_job_list (_next_solution->ll_assignment[agent], job) ;
  _next_solution->assignment[agent][job] = 1 ;
  _next_solution->capacity_left[agent] -= _instance->cost[agent][job] ;
  _next_solution->value += _instance->gain[agent][job] ;
}

static void
_update_source_agent ()
{
  _source_agent = (_source_agent + 1) % _instance->agent_count ;
}
