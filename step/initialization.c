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
 * Gives a time repartition with the given schedule type.
 *
 * @param step		Array
 * @param schedule	Step schedule type
 * @param duration	The sum of every step duration
 * @param step_count
 */
void
init_step_schedule (int * step, t_step_schedule schedule, int duration, int step_count)
{
  void (* schedule_function) (int *, int, int) ;
  switch (schedule)
    {
      case STEP_SCHEDULE_EQUAL:
        schedule_function = duration_equal ;
        break ;
      case STEP_SCHEDULE_ASCENDING_1:
        schedule_function = duration_ascending_1 ;
        break ;
      case STEP_SCHEDULE_ASCENDING_2:
        schedule_function = duration_ascending_2 ;
        break ;
      case STEP_SCHEDULE_ASCENDING_3:
        schedule_function = duration_ascending_3 ;
        break ;
      case STEP_SCHEDULE_DESCENDING_1:
        schedule_function = duration_descending_1 ;
        break ;
      case STEP_SCHEDULE_DESCENDING_2:
        schedule_function = duration_descending_2 ;
        break ;
      case STEP_SCHEDULE_DESCENDING_3:
        schedule_function = duration_descending_3 ;
        break ;
      case STEP_SCHEDULE_NORMAL_1:
        schedule_function = duration_normal_1 ;
        break ;
      case STEP_SCHEDULE_NORMAL_2:
        schedule_function = duration_normal_2 ;
        break ;
      case STEP_SCHEDULE_NORMAL_3:
        schedule_function = duration_normal_3 ;
        break ;
    }
  schedule_function (step, duration, step_count) ;
}

/**
 * Gives a temperature repartition with the given schedule type.
 *
 * @param temperature	Array
 * @param step_schedule	Temperature schedule type
 * @param start		Max temperature
 * @param end		Min temperature
 */
void
init_temperature_schedule (
  int * temperature,
  t_temperature_schedule schedule,
  int start,
  int end,
  int step_count
)
{
  void (* schedule_function) (int *, int, int, int) ;
  switch (schedule)
    {
      case TEMPERATURE_SCHEDULE_LINEAR:
        schedule_function = temperature_linear ;
        break ;
      case TEMPERATURE_SCHEDULE_EXPONENTIAL:
        schedule_function = temperature_exponential ;
        break ;
    }
  schedule_function (temperature, start, end, step_count);
}
