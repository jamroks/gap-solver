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

static enum _INDICES {
  INDEX_PROBLEM_TYPE,
  INDEX_NEIGHBOURHOOD_EXPLORATION,
  INDEX_DURATION,
  INDEX_STEP_COUNT,
  INDEX_STEP_SCHEDULE,
  INDEX_TEMPERATURE_FIRST,
  INDEX_TEMPERATURE_LAST,
  INDEX_TEMPERATURE_SCHEDULE,
  INDEX_VERBOSE,
} ;

static t_configuration_annealing * _annealing ;

static t_configuration_execution * _execution,

short
parse_cli_arguments (
  t_configuration_annealing * annealing,
  t_configuration_execution * execution,
  int argc,
  char ** argv
)
{
  _annealing = annealing ;
  _execution = execution ;
  FILE *file;
  if (argc < 2)
    {
      fprintf (stderr, "%s", "un nom de fichier est attendu\n") ;
      exit (1) ;
    }
  execution->input_source = INPUT_SOURCE_FILE ;
  execution->input_file = argv[argc - 1] ;
  if (NULL == (file = fopen (execution->input_file, "rt")))
    {
      fprintf (
        stderr,
        "erreur lors de l'ouverture de : \"%s\"\n",
        execution->input_file
      ) ;
      exit (1) ;
    }
  fclose (file);
  annealing->problem_type = MAXIMIZATION ;
  annealing->duration = 0 ;
}

static short
_get_option_parameters(
  int argc,
  char ** argv
)
{
  int option_index, c ;
  struct option long_option[] =
  {
    {"problem_type", required_argument, NULL, INDEX_PROBLEM_TYPE},
    {"neighbourhood_exploration", required_argument, NULL, INDEX_NEIGHBOURHOOD_EXPLORATION},
    {"duration", required_argument, NULL, INDEX_DURATION},
    {"step_schedule", required_argument, NULL, INDEX_STEP_SCHEDULE},
    {"step_count", required_argument, NULL, INDEX_STEP_COUNT},
    {"temperature_schedule", required_argument, NULL, INDEX_TEMPERATURE_SCHEDULE},
    {"temperature_first", required_argument, NULL, INDEX_TEMPERATURE_FIRST},
    {"temperature_last", required_argument, NULL, INDEX_TEMPERATURE_LAST},
    {"verbose", no_argument, NULL, INDEX_VERBOSE},
  };
  while (-1 != (c = getopt_long (argc, argv, "d:s:S:t:T:u:p:n:v", long_option, & option_index)))
    switch (c)
      {
        case 0:
          switch (option_index)
            {
              case INDEX_PROBLEM_TYPE:
                  
                break ;

              case INDEX_NEIGHBOURHOOD_EXPLORATION:
                  
                break ;

              case INDEX_DURATION:
                  
                break ;

              case INDEX_STEP_SCHEDULE:
                  
                break ;

              case INDEX_STEP_COUNT:
                  
                break ;

              case INDEX_TEMPERATURE_SCHEDULE:
                  
                break ;

              case INDEX_TEMPERATURE_FIRST:
                  
                break ;

              case INDEX_TEMPERATURE_LAST:
                  
                break ;

              case INDEX_VERBOSE:
                  
                break ;
            }
          break ;
        case 'd':
          break ;
        case 's':
          break ;
        case 'S':
          break ;
        case 't':
          break;
        case 'T':
          break ;
        case 'u':
          break ;
        case 'p':
          break ;
        case 'n':
          break ;
        case 'v':
          break ;
      }
    printf("%s", optarg) ;
}
