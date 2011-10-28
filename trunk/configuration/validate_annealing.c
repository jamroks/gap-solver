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
 * Checks if the given input int value is valid for a duration.
 * @param value Given duration
 */
short validate_duration (int value)
{
  return validate_int (value, INPUT_TEMPERATURE_MIN, INPUT_TEMPERATURE_MAX) ;
}

/**
 * Checks if the given input int value is valid for a step count.
 * @param value Given step count
 */
short validate_step_count (int value)
{
  return validate_int (value, INPUT_STEP_COUNT_MIN, INPUT_STEP_COUNT_MAX) ;
}

/**
 * Checks if the given temperature bounds are valid as a range
 * @param value1 Lower bound
 * @param value2 Upper bound
 */
short validate_temperatures (int value1, int value2)
{
  return validate_int (value1, INPUT_TEMPERATURE_MIN, INPUT_TEMPERATURE_MAX) 
  && validate_int (value2, INPUT_TEMPERATURE_MIN, INPUT_TEMPERATURE_MAX)
  && value1 < value2 ;
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
