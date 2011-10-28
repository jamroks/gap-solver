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
 * Return the position of the searched string in the allowed array,
 * -1 if it is not present.
 * @param string Searched string
 * @param string Allowed strings
 */
short validate_string (char * string, char ** allowed)
{
  int i ;
  for (i = 0 ; allowed[i] && i < INPUT_MAX_STRING_PARAMETER_VALUES ; i ++)
    if (0 == strncmp (string, allowed[i], INPUT_STRING_PARAMETER_LENGTH))
      return i ;
  return -1 ;
}

/**
 * Return 1 if the given int is in the given range,
 * 0 otherwise
 * @param min Range start inclusive
 * @param max Range end inclusive
 */
short validate_int (int value, int min, int max)
{
  return value >= min && value <= max ;
}
