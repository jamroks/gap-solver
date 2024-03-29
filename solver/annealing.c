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

static t_bool
_solution_is_improved (
  t_gap_solution * best,
  t_gap_solution * new,
  t_problem_type type
) ;

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
  t_gap_solution best_solution ;
  clone_gap_solution (& best_solution, solution) ;
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
    }
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
        if (
          _solution_is_improved (
            & best_solution,
            solution,
            registry->problem_type
          )
        )
          {
            free_gap_solution (& best_solution) ;
            clone_gap_solution (& best_solution, solution) ;
          }
          
        solution_apply_change (instance, solution, & change) ;
    }

    free_gap_solution (solution) ;
    clone_gap_solution (solution, & best_solution) ;

    //registry->memorization.best_solution = registry->best_solution ;
    memorize_best( instance , solution , registry ) ;

    char file[300] ;
    sprintf (
      file,
      "%s/",
      DIRECTORY_RESULT_DUMP
    ) ;
    switch (registry->problem_type)
    {
      case MAXIMIZATION:
        sprintf (file, "%s%s_", file, "max");
        break ;
      case MINIMIZATION:
        sprintf (file, "%s%s_", file, "min");
        break ;
    }
    sprintf (
      file,
      "%s%s_%d_%ld",
      file,
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
    sprintf (
      file,
      "%s_conf",
      file
    ) ;
    FILE * conf = fopen (file, "w") ;
    int i ;
    
    switch (registry->neighbourhood_exploration)
    {
      case NEIGHBOURHOOD_EXPLORATION_DETERMINIST:
        fprintf (conf, "%s\n", "sequential");
        break ;
      case NEIGHBOURHOOD_EXPLORATION_STOCHASTIC:
        fprintf (conf, "%s\n", "stochastic");
        break ;
    }
    for (i = 0 ; i < registry->step_count ; i ++)
      fprintf (conf, "%d ", registry->step_duration[i]) ;
    fprintf (conf, "\n") ;
    for (i = 0 ; i < registry->step_count ; i ++)
      fprintf (conf, "%d ", registry->step_temperature[i]) ;
    fprintf (conf, "\n") ;
    fclose (conf) ;
}

static t_bool
_solution_is_improved (
  t_gap_solution * best,
  t_gap_solution * new,
  t_problem_type type
)
{
   switch (type)
    {
      case MAXIMIZATION:
        return ((best->value - new->value) < 0) ? TRUE : FALSE ;
        break ;
      case MINIMIZATION:
        return ((best->value - new->value) < 0) ? FALSE : TRUE ;
        break ;
    }
}
