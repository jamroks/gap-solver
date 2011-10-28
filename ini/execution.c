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
  char ** allowed_problem_type ;
  char ** allowed_neighbourhood_exploration ;
  char * value ;
  int value ;
  dictionary * dictionary;
  if (NULL == (dictionary = iniparser_load (file)))
    return 0 ;
  allowed_problem_type = configuration_get_allowed_problem_type () ;
  allowed_neighbourhood_exploration = configuration_get_allowed_neighbourhood_exploration () ;
  value = iniparser_getstring (
    dictionary,
    "problem_type",
    "@@@"
  ) ;
  count = sizeof (allowed_problem_type) / sizeof (char *) ;
  configuration->problem_type = MAXIMIZATION ;
  for (i = 0 ; i < count ; i ++)
    if (0 == strcmp (allowed_problem_type[i], value))
      {
        configuration->problem_type = i ;
        break ;
      }

  value = iniparser_getstring (
    dictionary,
    "neighbourhood_exploration",
    "@@@"
  ) ;
  count = sizeof (allowed_neighbourhood_exploration) / sizeof (char *) ;
  configuration->neighbourhood_exploration = NEIGHBOURHOOD_EXPLORATION_STOCHASTIC;
  for (i = 0 ; i < count ; i ++)
    if (0 == strcmp (allowed_neighbourhood_exploration[i], value))
      {
        configuration->neighbourhood_exploration = i ;
        break ;
      }
  return 1 ;
}
