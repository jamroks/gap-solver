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
_job_transfer (t_job job, t_agent source, t_agent destination) ;

static void
_job_remove (t_job job, t_agent agent) ;

static void
_job_add (t_job job, t_agent agent) ;

static void
_job_swap (t_job job1, t_agent agent1, t_agent agent2, t_job job2) ;

static void
_agents_update () ;

static t_bool
_change_is_improving () ;

static t_agent _agent_source = 0 ;

static t_agent _agent_destination = 1 ;

static t_gap_instance * _instance ;

static t_gap_solver_registry * _registry ;

static t_solution_change * _change ;

static t_job _job_destination = -1 ;

/**
 * Offer a new practicable solution to the GAP instance.
 * Operates in a *determinist* fashion, minus a turnover,
 * which occurs on agents, from call to call.
 *
 * @param change	Changes to be made to the current solution
 *
 * @param instance	GAP instance
 *
 * @param current	Current solution
 *
 * @param registry	Application level variables
 *
 * @param improvement	Return improving change
 *
 * @return 		TRUE if a new solution was found, FALSE otherwise
 */
short
determinist_next_solution (
  t_solution_change * change,
  t_gap_instance * instance,
  t_gap_solution * current,
  t_gap_solver_registry * registry,
  t_bool improvement
)
{
  t_job_list * job, *job1 ;
  int i, j, source, destination;
  _change = change ;
  _instance = instance ;
  _registry = registry ;
  change->delta_value = 0 ;
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

// printf("considering transfer %d %d %d\n", source, destination, job->job);

              if (instance->cost[destination][job->job]
                    <= current->capacity_left[destination])
                {
                  _job_transfer (job->job, source, destination) ;
                  if (improvement && ! _change_is_improving())
                    {
                      change->delta_value = 0 ;
                      continue ;
                    }

// printf("%d transfer done: %d %d %d\n", change->delta_value, job->job, source, destination);

                  _agents_update() ;
                  return TRUE ;
                }
            }
          // Then, we look for any possible swap
          job = current->ll_assignment[source] ;
          while (job = job->next)
            { 

// printf("considering job swap : %d %d\n", source, job->job);

              job1 = current->ll_assignment[destination] ;
              while (job1 = job1->next)
                {

// printf("with %d : %d\n", destination, job1->job);

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
                      if (improvement && ! _change_is_improving())
                        {
                          change->delta_value = 0 ;
                          continue ;
                        }

// printf("%d swap done: %d %d %d %d\n", change->delta_value, job->job, source, job1->job, destination);

                      _agents_update () ;
                      return TRUE ;
                    }
                }
            }
        }
    }
  return FALSE ;
}

void XAVIER_neighbourhood_determinist_try (
  t_gap_solution * solution,
  t_gap_instance * instance,
  t_gap_solver_registry * registry)
{
  t_solution_change change ;
//  print_result(instance, solution) ;
  int delta = 0 ;
  while (TRUE)
    {
      if (
        determinist_next_solution (
          & change,
          instance,
          solution,
          registry,
          TRUE
        )
      )
        {
          delta += change.delta_value ;
          solution_apply_change ( instance, solution , & change) ;
        }
      else
        break ;
    }
//    printf("%d\n", delta);
//    print_result (instance, solution) ;
}

static t_bool
_change_is_improving ()
{
  switch (_registry->problem_type)
    {
      case MAXIMIZATION:
        if (_change->delta_value <= 0)
          return FALSE ;
        break ;
      case MINIMIZATION:
        if (_change->delta_value >= 0)
          return FALSE ;
        break ;
    }
  return TRUE ;
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
_job_swap (t_job job1, t_agent agent1, t_job job2, t_agent agent2)
{
  _change->type = SOLUTION_CHANGE_SWAP ;
  _change->contents.swap.source_swapped_job = job1 ;
  _change->contents.swap.source = agent1 ;
  _change->contents.swap.destination_swapped_job = job2 ;
  _change->contents.swap.destination = agent2 ;
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
  _agent_source ++ ;
  if (_agent_source != 0 && _agent_source % _instance->agent_count == 0)
  {
    _agent_destination = (_agent_destination + 1) % _instance->agent_count ;
    _agent_source = 0 ;
  }
}
