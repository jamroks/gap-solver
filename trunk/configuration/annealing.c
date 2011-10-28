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

static void _init_temperature_schedule_allowed (char **) ;

static void _init_step_schedule_allowed (char **) ;

/*
 * Parse the simulated annealing parameter file, expected in INI format.
 * The parameters control the annealing process.
 * They define the temperature schedule and the step schedule,
 * which are later computed from them.
 *
 * @param	configuration	An in/out argument which holds the annealing parameters.
 * @param	file		The INI file to parse the parameter from.
 * @return	A numeric value, 1 for success, 0 for failure	
 */
short
load_configuration_annealing (
  t_configuration_annealing * configuration,
  char * file
)
{
  dictionary * dictionary = iniparser_load (file);
  char * temperature_schedule_allowed[INI_MAX_STRING_PARAMETER_VALUES] ;
  _init_temperature_schedule_allowed (
    temperature_schedule_allowed
  ) ;
  char * step_schedule_allowed[INI_MAX_STRING_PARAMETER_VALUES] ;
  _init_step_schedule_allowed (
    step_schedule_allowed
  ) ;
  char * value ;
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
  configuration->step_repartition ;
  configuration->temperature_first = iniparser_getint (
    dictionary,
    "temperature_first",
    10
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
  int count, i;
  count = sizeof (temperature_schedule_allowed) / sizeof (char *) ;
  for (i = 0 ; i < count ; i ++)
    if (0 == strcmp (temperature_schedule_allowed[i], value))
      break ;
  configuration->temperature_schedule ;
//  configuration->problem_type ;
//  configuration->neighbourhood_exploration ;
}

static void _init_temperature_schedule_allowed (char * allowed[INI_MAX_STRING_PARAMETER_VALUES])
{
  allowed[TEMPERATURE_SCHEDULE_LOGARITHMIC_1] =
    INI_TEMPERATURE_SCHEDULE_LOGARITHMIC_1 ;
  allowed[TEMPERATURE_SCHEDULE_LOGARITHMIC_2] =
    INI_TEMPERATURE_SCHEDULE_LOGARITHMIC_2 ;
  allowed[TEMPERATURE_SCHEDULE_LOGARITHMIC_3] =
    INI_TEMPERATURE_SCHEDULE_LOGARITHMIC_3 ;
  allowed[TEMPERATURE_SCHEDULE_LINEAR_1] =
    INI_TEMPERATURE_SCHEDULE_LINEAR_1 ;
  allowed[TEMPERATURE_SCHEDULE_LINEAR_2] =
    INI_TEMPERATURE_SCHEDULE_LINEAR_2 ;
  allowed[TEMPERATURE_SCHEDULE_LINEAR_3] =
    INI_TEMPERATURE_SCHEDULE_LINEAR_3 ;
  allowed[TEMPERATURE_SCHEDULE_EXPONENTIAL_1] =
    INI_TEMPERATURE_SCHEDULE_EXPONENTIAL_1 ;
  allowed[TEMPERATURE_SCHEDULE_EXPONENTIAL_2] =
    INI_TEMPERATURE_SCHEDULE_EXPONENTIAL_2 ;
  allowed[TEMPERATURE_SCHEDULE_EXPONENTIAL_3] =
    INI_TEMPERATURE_SCHEDULE_EXPONENTIAL_3 ;
  allowed[TEMPERATURE_SCHEDULE_EQUAL] =
    INI_TEMPERATURE_SCHEDULE_EQUAL ;
}

static void _init_step_schedule_allowed (char * allowed[INI_MAX_STRING_PARAMETER_VALUES])
{
  allowed[STEP_SCHEDULE_EQUAL] =
    INI_STEP_SCHEDULE_EQUAL ;
  allowed[STEP_SCHEDULE_ASCENDING_1] =
    INI_STEP_SCHEDULE_ASCENDING_1 ;
  allowed[STEP_SCHEDULE_ASCENDING_2] =
    INI_STEP_SCHEDULE_ASCENDING_2 ;
  allowed[STEP_SCHEDULE_ASCENDING_3] =
    INI_STEP_SCHEDULE_ASCENDING_3 ;
  allowed[STEP_SCHEDULE_DESCENDING_1] =
    INI_STEP_SCHEDULE_DESCENDING_1 ;
  allowed[STEP_SCHEDULE_DESCENDING_2] = 
    INI_STEP_SCHEDULE_DESCENDING_2 ;
  allowed[STEP_SCHEDULE_DESCENDING_3] =
    INI_STEP_SCHEDULE_DESCENDING_3 ;
  allowed[STEP_SCHEDULE_NORMAL_1] =
    INI_STEP_SCHEDULE_NORMAL_1 ;
  allowed[STEP_SCHEDULE_NORMAL_2] =
    INI_STEP_SCHEDULE_NORMAL_2 ;
  allowed[STEP_SCHEDULE_NORMAL_3] =
    INI_STEP_SCHEDULE_NORMAL_3 ;
}
