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

/**
 * Performs a whole check on the annealing configuration structure informations.
 * @param annealing
 */
short
validate_configuration_annealing (t_configuration_annealing * annealing)
{
  short error = 0 ;
  if ( ! validate_duration (annealing->duration))
    {
      fprintf (
        stderr,
        "error: invalid duration \"%d\"\n",
        annealing->duration
      );
      error = 1 ;
    }
  if ( ! validate_step_count (annealing->step_count))
    {
       fprintf (
        stderr,
        "error: invalid step count \"%d\"\n",
        annealing->step_count
      );
      error = 1 ;
    }
  if ( ! validate_temperatures (annealing->temperature_last, annealing->temperature_first))
    {
      fprintf (
        stderr,
        "error: invalid temperatures \"%d\" \"%d\"\n",
        annealing->temperature_first,
        annealing->temperature_last
      );
      error = 1 ;
    }
  if (STEP_SCHEDULE_UNASSIGNED == annealing->step_schedule)
    {
      fprintf (stderr, "error: missing step schedule\n");
      error = 1 ;
    }
  if (TEMPERATURE_SCHEDULE_UNASSIGNED == annealing->temperature_schedule)
    {
      fprintf (stderr, "error: missing temperature schedule\n");
      error = 1 ;
    }
  return error ? 0 : 1 ;
}

/**
 * Checks if the given input int value is valid for a duration.
 * @param value Given duration
 */
short
validate_duration (int value)
{
  return validate_int (value, INPUT_TEMPERATURE_MIN, INPUT_TEMPERATURE_MAX) ;
}

/**
 * Checks if the given input int value is valid for a step count.
 * @param value Given step count
 */
short
validate_step_count (int value)
{
  return validate_int (value, INPUT_STEP_COUNT_MIN, INPUT_STEP_COUNT_MAX) ;
}

/**
 * Checks if the given temperature is valid
 * @param value Given temperature
 */
short
validate_temperature (int value)
{
  return validate_int (value, INPUT_TEMPERATURE_MIN, INPUT_TEMPERATURE_MAX) ;
}

/**
 * Checks if the given temperature bounds are valid as a range
 * @param value1 Lower bound
 * @param value2 Upper bound
 */
short
validate_temperatures (int value1, int value2)
{
  return validate_temperature (value1) && validate_temperature (value2) && value1 < value2 ;
}

/**
 * Checks if the given input string value is valid for a *STEP* schedule,
 * and returns the scalar value to which it is mapped.
 * The expected values are defined as constants.
 *
 * @param value A string that should match the expected param value (ie. equ no1 as1 de1 ...)
 * @return The t_step_schedule enum value of the given string if valid, -1 otherwise.
 */
short validate_step_schedule (char * value)
{
  return validate_string (
    value,
    configuration_get_allowed_step_schedule ()
  ) ;
}

/**
 * Checks if the given input string value is valid for a *TEMPERATURE* schedule,
 * and returns the scalar value to which it is mapped.
 * The expected values are defined as constants.
 *
 * @param value A string that should match the expected param value (ie. equ li1 ex1 lo1 ...)
 * @return The t_temperature_schedule enum value of the given string if valid, -1 otherwise.
 */
short validate_temperature_schedule (char * value)
{
  return validate_string (
    value,
    configuration_get_allowed_temperature_schedule ()
  ) ;
}


/**
 * Checks if the given input string value is valid for a *AGENT PONDERATION* ,
 * and returns the function value to which it is mapped.
 * The expected values are defined as constants.
 *
 * @param value A string that should match the expected param value (ie. uni cap ...)
 * @return The adress of function if valid, NULL otherwise.
 */
short validate_agent_ponderation (char * value)
{
  return validate_string (
    value,
    configuration_get_allowed_agent_ponderation ()
  ) ;
}


