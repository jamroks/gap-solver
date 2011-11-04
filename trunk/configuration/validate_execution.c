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
 *
 * @param annealing
 */
short
validate_configuration_execution (t_configuration_execution * execution)
{
  short error = 0 ;
  if ( ! validate_file (execution->input_file))
    {
      if (execution->input_file)
        fprintf (stderr, "error opening: \"%s\"\n", execution->input_file) ;
      error = 1 ;
    }
  if (UNASSIGNED == execution->problem_type)
    {
      fprintf (
        stderr,
        "error: problem type \"%d\"\n",
        execution->problem_type
      );
      error = 1 ;
    }
  if (NEIGHBOURHOOD_EXPLORATION_UNASSIGNED == execution->neighbourhood_exploration)
    {
       fprintf (
        stderr,
        "error: invalid neighbourhood exploration \"%d\"\n",
        execution->neighbourhood_exploration
      );
      error = 1 ;
    }
  return error ? 0 : 1 ;
}

/**
 * Checks if the given input string value is valid for a problem type,
 * and returns the scalar value to which it is mapped.
 * The expected values are defined as constants.
 *
 * @param value A string that should match the expected param value (ie. equ li1 ex1 lo1 ...)
 *
 * @return The t_problem_type enum value of the given string if correct, -1 otherwise.
 *
 */
short
validate_problem_type (char * value)
{
  return validate_string (
    value,
    configuration_get_allowed_problem_type ()
  ) ;
}

/**
 * Checks if the given input string value is valid for a neighbourhood exploration,
 * and returns the scalar value to which it is mapped.
 * The expected values are defined as constants.
 *
 * @param value A string that should match the expected param value (ie. equ no1 as1 de1 ...)
 *
 * @return The t_neighbourhood_exploration enum value of the given string if correct, -1 otherwise.
 */
short
validate_neighbourhood_exploration (char * value)
{
  return validate_string (
    value,
    configuration_get_allowed_neighbourhood_exploration ()
  ) ;
}
