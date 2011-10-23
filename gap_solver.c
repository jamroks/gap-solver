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
main(int argc, char ** argv)
{
  t_gap_solver_context context ;
  t_gap_instance instance ;
  t_gap_solution solution ;
  parse_cli_arguments (argc, argv, & context);
  context.get_input (
    context.input_file,
    & instance,
    & solution
  );
  search_solution_0 (& instance, & solution);
  print_result (& instance, & solution);
}
