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

#include "header/common.h"

static void
_init_configuration_annealing (t_configuration_annealing *) ;

static void
_init_configuration_execution (t_configuration_execution *) ;

static void
_init_registry (
  t_gap_solver_registry * registry,
  t_configuration_annealing * annealing,
  t_configuration_execution * execution
) ;

int 
main (int argc, char ** argv)
{
  int test_b=100 ;
  short error = 0 ;
  t_gap_instance instance ;
  t_gap_solution solution ;
  t_gap_solution next_solution ;
  t_configuration_annealing configuration_annealing ;
  t_configuration_execution configuration_execution ;
  t_gap_solver_registry registry ;
  _init_configuration_annealing (& configuration_annealing) ;
  _init_configuration_execution (& configuration_execution) ;
  load_configuration_annealing (& configuration_annealing, "annealing.ini") ;
  load_configuration_execution (& configuration_execution, "execution.ini") ;
  parse_cli_arguments (
    & configuration_annealing,
    & configuration_execution,
    argc,
    argv
  ) ;
  if ( ! validate_configuration_annealing (& configuration_annealing))
    error = 1 ; 
  if ( ! validate_configuration_execution (& configuration_execution))
    error = 1 ;
  if (error)
    {
      fprintf (stderr, "%s", "enter gapsolver --help or see README for help\n") ;
      exit (1) ;
    }
  registry.step_duration = (int *) calloc (
    configuration_annealing.step_count,
    sizeof (int)
  ) ;
  if ( ! registry.step_duration)
      memory_allocation_error () ;
  registry.step_temperature = (int *) calloc (
    configuration_annealing.step_count,
    sizeof (int)
  ) ;
  if ( ! registry.step_temperature)
      memory_allocation_error () ;
  init_step_schedule (
    registry.step_duration,
    configuration_annealing.step_schedule,
    configuration_annealing.duration,
    configuration_annealing.step_count
  ) ;
  init_temperature_schedule (
    registry.step_temperature,
    configuration_annealing.temperature_schedule,
    configuration_annealing.temperature_first,
    configuration_annealing.temperature_last,
    configuration_annealing.step_count
  ) ;

  int i;
  for (i = 0 ; i < configuration_annealing.step_count ; i++)
    printf ("%d:%d\n", registry.step_duration[i], registry.step_temperature[i]) ;

  switch (configuration_execution.input_source)
    {
      case INPUT_SOURCE_FILE:
        read_orlibrary_input_file (
          configuration_execution.input_file,
          & instance,
          & solution
        );
      break ;
    }
  _init_registry (
    & registry,
    & configuration_annealing,
    & configuration_execution
  ) ;
  if ( ! search_solution_0 (& instance, & solution))
    {
      printf ("%s", "no possible assignment\n") ;
      exit (0) ;
    }
  XAVIER_neighbourhood_determinist_try (
    & solution,
    & instance,
    & registry
  ) ;
/*
  countdown : a thread that will stop the process after a given duration
  temperature : a thread that will lower the temperature at the given steps
*/
 // pthread_t * countdown, * temperature ;
 // pthread_create (temperature, NULL, & thread_temperature, & registry) ;
//  pthread_create (countdown, NULL, & thread_countdown, & registry) ;

  // test voisinage
  //   printf("\n______________________________________\ndebut de paramétrage pour voisinage\n") ;
  registry.problem_type = MINIMIZATION  ;
  registry.verbosity = FALSE  ;

  if (registry.problem_type == MAXIMIZATION)
    {
    printf("problème en MAXIMISATION\n") ;
    }
  else
    {
    printf("problème en MINIMISATION\n") ;
    } ;
  printf("ponderation agent= _capacity_left\n") ;
  printf("ponderation job  = _uniform\n") ;
  registry.agtponderate=&_capacity_left ;
  registry.jobponderate=&_uniform ;
  printf("méthode = TRANSFERT\n") ;
  registry.method=TRANSFERT ;
  registry.unavailable_count=0 ;
  registry.max_try_count = 50 ;
  printf("échec voisinage à %d\n",registry.max_try_count) ;
  registry.max_try_count_failure = 0 ;
  printf("Le voisinage sera ") ;
  if (registry.verbosity) printf("bavard\n") ;
  if (! registry.verbosity) printf("silencieux\n") ;
  printf("fin de paramétrage pour voisinage\n") ;
//                               

//  test voisinage stochastique
srand(time(NULL));
printf("solution initiale:: %d\n",solution.value) ;
printf("\n pour %d tests \n", test_b) ;
  while (test_b > 0)
    {
    stochastic_next_solution (& next_solution , & instance , & solution, & registry) ;
    next_solution.value=objective_cost(&next_solution , & instance ) ;
    memorize_solution( & instance , & next_solution, & registry ) ;
    printf("%d solution courante:: %d    envisagée:: %d\t",test_b,solution.value, next_solution.value) ;
    if (((next_solution.value > solution.value) && (registry.problem_type == MAXIMIZATION))
       || ((next_solution.value < solution.value) && (registry.problem_type == MINIMIZATION)))
      {
      printf("suivie\n") ;
      clone_gap_solution (&solution , &next_solution) ;
      }
    else
      {
      printf("abandonnée\n") ;
      } ;

    test_b-- ;
    } ;
  printf(" nb blocages   =%d\n", registry.unavailable_count) ;
  printf(" nb échec      =%d\n", registry.max_try_count_failure) ;
  printf(" nb transferts =%d\n", registry.transfert_count) ;
  printf(" nb swap       =%d\n", registry.swap_count) ;
//
}

static void
_init_configuration_annealing (t_configuration_annealing * annealing)
{
  annealing->duration = -1 ;
  annealing->step_count = -1 ;
  annealing->step_schedule = STEP_SCHEDULE_UNASSIGNED ;
  annealing->temperature_first = -1 ;
  annealing->temperature_last = -1 ;
  annealing->temperature_schedule = TEMPERATURE_SCHEDULE_UNASSIGNED ;
}

static void
_init_configuration_execution (t_configuration_execution * execution)
{
  execution->input_source = INPUT_SOURCE_FILE ;
  execution->input_file = NULL ;
  execution->problem_type = UNASSIGNED ;
  execution->neighbourhood_exploration = NEIGHBOURHOOD_EXPLORATION_UNASSIGNED ;
}

static void
_init_registry (
  t_gap_solver_registry * registry,
  t_configuration_annealing * annealing,
  t_configuration_execution * execution
)
{
  registry->problem_type = execution->problem_type ;
  registry->step_current = 0 ;
  registry->step_count = annealing->step_count ;
  registry->timeout = 0 ;
  registry->transfert_count = 0 ;
  registry->swap_count = 0 ;
  registry->iteration_count = 0 ;
}
