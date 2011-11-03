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

static void
_job_transfer(t_job job, t_agent source, t_agent destination) ;

static void
_job_remove (t_job job, t_agent agent) ;

static void
_job_add (t_job job, t_agent agent) ;

static void
_job_swap (t_job job1, t_agent agent1, t_agent agent2, t_job job2) ;

static void
_agents_update () ;

static int _agent_source = 0 ;

static int _agent_destination = 1 ;

static t_gap_instance * _instance ;

static t_gap_solver_registry * _registry ;

static t_solution_change * _change ;

/**
 *
 * Offer a new practicable solution to the GAP instance, from a current one.
 * Operates in a determinist fashion ;
 * if consecutively called from a given solution,
 * at the same time, from different program calls,
 * the same changes will always be proposed at the same step.
 * A turnover occurs on agents, from one call to the next.
 * Because of this turnover, several calls from the same solution,
 * will not result in the same change proposition.
 * It is determinist at the program execution level.
 *
 * @param change	Changes to be made to the current solution
 *
 * @param instance	GAP instance
 *
 * @param current	Current solution
 *
 * @param registry	Application level variables
 *
 */
short
determinist_next_solution (
  t_solution_change * change,
  t_gap_instance * instance,
  t_gap_solution * current,
  t_gap_solver_registry * registry
)
{
  t_job_list * job, *job1 ;
  int i, j, source, destination;
  _change = change ;
  _instance = instance ;
  _registry = registry ;
  for (i = 0 ; i < instance->agent_count ; i ++)
    {
      source = (_agent_source + i) % instance->agent_count ;
      for (j = 0 ; j < instance->agent_count ; j ++)
        {
          destination = (_agent_destination + j) % instance->agent_count ;
          if (destination == source)
            continue ;
          // First we look for any possible transfer
          job = current->ll_assignment[source] ;
          while (job = job->next)
            {
              if (instance->cost[destination][job->job]
                    <= current->capacity_left[destination])
                {
                  _job_transfer(job->job, source, destination) ;
                  _agents_update() ;
                  return 1 ;
                }
            }
          // Then, we look for any possible swap
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
                      _job_swap (job->job, source, job1->job, destination) ;
                      _agents_update () ;
                      return 1 ;
                    }
                }
            }
        }
    }
  return 0 ;
}

void XAVIER_neighbourhood_determinist_try (
  t_gap_solution * solution,
  t_gap_instance * instance,
  t_gap_solver_registry * registry)
{
  t_solution_change change ;
  print_result (instance, solution) ;
  int i ;
  for (i = 0 ; i < 5000 ; i ++)
  {
  change.delta_value = 0 ;
  determinist_next_solution (
    & change,
    instance,
    solution ,
    registry
  ) ;
 // printf("%d\n", change.delta_value) ;
  }
}

static void
_job_transfer (t_job job, t_agent source, t_agent destination)
{
  _change->type = SOLUTION_CHANGE_TRANSFER ;
  _change->contents.transfer.source = source ;
  _change->contents.transfer.destination = destination ;
  _change->contents.transfer.job = job ;
  _job_remove (job, source) ;
  _job_add (job, destination) ;
}

static void
_job_swap (t_job job1, t_agent agent1, t_agent agent2, t_job job2)
{
  _change->type = SOLUTION_CHANGE_SWAP ;
  _change->contents.swap.source_swapped_job = job1 ;
  _change->contents.swap.source = agent1 ;
  _change->contents.swap.destination_swapped_job = job2 ;
  _change->contents.swap.destination = agent1 ;
  _job_remove (job1, agent1) ;
  _job_add (job1, agent2) ;
  _job_remove (job2, agent2) ;
  _job_add (job2, agent1) ;
}

static void
_job_remove (t_job job, t_agent agent)
{
  _change->delta_value -= _instance->gain[agent][job] ;
}

static void
_job_add (t_job job, t_agent agent)
{
  _change->delta_value += _instance->gain[agent][job] ;
}

static void
_agents_update ()
{
  _agent_source = (_agent_source + 1) % _instance->agent_count ;
  _agent_destination = (_agent_destination + 1) % _instance->agent_count ;
}
