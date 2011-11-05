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

void annealing (
  t_gap_instance * instance,
  t_gap_solution * solution,
  t_gap_solver_registry * registry
)
{
  t_bool (* next_solution) (
    t_solution_change *,
    t_gap_instance *,
    t_gap_solution *,
    t_gap_solver_registry *,
    t_bool
  ) ;
  pthread_t operator ;
  t_solution_change change ;
  switch (registry->neighbourhood_exploration)
    {
      case NEIGHBOURHOOD_EXPLORATION_DETERMINIST:
        next_solution = next_solution_sequential ;
        break ;
      case NEIGHBOURHOOD_EXPLORATION_STOCHASTIC:
        next_solution = stochastic_next_solution ;
        break ;
    }      if (registry->verbose)
  simple_search (instance, solution, registry) ;
  pthread_create (& operator, NULL, thread_operator, registry) ;
  while ( ! registry->timeout)
    {
      if (registry->step_timeout)
        {
          simple_search (instance, solution, registry) ;
          registry->step_timeout = FALSE ;
        }
      next_solution (& change, instance, solution, registry, FALSE) ;
      if ( 
        solution_evaluation (
          change.delta_value,
          registry->problem_type,
          registry->step_temperature[registry->step_current]
        )
      )
        solution_apply_change (instance, solution, & change) ;
    }
    char file[300] ;
    sprintf (
      file,
      "%s/%s_%d_%d",
      DIRECTORY_RESULT_DUMP,
      registry->instance_name,
      solution->value,
      time (NULL)
    ) ;
    FILE * dump = fopen (file, "w") ;
    print_result(
      dump,
      instance,
      solution
    ) ;
    fclose (dump) ;
}
