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
 * Return an array holding allowed values for the problem type string parameter.
 * This array is indexed by enum values, and contains char array pointers.
 * The pointed string are the expected values.
 */
char ** configuration_get_allowed_problem_type ()
{
  static int initialized = 0 ;
  static char * allowed[INPUT_MAX_STRING_PARAMETER_VALUES] ;
  if (0 == initialized)
    {
      allowed[MAXIMIZATION] = INPUT_MAXIMIZATION ;
      allowed[MINIMIZATION] = INPUT_MINIMIZATION ;
    }
  initialized = 1 ;
  return allowed ;
}

/**
 * Return an array holding allowed values for the neighbourhood exploration string parameter.
 * This array is indexed by enum values, and contains char array pointers.
 * The pointed string are the expected values.
 */
char ** configuration_get_allowed_neighbourhood_exploration ()
{
 static int initialized = 0 ;
 static char * allowed[INPUT_MAX_STRING_PARAMETER_VALUES] ;
  if (0 == initialized)
    {
      allowed[NEIGHBOURHOOD_EXPLORATION_DETERMINIST] =
        INPUT_NEIGHBOURHOOD_EXPLORATION_DETERMINIST ;
      allowed[NEIGHBOURHOOD_EXPLORATION_STOCHASTIC] =
        INPUT_NEIGHBOURHOOD_EXPLORATION_STOCHASTIC ;
    }
  initialized = 1 ;
  return allowed ;
}
