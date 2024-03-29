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
_agents_update () ;

static void
_job_remove (t_job job, t_agent agent) ;

static void
_job_add (t_job job, t_agent agent) ;

static void
_job_transfer (t_job job, t_agent source, t_agent destination) ;

static void
_job_swap (t_job job1, t_agent agent1, t_agent agent2, t_job job2) ;

static t_bool 
_search_transfer (t_agent source, t_agent destination) ;

static t_bool
_search_swap (t_agent source, t_agent destination) ;

static t_bool
_search_multi_swap (t_agent source, t_agent destination) ;

static t_bool
_full_swap (t_agent source, t_agent destination) ;

static t_bool
_change_is_improving () ;

static void
_job_multi_swap (
  t_job job1,
  t_agent agent1,
  t_job_list * job2,
  t_agent agent2
) ;

static t_bool
_job_multi_swap_is_seed (
  t_job job1,
  t_agent agent1,
  t_job_list * job2,
  t_job new
) ;

static t_bool
_job_multi_swap_is_valid (
  t_job job1,
  t_job_list * job2,
  t_agent agent2
) ;

static void
_job_list_list_free (t_job_list_list *head) ;

static t_agent _agent_source = 0 ;

static t_agent _agent_destination = 1 ;

static t_gap_instance * _instance ;

static t_gap_solution * _solution ;

static t_gap_solver_registry * _registry ;

static t_solution_change * _change ;

static t_job _job_destination = -1 ;

static t_bool _improvement ;

/**
 * Offer a new practicable solution to the GAP instance.
 * Operates in a *determinist* fashion, minus a turnover,
 * which occurs on agents, from call to call.
 *
 * @param change	Changes to be made to the current solution
 *
 * @param instance	GAP instance
 *
 * @param solution	Current solution
 *
 * @param registry	Application level variables
 *
 * @param improvement	Return improving change
 *
 * @return 		TRUE if a new solution was found, FALSE otherwise
 */
t_bool
next_solution_sequential (
  t_solution_change * change,
  t_gap_instance * instance,
  t_gap_solution * solution,
  t_gap_solver_registry * registry,
  t_bool improvement
)
{
  t_job_list * job_s, * job_d, * elt ;
  int i, j, source, destination;
  _change = change ;
  _instance = instance ;
  _solution = solution ;
  _registry = registry ;
  _improvement = improvement ;
  change->delta_value = 0 ;
  for (i = 0 ; i < instance->agent_count ; i ++)
    {
      source = (_agent_source + i) % instance->agent_count ;
      for (j = 0 ; j < instance->agent_count ; j ++)
        {
          destination = (_agent_destination + j) % instance->agent_count ;
          if (destination == source)
            continue ;
          if (registry->neighbourhood_transfer)
            if (_search_transfer (source, destination))
              return TRUE ;
          if (registry->neighbourhood_swap)
            if (_search_swap (source, destination))
              return TRUE ;
          if (registry->neighbourhood_multi_swap)
            if (_search_multi_swap (source, destination))
              return TRUE ;
          if (registry->neighbourhood_full_swap)
           if (_full_swap (source, destination))
              return TRUE ;
        }
    }
  return FALSE ;
}

static t_bool _search_transfer (
  t_agent source,
  t_agent destination
)
{
  t_job_list * job_s ;
  job_s = _solution->ll_assignment[source] ;
  while (job_s = job_s->next)
    {
      if (_instance->cost[destination][job_s->job]
          <= _solution->capacity_left[destination])
        {
          _job_transfer (job_s->job, source, destination) ;
          if (_improvement && ! _change_is_improving())
            continue ;
          _agents_update() ;
          return TRUE ;
        }
    }
  return FALSE ;
}

static t_bool _search_swap (
  t_agent source,
  t_agent destination
)
{
  t_job_list * job_s, * job_d ;
  job_s = _solution->ll_assignment[source] ;
  while (job_s = job_s->next)
    {
      job_d = _solution->ll_assignment[destination] ;
      while (job_d = job_d->next)
        {
          if (
            (_instance->cost[destination][job_s->job] <=
             (_solution->capacity_left[destination]
              + _instance->cost[destination][job_d->job]))
            &&
            (_instance->cost[source][job_d->job] <=
             (_solution->capacity_left[source]
              + _instance->cost[source][job_s->job]))
          )
            {
              _job_swap (job_s->job, source, job_d->job, destination) ;
              if (_improvement && ! _change_is_improving())
                continue ;
              _agents_update () ;
              return TRUE ;
            }
        }
    }
  return FALSE ;
}

