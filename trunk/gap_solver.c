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
  t_gap_solver_registry registry ;
  parse_cli_arguments (& registry, argc, argv) ;
  registry.get_input (
    registry.input_file,
    & instance,
    & solution
  );
  if ( ! search_solution_0 (& instance, & solution))
    {
      printf ("%s", "pas d\'affectation possible\n") ;
      exit (0) ;
    }
  pthread_t * countdown ;
  registry.duration = 5 ;
  registry.timeout = 0 ;
  pthread_create (countdown, NULL, thread_countdown, & registry) ;
  while ( ! registry.timeout) ;
  print_result (& instance, & solution) ;
}
