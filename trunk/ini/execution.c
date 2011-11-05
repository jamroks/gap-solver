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
 * Parse the execution parameter file, expected in INI format.
 * The parameters control some of the execution process.
 *
 * @param	configuration	An in/out parameter which holds the execution settings.
 * @param	file		The INI file to parse the parameter from.
 * @return	1 for success, 0 for failure	
 */
short
load_configuration_execution (
  t_configuration_execution * configuration,
  char * file
)
{

  char * string_value ;
  int int_value ;
  dictionary * dictionary;
  if (NULL == (dictionary = iniparser_load (file)))
    {
      fprintf (stderr, "error: couldn\'t load \"%s\"\n", file) ;
      return 0 ;
    }
  int_value = iniparser_getint (
    dictionary,
    ":full_result",
    -1
  ) ;
  if (-1 != int_value)
    configuration->full_result = int_value ;
  int_value = iniparser_getint (
    dictionary,
    ":simple_search",
    -1
  ) ;
  if (-1 != int_value)
    configuration->simple_search = int_value ;
  string_value = iniparser_getstring (
    dictionary,
    ":problem_type",
    "@@@"
  ) ;
  if (-1 != (int_value = validate_problem_type (string_value)))
    configuration->problem_type = int_value ;
  else
    {
      fprintf (stderr, "warning: missing or unexpected problem type value in \"%s\"\n", file) ;
      fprintf (stderr, "found: %s\n", string_value) ;
    }
  string_value = iniparser_getstring (
    dictionary,
    ":neighbourhood_exploration",
    "@@@"
  ) ;
  if (-1 != (int_value = validate_neighbourhood_exploration (string_value)))
    configuration->neighbourhood_exploration = int_value ;
  else
    {
      fprintf (stderr, "warning: missing or unexpected neighbourhood exploration value in \"%s\"\n", file) ;
      fprintf (stderr, "found: %s\n", string_value) ;
    }
  int_value = iniparser_getint (
    dictionary,
    ":neighbourhood_swap",
    -1
  ) ;
  if (-1 != int_value)
    configuration->neighbourhood_swap = int_value ;
  else
    {
      fprintf (stderr, "warning: missing or unexpected neighbourhood swap value in \"%s\"\n", file) ;
      fprintf (stderr, "found: %d\n", int_value) ;
    }
  int_value = iniparser_getint (
    dictionary,
    ":neighbourhood_multi_swap",
    -1
  ) ;
  if (-1 != int_value)
    configuration->neighbourhood_multi_swap = int_value ;
  int_value = iniparser_getint (
    dictionary,
    ":neighbourhood_multi_swap_max_iteration",
    -1
  ) ;
  if (-1 != int_value)
    configuration->neighbourhood_multi_swap_max_iteration = int_value ;
  int_value = iniparser_getint (
    dictionary,
    ":neighbourhood_full_swap",
    -1
  ) ;
  if (-1 != int_value)
    configuration->neighbourhood_full_swap = int_value ;
  else
    {
      fprintf (stderr, "warning: missing or unexpected neighbourhood full swap value in \"%s\"\n", file) ;
      fprintf (stderr, "found: %d\n", int_value) ;
    }
  int_value = iniparser_getint (
    dictionary,
    ":neighbourhood_transfer",
    -1
  ) ;
  if (-1 != int_value)
    configuration->neighbourhood_transfer = int_value ;
  else
    {
      fprintf (stderr, "warning: missing or unexpected neighbourhood transfer value in \"%s\"\n", file) ;
      fprintf (stderr, "found: %d\n", int_value) ;
    }
  return 1 ;
}
