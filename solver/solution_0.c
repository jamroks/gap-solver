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
_update_mean (float *, float *, int, int);

short
search_solution_0 (t_gap_instance * instance, t_gap_solution * solution)
{
  float ratio[instance->agent_count][instance->job_count]; // (job capacity cost) / (agent capacity) ratios
  int agent, job;
  for (agent = 0 ; agent < instance->agent_count ; agent ++) // ratios initialization
    {
      for (job = 0 ; job < instance->job_count ; job ++)
        {
          ratio[agent][job] = instance->cost[agent][job] / solution->capacity_left[agent];
        }
    }
  int assigned, max_mean_job, min_ratio_agent;
  float mean[instance->job_count]; // mean of job capacity cost on each agent
  for (assigned = 0 ; assigned < instance->job_count ; assigned ++)
    {
      _update_mean (mean, ratio[0], instance->agent_count, instance->job_count) ;
      for (max_mean_job = job = 0 ; job < instance->job_count ; job ++)
        if (mean[job] > mean[max_mean_job])
          max_mean_job = job ;
      for (min_ratio_agent = agent = 0; agent < instance->agent_count ; agent ++)
        if (ratio[agent][max_mean_job] < ratio[min_ratio_agent][max_mean_job])
          min_ratio_agent = agent ;
      if (solution->capacity_left[agent] < instance->cost[min_ratio_agent][max_mean_job])
        return 0 ;
      solution->capacity_left[agent] -= instance->cost[min_ratio_agent][max_mean_job] ;
      solution->assignment[min_ratio_agent][max_mean_job] = 1 ;
      for (job = 0; job < instance->job_count ; job ++)
        ratio[min_ratio_agent][job] = instance->cost[min_ratio_agent][job] / solution->capacity_left[min_ratio_agent];
    }
  return 1;
}

static void
_update_mean (
  float * mean,
  float * ratio,
  int agent_count,
  int job_count
)
{
  int job, agent ;
  float sum ;
  for (job = 0 ; job < job_count ; job ++)
    {
      for (agent = 0 ; agent < agent_count ; agent ++)
        {
          sum += ratio[agent_count * agent + job] ;
        }
      mean[job] = sum / job_count ;
    }
}
