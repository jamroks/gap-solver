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

static int _assigned_count = 0 ;

static short * _assigned = NULL ;

static short
_alloc_assigned(short *, int) ;

static void
_assign (t_gap_instance *, t_gap_solution *, int, int) ;

static short
_is_assigned (int) ;

static void
_update_mean (float *, float *, int, int) ;

short
search_solution_0 (t_gap_instance * instance, t_gap_solution * solution)
{
  _alloc_assigned (_assigned, instance->job_count) ;
  float ratio[instance->agent_count][instance->job_count] ; // (job capacity cost) / (agent capacity) ratios
  int agent, job ;
  for (agent = 0 ; agent < instance->agent_count ; agent ++) // ratios initialization
    for (job = 0 ; job < instance->job_count ; job ++)
      ratio[agent][job] =
        (float) instance->cost[agent][job] / (float) solution->capacity_left[agent];
  int max_job, min_agent ;
  float max_mean, min_ratio ;
  float mean[instance->job_count] ; // ratio means
  while (_assigned_count < instance->job_count)
    {  
      _update_mean (mean, ratio[0], instance->agent_count, instance->job_count) ;
      max_mean = 0.0 ;
      max_job = -1 ;
      for (job = 0 ; job < instance->job_count ; job ++)
        if (_is_assigned(job))
          continue;
        else if (mean[job] > max_mean)
          {
            max_mean = mean[job] ;
            max_job = job ;
          }
      min_ratio = 1.0;
      min_agent = -1;
      for (agent = 0 ; agent < instance->agent_count ; agent ++)
          if (ratio[agent][max_job] <= 1 && ratio[agent][max_job] < min_ratio)
            {
              min_ratio = ratio[agent][max_job];
              min_agent = agent ;
            }
      if (min_agent == -1)
        return 0 ;
      _assign(instance, solution, min_agent, max_job);
      for (job = 0 ; job < instance->job_count ; job ++)
        if (_is_assigned(job))
          continue ;
        else
          ratio[min_agent][job] =
            (float) instance->cost[min_agent][job] / (float) solution->capacity_left[min_agent];
    }
  return 1;
}

static void
_update_mean (float * mean, float * ratio, int agent_count, int job_count)
{
  int job, agent ;
  float sum ;
  for (job = 0 ; job < job_count ; job ++)
    {
      if (_is_assigned (job))
        continue;
      sum = 0.0;
      for (agent = 0 ; agent < agent_count ; agent ++)
        {
          sum += ratio[agent_count * agent + job] ;
        }
      mean[job] = sum / (float) agent_count ;
    }
}

static short
_alloc_assigned (short * assigned, int job_count)
{
  if (NULL == (_assigned = calloc (sizeof(short), job_count)))
    return 0 ;
  int i;
  for (i = 0 ; i < job_count ; i++)
    _assigned[i] = 0 ;
  return 1;
}

static void
_assign (t_gap_instance * instance, t_gap_solution * solution, int agent, int job)
{
  solution->value += instance->gain[agent][job] ;
  solution->capacity_left[agent] -= instance->cost[agent][job] ;
  solution->assignment[agent][job] = 1 ;
  _assigned[job] = 1 ;
  _assigned_count ++ ;
}

static short
_is_assigned (int job) 
{
  return _assigned[job];
}
