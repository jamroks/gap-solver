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
 * Gives a temperature schedule with exponential temperature decrease.
 *
 * @param schedule_temperature	Array
 * @param temperature	The sum of every step temperature
 * @param step_count
 */
void
temperature_exponential (
  int * schedule_temperature,
  int temperature_start,
  int temperature_end,
  int step_count
)
{
  int i ;
  double ratio ;
  ratio = pow (
    (double) temperature_end / (double) temperature_start ,
    1.0 / (double) (step_count - 1)
  ) ;
  for (i = 0 ; i < step_count ; i ++)
    schedule_temperature[i] = (int) (temperature_start * (pow (ratio, (double) i))) ;
}


/**
 * Gives a temperature schedule with linear temperature decrease.
 *
 * @param schedule_temperature	Array
 * @param temperature	The sum of every step temperature
 * @param step_count
 */
void
temperature_linear (
  int * schedule_temperature,
  int temperature_start,
  int temperature_end,
  int step_count
)
{
  int total, difference, average, remainder, i ;
  total = temperature_start - temperature_end ;
  difference = total / (step_count - 1) ;
  remainder = total % (step_count - 1) ;
  schedule_temperature[0] = temperature_start ;
  for (i = 1 ; i < step_count ; i ++)
    {
      schedule_temperature[i] = schedule_temperature[i - 1] - difference ;
      if (remainder > 0)
        {
          schedule_temperature[i] -- ;
          remainder -- ;
        }
    }
}
