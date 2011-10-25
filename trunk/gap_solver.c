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

int 
main (int argc, char ** argv)
{
  t_gap_instance instance ;
  t_gap_solution solution ;
  t_configuration_annealing configuration_annealing ;
  t_configuration_execution configuration_execution ;
  t_gap_solver_registry registry ;
  load_configuration_annealing (
    & configuration_annealing,
    "annealing.ini"
  ) ;
  parse_cli_arguments (
    & configuration_annealing,
    & configuration_execution,
    argc,
    argv
  ) ;

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

  if ( ! search_solution_0 (& instance, & solution))
    {
      printf ("%s", "pas d\'affectation possible\n") ;
      exit (0) ;
    }
/*
  countdown : a thread that will stop the process after a given duration
  temperature : a thread that will lower the temperature at the given steps
*/
 // pthread_t * countdown, * temperature ;
 // pthread_create (temperature, NULL, & thread_temperature, & registry) ;
//  pthread_create (countdown, NULL, & thread_countdown, & registry) ;
  print_result (& instance, & solution) ;
}
