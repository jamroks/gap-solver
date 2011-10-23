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

short
search_solution_0 (t_gap_instance * instance, t_gap_solution * solution)
{
  int assigned;
  // (job capacity cost) / (agent capacity) ratios
  float ratio[instance->agent_count][instance->job_count];
  // mean of job capacity cost on each agent
  float mean[instance->job_count];
  // ratios initialization
  int agent, job;
  for (agent = 0 ; agent < instance->agent_count ; agent ++)
    {
      for (job = 0 ; job < instance->job_count ; job ++)
        {
          ratio[agent][job] = instance->cost[agent][job] / solution->capacity_left[agent];
        }
    }

  for (assigned = 0 ; assigned < instance->job_count ; )
    {
      _update_mean (mean, ratio, instance) ;
    }
}

static void
_update_mean (
  float ** mean,
  t_gap_instance * instance,
  t_gap_solution * solution,
  t_gap_instance * instance
)
{

}
