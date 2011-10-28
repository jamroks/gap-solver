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

static void _set_problem_type () ;

static void _set_neighbourhood_exploration () ;

static void _set_duration () ;

static void _set_step_schedule () ;

static void _set_step_count () ;

static void _set_temperature_schedule () ;

static void _set_temperature_first () ;

static void _set_temperature_last () ;

static void _set_verbose () ;

// Indices used by getopt_long
enum _INDICES {
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

static t_configuration_execution * _execution ;

/**
 * Populates the passed structure with the given command line arguments
 * @param annealing	Annealing configuration 
 * @param execution	Execution configuration
 * @param argc		argc from main
 * @param argv		argv from main
 */
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
      fprintf (stderr, "%s", "a file is expected as parameter\n") ;
      exit (1) ;
    }
  execution->input_source = INPUT_SOURCE_FILE ;
  execution->input_file = argv[argc - 1] ;
  if (NULL == (file = fopen (execution->input_file, "rt")))
    {
      fprintf (
        stderr,
        "error opening: \"%s\"\n",
        execution->input_file
      ) ;
      exit (1) ;
    }
  fclose (file);
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
  while (-1 != (c = getopt_long (argc, argv, "p:n:d:s:S:t:T:u:v", long_option, & option_index)))
    switch (c)
      {
        case 0:
          switch (option_index)
            {
              case INDEX_PROBLEM_TYPE:
                  _set_problem_type () ;
                break ;

              case INDEX_NEIGHBOURHOOD_EXPLORATION:
                  _set_neighbourhood_exploration () ;
                break ;

              case INDEX_DURATION:
                  _set_duration () ;
                break ;

              case INDEX_STEP_SCHEDULE:
                  _set_step_schedule () ;
                break ;

              case INDEX_STEP_COUNT:
                  _set_step_count () ;
                break ;

              case INDEX_TEMPERATURE_SCHEDULE:
                  _set_temperature_schedule () ;
                break ;

              case INDEX_TEMPERATURE_FIRST:
                  _set_temperature_first () ;
                break ;

              case INDEX_TEMPERATURE_LAST:
                  _set_temperature_last ();
                break ;

              case INDEX_VERBOSE:
                  _set_verbose ();
                break ;
            }
          break ;

        case 'p':
          _set_problem_type () ;
          break ;

        case 'n':
          _set_neighbourhood_exploration () ;
          break ;
        case 'd':
          _set_duration () ;
          break ;

        case 's':
          _set_step_schedule () ;
          break ;

        case 'S':
          _set_step_count () ;
          break ;

        case 't':
          _set_temperature_schedule () ;
          break;

        case 'T':
          _set_temperature_first () ;
          break ;

        case 'u':
          _set_temperature_last ();
          break ;

        case 'v':
          _set_verbose ();
          break ;
      }
}

static void
_set_problem_type ()
{
  int value ;
  if (-1 != (value = validate_problem_type (optarg)))
    _execution->problem_type = value;
  else
    fprintf (stderr, "warning: unexpected temperature schedule argument \"%s\"", optarg) ;
}

static void
_set_neighbourhood_exploration ()
{
  int value ;
  if (-1 != (value = validate_neighbourhood_exploration (optarg)))
    _execution->neighbourhood_exploration = value;
  else
    fprintf (stderr, "warning: unexpected neighbourhood exploration argument \"%s\"", optarg) ;
}

static void
_set_duration ()
{
  int value = atoi (optarg) ;
  if (validate_duration (value))
    _annealing->duration = value ;
  else
    fprintf (stderr, "warning: unexpected duration argument \"%d\"", value) ;
}

static void
_set_step_schedule()
{
  int value ;
  if (-1 != (value = validate_step_schedule (optarg)))
    _annealing->step_schedule = value;
  else
    fprintf (stderr, "warning: unexpected step schedule argument \"%s\"", optarg) ;
}

static void
_set_step_count()
{
  int value = atoi (optarg) ;
  if (validate_step_count (value))
    _annealing->step_count = value ;
  else
    fprintf (stderr, "warning: unexpected step count argument \"%d\"", value) ;
}

static void
_set_temperature_schedule ()
{
  int value ;
  if (-1 != (value = validate_temperature_schedule (optarg)))
    _annealing->temperature_schedule = value;
  else
    fprintf (stderr, "warning: unexpected temperature schedule argument \"%s\"", optarg) ;
}

static void
_set_temperature_first ()
{
  int value = atoi (optarg) ;
  if (validate_temperature (value))
    _annealing->temperature_first = value ;
  else
    fprintf (stderr, "warning: unexpected temperature first argument \"%d\"", value) ;
}

static void
_set_temperature_last ()
{
  int value = atoi (optarg) ;
  if (validate_temperature (value))
    _annealing->temperature_last = value ;
  else
    fprintf (stderr, "warning: unexpected temperature last argument \"%d\"", value) ;
}

static void
_set_verbose ()
{
  _execution->verbose = 1 ;
}

