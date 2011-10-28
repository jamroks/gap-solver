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
  char * temperature_schedule_possible_value[] =
  {
    ANNEALING_CONFIGURATION_TEMPERATURE_SCHEDULE_EQUAL,
    ANNEALING_CONFIGURATION_TEMPERATURE_SCHEDULE_LINEAR_1,
    ANNEALING_CONFIGURATION_TEMPERATURE_SCHEDULE_LINEAR_2,
    ANNEALING_CONFIGURATION_TEMPERATURE_SCHEDULE_LINEAR_3,
    ANNEALING_CONFIGURATION_TEMPERATURE_SCHEDULE_LOGARITHMIC_1,
    ANNEALING_CONFIGURATION_TEMPERATURE_SCHEDULE_LOGARITHMIC_2,
    ANNEALING_CONFIGURATION_TEMPERATURE_SCHEDULE_LOGARITHMIC_3,
    ANNEALING_CONFIGURATION_TEMPERATURE_SCHEDULE_EXPONENTIAL_1,
    ANNEALING_CONFIGURATION_TEMPERATURE_SCHEDULE_EXPONENTIAL_2,
    ANNEALING_CONFIGURATION_TEMPERATURE_SCHEDULE_EXPONENTIAL_3
  };
  char * step_schedule_possible_value[] =
  {
    ANNEALING_CONFIGURATION_STEP_SCHEDULE_EQUAL,
    ANNEALING_CONFIGURATION_STEP_SCHEDULE_ASCENDING_1,
    ANNEALING_CONFIGURATION_STEP_SCHEDULE_ASCENDING_2,
    ANNEALING_CONFIGURATION_STEP_SCHEDULE_ASCENDING_3,
    ANNEALING_CONFIGURATION_STEP_SCHEDULE_DESCENDING_1,
    ANNEALING_CONFIGURATION_STEP_SCHEDULE_DESCENDING_2,
    ANNEALING_CONFIGURATION_STEP_SCHEDULE_DESCENDING_3,
    ANNEALING_CONFIGURATION_STEP_SCHEDULE_NORMAL_1,
    ANNEALING_CONFIGURATION_STEP_SCHEDULE_NORMAL_2,
    ANNEALING_CONFIGURATION_STEP_SCHEDULE_NORMAL_3
  };
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
  configuration->step_max_duration = iniparser_getint (
    dictionary,
    "step_max_duration",
    10
  ) ;
  configuration->step_repartition ;
  configuration->temperature_max = iniparser_getint (
    dictionary,
    "temperature_max",
    10
  ) ;
  configuration->temperature_min = iniparser_getint (
    dictionary,
    "temperature_min",
    10
  ) ;
  configuration->temperature_schedule = iniparser_getstring (
    dictionary,
    "temperature_schedule",
    "lin1"
  ) ;
  configuration->temperature_schedule ;
  configuration->problem_type ;
  configuration->neighbourhood_exploration ;
}
