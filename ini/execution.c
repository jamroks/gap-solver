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
 * @return	A numeric value, 1 for success, 0 for failure	
 */
short
load_configuration_execution (
  t_configuration_execution * configuration,
  char * file
)
{
  char * problem_type_allowed[INPUT_MAX_STRING_PARAMETER_VALUES] ;
  char * neighbourhood_exploration_allowed[INPUT_MAX_STRING_PARAMETER_VALUES] ;
  char * value ;
  int count, i ;
  dictionary * dictionary;
  if (NULL == (dictionary = iniparser_load (file)))
    return 0 ;
  configuration_get_allowed_neighbourhood_exploration (
    neighbourhood_exploration_allowed
  ) ;
  configuration_get_allowed_problem_type (
    problem_type_allowed
  ) ;
  value = iniparser_getstring (
    dictionary,
    "problem_type",
    "max"
  ) ;
  count = sizeof (problem_type_allowed) / sizeof (char *) ;
  configuration->problem_type = MAXIMIZATION ;
  for (i = 0 ; i < count ; i ++)
    if (0 == strcmp (problem_type_allowed[i], value))
      {
        configuration->problem_type = i ;
        break ;
      }

  value = iniparser_getstring (
    dictionary,
    "neighbourhood_exploration",
    "sto"
  ) ;
  count = sizeof (neighbourhood_exploration_allowed) / sizeof (char *) ;
  configuration->neighbourhood_exploration = NEIGHBOURHOOD_EXPLORATION_STOCHASTIC;
  for (i = 0 ; i < count ; i ++)
    if (0 == strcmp (neighbourhood_exploration_allowed[i], value))
      {
        configuration->neighbourhood_exploration = i ;
        break ;
      }
  return 1 ;
}
