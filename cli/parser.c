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

static void _set_simple_search () ;

static void _set_full_result () ;

static void _set_problem_type () ;

static void _set_neighbourhood_exploration () ;

static void _set_duration () ;

static void _set_step_schedule () ;

static void _set_step_count () ;

static void _set_temperature_schedule () ;

static void _set_temperature_first () ;

static void _set_temperature_last () ;

static void _set_verbose () ;

static void _display_help () ;

static void _set_agt_ponderation () ;

//static void _job_ponderation () ;

static short _get_option_parameters (int argc, char ** argv) ;

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
  if (argc < 2)
    {
      fprintf (stderr, "%s", "a file is expected as parameter\n") ;
      return 0 ;
    }
  execution->input_file = argv[argc - 1] ;
  _get_option_parameters (argc, argv) ;
  return 1 ;
}

static short
_get_option_parameters (
  int argc,
  char ** argv
)
{
  int option_index, c ;
  struct option long_option[] =
  {
    {"simple_search", no_argument, NULL, 'S'},
    {"full_result", no_argument, NULL, 'M'},
    {"problem_type", required_argument, NULL, 'P'},
    {"neighbourhood_exploration", required_argument, NULL, 'N'},
    {"duration", required_argument, NULL, 'D'},
    {"step_schedule", required_argument, NULL, 'X'},
    {"step_count", required_argument, NULL, 'C'},
    {"temperature_schedule", required_argument, NULL, 'Y'},
    {"temperature_first", required_argument, NULL, 'F'},
    {"temperature_last", required_argument, NULL, 'L'},
    {"job_ponderation", required_argument, NULL, 'J'},
    {"agt_ponderation", required_argument, NULL, 'A'},
    {"verbose", no_argument, NULL, 'V'},
    {"help", no_argument, NULL, 'H'},
    {NULL, 0, NULL, 0}
  };
  while (-1 != (c = getopt_long (argc, argv, "S:F:P:N:D:X:C:Y:F:L:A:J:V:H", long_option, & option_index)))
    switch (c)
      {
        case 'M':
         _set_full_result () ;
        case 'S':
         _set_simple_search () ;
        break ;
        case 'P':
         _set_problem_type () ;
        break ;
        case 'N':
          _set_neighbourhood_exploration () ;
        break ;
        case 'D':
          _set_duration () ;
        break ;
        case 'X':
          _set_step_schedule () ;
        break ;
        case 'C':
          _set_step_count () ;
        break ;
        case 'Y':
          _set_temperature_schedule () ;
        break ;
/*        case 'J':
          _set_job_ponderation () ;
        break ;
*/      case 'A':
          _set_agt_ponderation () ;
        break ;
        case 'F':
          _set_temperature_first () ;
        break ;
        case 'L':
          _set_temperature_last ();
        break ;
        case 'V':
          _set_verbose ();
        break ;
        case 'H':
          _display_help ();
        break ;
      }
}

static void
_set_simple_search ()
{
  _execution->simple_search = TRUE ;
}

static void
_set_full_result ()
{
  _execution->full_result = TRUE ;
}

static void
_set_problem_type ()
{
  int value ;
  if (-1 != (value = validate_problem_type (optarg)))
    _execution->problem_type = value;
  else
    fprintf (stderr, "warning: unexpected temperature schedule argument \"%s\"\n", optarg) ;
}

static void
_set_neighbourhood_exploration ()
{
  int value ;
  if (-1 != (value = validate_neighbourhood_exploration (optarg)))
    _execution->neighbourhood_exploration = value;
  else
    fprintf (stderr, "warning: unexpected neighbourhood exploration argument \"%s\"\n", optarg) ;
}

static void
_set_duration ()
{
  int value = atoi (optarg) ;
  if (validate_duration (value))
    _annealing->duration = value ;
  else
    fprintf (stderr, "warning: unexpected duration argument \"%d\"\n", value) ;
}

static void
_set_step_schedule()
{
  int value ;
  if (-1 != (value = validate_step_schedule (optarg)))
    _annealing->step_schedule = value;
  else
    fprintf (stderr, "warning: unexpected step schedule argument \"%s\"\n", optarg) ;
}

static void
_set_step_count()
{
  int value = atoi (optarg) ;
  if (validate_step_count (value))
    _annealing->step_count = value ;
  else
    fprintf (stderr, "warning: unexpected step count argument \"%d\"\n", value) ;
}

static void
_set_temperature_schedule ()
{
  int value ;
  if (-1 != (value = validate_temperature_schedule (optarg)))
    _annealing->temperature_schedule = value;
  else
    fprintf (stderr, "warning: unexpected temperature schedule argument \"%s\"\n", optarg) ;
}

static void
_set_agt_ponderation ()
{
  int value ;
  if (-1 != (value = validate_agent_ponderation (optarg)))
    {
      switch (value)
        {
          case AGENT_PONDERATION_UNIFORM :
            _annealing->agtponderate= & _uniform ;
            break ;
          case AGENT_PONDERATION_CAPACITY :
            _annealing->agtponderate= & _capacity ;
            break ;
          case AGENT_PONDERATION_CAPACITY_LEFT :
            _annealing->agtponderate= & _capacity_left ;
            break ;
          case AGENT_PONDERATION_ASSIGNMENT :
            _annealing->agtponderate= & _assignment ;
            break ;
        } ; 
    }
  else
    fprintf (stderr, "warning: unexpected agent ponderation function argument \"%s\"\n", optarg) ;
}
/*
static void
_set_job_ponderation ()
{
  int value ;
  if (-1 != (value = validate_job_ponderation (optarg)))
    _annealing->job_ponderation = value;
  else
    fprintf (stderr, "warning: unexpected job ponderation function argument \"%s\"\n", optarg) ;
}
*/
static void
_set_temperature_first ()
{
  int value = atoi (optarg) ;
  if (validate_temperature (value))
    _annealing->temperature_first = value ;
  else
    fprintf (stderr, "warning: unexpected temperature first argument \"%d\"\n", value) ;
}

static void
_set_temperature_last ()
{
  int value = atoi (optarg) ;
  if (validate_temperature (value))
    _annealing->temperature_last = value ;
  else
    fprintf (stderr, "warning: unexpected temperature last argument \"%d\"\n", value) ;
}

static void
_set_verbose ()
{
  _execution->verbose = 1 ;
}

static void
_display_help ()
{

}

