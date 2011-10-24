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
parse_cli_arguments (t_gap_solver_registry * registry, int argc, char ** argv)
{
  FILE *file;
  if (argc < 2)
    {
      fprintf (stderr, "%s", "un nom de fichier est attendu\n") ;
      exit (1) ;
    }
  registry->input_file = argv[argc - 1] ;
  if (NULL == (file = fopen (registry->input_file, "rt")))
    {
      fprintf (
        stderr,
        "erreur lors de l'ouverture de : \"%s\"\n",
        registry->input_file
      ) ;
      exit (1) ;
    }
  fclose (file);
  registry->problem_type = MAXIMIZATION ;
  registry->get_input = & read_orlibrary_input_file ;
  registry->get_next_solution = & determinist_next_solution ;
}

char *
get_usage()
{
/*
--duration 
--start-temperature
--temperature-decrease-function
--temperature-time-decrease-function
--neighborhood
--verbose
--Version
--about
--help
*/
}