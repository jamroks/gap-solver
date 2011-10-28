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
 * @return	A numeric value, 1 for success, 0 for failure	
 */
short
load_configuration_annealing (
  t_configuration_annealing * configuration,
  char * file
)
{
  char * temperature_schedule_allowed[INPUT_MAX_STRING_PARAMETER_VALUES] ;
  char * step_schedule_allowed[INPUT_MAX_STRING_PARAMETER_VALUES] ;
  char * value ;
  int count, i ;
  dictionary * dictionary;
  if (NULL == (dictionary = iniparser_load (file)))
    return 0 ;
  configuration_get_allowed_temperature_schedule (
    temperature_schedule_allowed
  ) ;
  configuration_get_allowed_step_schedule (
    step_schedule_allowed
  ) ;
  configuration->duration = iniparser_getint (
    dictionary,
    "duration",
    10
  ) ;
  configuration->step_count = iniparser_getint (
    dictionary,
    "step_count",
    10
  ) ;
  value = iniparser_getstring (
    dictionary,
    "step_schedule",
    "equ"
  ) ;
  count = sizeof (step_schedule_allowed) / sizeof (char *) ;
  configuration->step_schedule = STEP_SCHEDULE_EQUAL ;
  for (i = 0 ; i < count ; i ++)
    if (0 == strcmp (step_schedule_allowed[i], value))
      {
        configuration->step_schedule = i ;
        break ;
      }
  
  configuration->temperature_first = iniparser_getint (
    dictionary,
    "temperature_first",
    90
  ) ;
  configuration->temperature_last = iniparser_getint (
    dictionary,
    "temperature_last",
    10
  ) ;
  value = iniparser_getstring (
    dictionary,
    "temperature_schedule",
    "li1"
  ) ;
  count = sizeof (temperature_schedule_allowed) / sizeof (char *) ;
  configuration->temperature_schedule = TEMPERATURE_SCHEDULE_LINEAR_1 ;
  for (i = 0 ; i < count ; i ++)
    if (0 == strcmp (temperature_schedule_allowed[i], value))
      {
        configuration->temperature_schedule = i ;
        break ;
      }
  return 1 ;
}