static t_bool _search_multi_swap (
  t_agent source,
  t_agent destination
)
{
  t_job_list_list * list, * list_i ;
  t_job_list * job_s, * job_d, * elt ;
  int iteration ;
  job_s = _solution->ll_assignment[source] ;
  while (job_s = job_s->next)
    {
      iteration = 0 ;
      list = job_list_list_allocate_head () ;
      elt = job_list_allocate_head () ;
      job_list_list_add_job_list (list, elt) ;
      job_d = _solution->ll_assignment[destination] ;
      while (job_d = job_d->next)
        {
          list_i = list ;
          while (list_i = list_i->next)
            {
              if (
                _job_multi_swap_is_seed (
                  job_s->job,
                  source,
                  list_i->job_list,
                  job_d->job
                )
              )
                {
                  elt = job_list_allocate_head () ;
                  job_list_clone (elt, list_i->job_list) ;
                  job_list_add_job (elt, job_d->job) ;
                  job_list_list_add_job_list (list, elt) ;
                  if (_job_multi_swap_is_valid (job_s->job, elt, destination))
                    {
                      _job_multi_swap (job_s->job, source, elt, destination) ;
                      if (_improvement && ! _change_is_improving ())
                        {
                          job_list_list_delete_job_list (list, elt) ;
                          continue ;
                        }
                      elt = job_list_allocate_head () ;
                      job_list_clone (
                        elt,
                        _change->contents.multi_swap.destination_swapped_job
                      ) ;
                      _change->contents.multi_swap.destination_swapped_job
                        = elt ;
                      _job_list_list_free (list) ;
                      return TRUE ;
                    }
                }
                  
              iteration ++ ;
              if (iteration > _registry->neighbourhood_multi_swap_max_iteration)
                 return FALSE ;
            }
        }
      _job_list_list_free (list) ;
    }
  return FALSE ;
}

static t_bool
_full_swap (t_agent source, t_agent destination)
{
  int new_cost_s, new_cost_d, gain_s, new_gain_s, gain_d, new_gain_d ;
  t_job_list * job_s, * job_d ;
  new_gain_s = new_gain_d = gain_s = new_gain_s = gain_d = new_gain_d = 0 ;
  job_s = _solution->ll_assignment[source] ;
  job_d = _solution->ll_assignment[destination] ;
  while (job_s = job_s->next)
    {
      gain_s += _instance->gain[source][job_s->job] ;
      new_gain_d += _instance->gain[destination][job_s->job] ;
      new_cost_d += _instance->cost[destination][job_s->job] ;
    }
  while (job_d = job_d->next)
    {
      gain_d += _instance->gain[destination][job_d->job] ;
      new_gain_s += _instance->gain[source][job_d->job] ;
      new_cost_s += _instance->cost[source][job_d->job] ;
    }
  _change->delta_value = new_gain_s - gain_s + new_gain_d - gain_d ;
  _change->type = SOLUTION_CHANGE_FULL_SWAP ;
  _change->contents.full_swap.source = source ;
  _change->contents.full_swap.destination = destination ;
  if (
    new_cost_s <= _instance->capacity[source]
    && new_cost_d <= _instance->capacity[destination]
  )
    {
      if (_improvement  && ! _change_is_improving ())
        return FALSE ;
      return TRUE ;
    }
  return FALSE ;
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
  _change->delta_value = 0 ;
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
  _change->delta_value = 0 ;
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
_job_multi_swap (
  t_job job1,
  t_agent agent1,
  t_job_list * job2,
  t_agent agent2
)
{
  t_job_list * elt = job2 ;
  _change->delta_value = 0 ;
  _change->type = SOLUTION_CHANGE_MULTI_SWAP ;
  _change->contents.multi_swap.source_swapped_job = job1 ;
  _change->contents.multi_swap.source = agent1 ;
  _change->contents.multi_swap.destination_swapped_job = job2 ;
  _change->contents.multi_swap.destination = agent2 ;
  while (elt = elt->next)
    {
      _job_add (elt->job, agent1) ;
      _job_remove (elt->job, agent2) ;
    }
  _job_remove (job1, agent1) ;
  _job_add (job1, agent2) ;
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

static t_bool
_job_multi_swap_is_seed(
  t_job job1,
  t_agent agent1,
  t_job_list * job2,
  t_job new
)
{
  t_job_list * elt ;
  int cost ;
  elt = job2 ;
  cost = _instance->cost[agent1][new] ;
  while (elt = elt->next)
    cost += _instance->cost[agent1][elt->job] ;
  cost -= _instance->cost[agent1][job1] ;
  return cost <= _solution->capacity_left[agent1] ;
}

static t_bool
_job_multi_swap_is_valid (t_job job1, t_job_list * job2, t_agent agent2)
{
  t_job_list * elt ;
  int gain ;
  elt = job2 ;
  gain = 0 ;
  while (elt = elt->next)
    {
      gain += _instance->cost[agent2][elt->job] ;
    }
  gain -= _instance->cost[agent2][job1] ;
  return (_solution->capacity_left[agent2] + gain) >= 0 ;
}

static void
_job_list_list_free (t_job_list_list * head)
{
  job_list_list_free (head) ;
  free (head) ;
}
