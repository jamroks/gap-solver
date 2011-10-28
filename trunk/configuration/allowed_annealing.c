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
 * Return an array holding allowed values for the *TEMPERATURE* schedule string parameter.
 * This array is indexed by enum values, and contains char array pointers.
 * The pointed string are the expected values.
 */
char ** configuration_get_allowed_temperature_schedule ()
{
  static int initialized = 0 ;
  static char * allowed[INPUT_MAX_STRING_PARAMETER_VALUES] ;
  if (0 == initialized)
    {
      for ( ; initialized < INPUT_MAX_STRING_PARAMETER_VALUES; initialized ++)
        allowed[initialized] = NULL;
      allowed[TEMPERATURE_SCHEDULE_LOGARITHMIC_1] =
        INPUT_TEMPERATURE_SCHEDULE_LOGARITHMIC_1 ;
      allowed[TEMPERATURE_SCHEDULE_LOGARITHMIC_2] =
        INPUT_TEMPERATURE_SCHEDULE_LOGARITHMIC_2 ;
      allowed[TEMPERATURE_SCHEDULE_LOGARITHMIC_3] =
        INPUT_TEMPERATURE_SCHEDULE_LOGARITHMIC_3 ;
      allowed[TEMPERATURE_SCHEDULE_LINEAR_1] =
        INPUT_TEMPERATURE_SCHEDULE_LINEAR_1 ;
      allowed[TEMPERATURE_SCHEDULE_LINEAR_2] =
        INPUT_TEMPERATURE_SCHEDULE_LINEAR_2 ;
      allowed[TEMPERATURE_SCHEDULE_LINEAR_3] =
        INPUT_TEMPERATURE_SCHEDULE_LINEAR_3 ;
      allowed[TEMPERATURE_SCHEDULE_EXPONENTIAL_1] =
        INPUT_TEMPERATURE_SCHEDULE_EXPONENTIAL_1 ;
      allowed[TEMPERATURE_SCHEDULE_EXPONENTIAL_2] =
        INPUT_TEMPERATURE_SCHEDULE_EXPONENTIAL_2 ;
      allowed[TEMPERATURE_SCHEDULE_EXPONENTIAL_3] =
        INPUT_TEMPERATURE_SCHEDULE_EXPONENTIAL_3 ;
      allowed[TEMPERATURE_SCHEDULE_EQUAL] =
        INPUT_TEMPERATURE_SCHEDULE_EQUAL ;
    }
  return allowed ;
}

/**
 * Return an array holding allowed values for the *STEP* schedule string parameter.
 * This array is indexed by enum values, and contains char array pointers.
 * The pointed string are the expected values.
 */
char ** configuration_get_allowed_step_schedule ()
{
  static int initialized = 0 ;
  static char * allowed[INPUT_MAX_STRING_PARAMETER_VALUES] ;
  if (0 == initialized)
    {
      for ( ; initialized < INPUT_MAX_STRING_PARAMETER_VALUES; initialized ++)
        allowed[initialized] = NULL;
      allowed[STEP_SCHEDULE_EQUAL] =
        INPUT_STEP_SCHEDULE_EQUAL ;
      allowed[STEP_SCHEDULE_ASCENDING_1] =
        INPUT_STEP_SCHEDULE_ASCENDING_1 ;
      allowed[STEP_SCHEDULE_ASCENDING_2] =
        INPUT_STEP_SCHEDULE_ASCENDING_2 ;
      allowed[STEP_SCHEDULE_ASCENDING_3] =
        INPUT_STEP_SCHEDULE_ASCENDING_3 ;
      allowed[STEP_SCHEDULE_DESCENDING_1] =
        INPUT_STEP_SCHEDULE_DESCENDING_1 ;
      allowed[STEP_SCHEDULE_DESCENDING_2] = 
        INPUT_STEP_SCHEDULE_DESCENDING_2 ;
      allowed[STEP_SCHEDULE_DESCENDING_3] =
        INPUT_STEP_SCHEDULE_DESCENDING_3 ;
      allowed[STEP_SCHEDULE_NORMAL_1] =
        INPUT_STEP_SCHEDULE_NORMAL_1 ;
      allowed[STEP_SCHEDULE_NORMAL_2] =
        INPUT_STEP_SCHEDULE_NORMAL_2 ;
      allowed[STEP_SCHEDULE_NORMAL_3] =
        INPUT_STEP_SCHEDULE_NORMAL_3 ;
  }
  return allowed ;
}
