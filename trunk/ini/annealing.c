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

/*
 * Parse the simulated annealing parameter file, expected in INI format.
 * The parameters control the annealing process.
 * They define the temperature schedule and the step schedule,
 * which are later computed from them.
 *
 * @param	configuration	An in/out parameter which holds the annealing settings.
 * @param	file		The INI file to parse the parameter from.
 * @return	A numeric string_value, 1 for success, 0 for failure	
 */
short
load_configuration_annealing (
  t_configuration_annealing * configuration,
  char * file
)
{
  char ** allowed_temperature_schedule ;
  char ** allowed_step_schedule ;
  char * string_value ;
  int int_value, int_value1 ;
  dictionary * dictionary;
  if (NULL == (dictionary = iniparser_load (file)))
    {
      fprintf (stderr, "error: couldn\'t load \"%s\"\n", file) ;
      return 0 ;
    }
  allowed_temperature_schedule = configuration_get_allowed_temperature_schedule () ;
  allowed_step_schedule = configuration_get_allowed_step_schedule () ;
  int_value = iniparser_getint (
    dictionary,
    ":duration",
    -1
  ) ;
  if (validate_duration (int_value))
    configuration->duration = int_value ;
  else
    {
      fprintf (stderr, "warning: missing or unexpected duration value in \"%s\"\n", file) ;
      fprintf (stderr, "found: %d\n", int_value) ;
    }
  int_value = iniparser_getint (
    dictionary,
    ":step_count",
    -1
  ) ;
  if (validate_step_count (int_value))
    configuration->step_count = int_value ;
  else
    {
      fprintf (stderr, "warning: missing or unexpected step count value in \"%s\"\n", file) ;
      fprintf (stderr, "found: %d\n", int_value) ;
    }
  string_value = iniparser_getstring (
    dictionary,
    ":step_schedule",
    "@@@"
  ) ;
  if (-1 != (int_value = validate_step_schedule (string_value)))
    configuration->step_schedule = int_value ;
  else
    {
      fprintf (stderr, "warning: missing or unexpected step schedule value in \"%s\"\n", file) ;
      fprintf (stderr, "found: %s\n", string_value) ;
    }
  int_value = iniparser_getint (
    dictionary,
    ":temperature_first",
    -1
  ) ;
  if (-1 != int_value)
    configuration->temperature_first = int_value ;
  else
    {
      fprintf (stderr, "warning: missing or unexpected temperature first value in \"%s\"\n", file) ;
      fprintf (stderr, "found: %d\n", int_value) ;
    }

  int_value1 = iniparser_getint (
    dictionary,
    ":temperature_last",
    -1
  ) ;
  if (-1 != int_value1)
    configuration->temperature_last = int_value1 ;
  else
    {
      fprintf (stderr, "warning: missing or unexpected temperature last value in \"%s\"\n", file) ;
      fprintf (stderr, "found: %d\n", int_value) ;
    }
  if ( ! validate_temperatures (int_value1, int_value))
    {
      fprintf (stderr, "warning: missing or unexpected temperatures values in \"%s\"\n", file) ;
      fprintf (stderr, "found: %d, %d\n", int_value, int_value1) ;
    }
  string_value = iniparser_getstring (
    dictionary,
    ":temperature_schedule",
    "@@@"
  ) ;
   if (-1 != (int_value = validate_temperature_schedule (string_value)))
    configuration->temperature_schedule = int_value ;
  else
    {
      fprintf (stderr, "warning: missing or unexpected temperature schedule value in \"%s\"\n", file) ;
      fprintf (stderr, "found: %s\n", string_value) ;
    }
  return 1 ;
}
