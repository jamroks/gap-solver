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
#include "../header/type.h"
#include "../header/function.h"

short 
read_orlibrary_input_file(char * file_name, t_gap_instance * instance, t_gap_solution * solution)
{
  FILE *file ;
  int value ;
  int agent, job ;
  file = fopen(file_name, "rt"); 
  if (file == NULL)
    return 1 ; 
  strcpy (instance->name, file_name) ;
  fscanf (file, "%d", & instance->agent_count) ;
  fscanf (file, "%d", & instance->job_count) ;
  alloc_gap_instance (instance, instance->agent_count, instance->job_count) ;
  alloc_gap_solution (solution, instance->agent_count, instance->job_count) ;
  for (agent = 0; agent < instance->agent_count; agent ++)
    {
      for (job = 0; job < instance->job_count; job ++)
      {
        fscanf (file, "%d", & value) ;
        instance->gain[agent][job] = value ;
      }
    };
  for (agent = 0; agent < instance->agent_count ; agent++)
    {
      for (job = 0 ; job < instance->job_count ; job++)
      {
        fscanf (file, "%d", & value);
        instance->cost[agent][job] = value ;
      }
    };
  for (agent = 0 ; agent < instance->agent_count ; agent++)
    {
      fscanf (file, "%d", & value);
      instance->capacity[agent] = value ;
      solution->capacity_left[agent] = value;
    };
  fclose (file) ;
  return 0 ;
}
