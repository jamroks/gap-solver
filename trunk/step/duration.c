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

static short _duration_normal (int * step_duration, int duration, int step_count, float ratio) ;

static short _duration_geometric (int * step_duration, int duration, int step_count, float ratio) ;

static void _populate_duration_geometric_progression (
  int * step_duration,
  int duration,
  int step_count,
  float ratio
) ;

/**
 * The following functions have an in/out array parameter,
 * which holds every step duration for the given step count.
 */

/**
 * Gives a time repartition with equal step.
 */
short
duration_equal (int * step_duration, int duration, int step_count)
{
  int reminder, step_size, i ;
  reminder = duration % step_count ;
  step_size = duration / step_count ;
  for (i = 0 ; i < step_count ; i++)
    {
      step_duration[i] = step_size ;
      if (reminder > 0)
        {
          step_duration[i] ++ ;
          reminder -- ;
        }
    }
  return 1 ;
}

/**
 * Gives a time repartition with slowly ascending step duration.
 * Its values belongs to a geometric progression which sums to the given duration argument.
 * The common ratio is 1.3.
 *
 * @param step_duration	The pointed memory area will be allocated. 
 * @param duration	The sum of every step duration
 * @param step_count
 */
short
duration_ascending_1 (int * step_duration, int duration, int step_count)
{
  return _duration_geometric (
    step_duration,
    duration,
    step_count,
    STEP_REPARTITION_ASCENDING_1_COMMON_RATIO
  ) ; 
}

/**
 * Gives a time repartition with medium ascending step duration.
 * Its values belongs to a geometric progression which sums to the given duration argument.
 * The common ratio is 1.6.
 *
 * @param step_duration	The pointed memory area will be allocated. 
 * @param duration	The sum of every step duration
 * @param step_count
 */
short
duration_ascending_2 (int * step_duration, int duration, int step_count)
{
  return _duration_geometric (
    step_duration,
    duration,
    step_count,
    STEP_REPARTITION_ASCENDING_2_COMMON_RATIO
  ) ; 
}

/**
 * Gives a time repartition with fast ascending step duration.
 * Its values belongs to a geometric progression which sums to the given duration argument.
 * The common ratio is 1.9.
 *
 * @param step_duration	The pointed memory area will be allocated. 
 * @param duration	The sum of every step duration
 * @param step_count
 */
short
duration_ascending_3 (int * step_duration, int duration, int step_count)
{
  return _duration_geometric (
    step_duration,
    duration,
    step_count,
    STEP_REPARTITION_DESCENDING_3_COMMON_RATIO
  ) ; 
}

/**
 * Gives a time repartition with slow descending step duration.
 * Its values belongs to a geometric progression which sums to the given duration argument.
 * The common ratio is 0.7.
 *
 * @param step_duration	The pointed memory area will be allocated. 
 * @param duration	The sum of every step duration
 * @param step_count
 */
short
duration_descending_1 (int * step_duration, int duration, int step_count)
{
  return _duration_geometric (
    step_duration,
    duration,
    step_count,
    STEP_REPARTITION_DESCENDING_1_COMMON_RATIO
  ) ; 
}

/**
 * Gives a time repartition with medium descending step duration.
 * Its values belongs to a geometric progression which sums to the given duration argument.
 * The common ratio is 0.4.
 *
 * @param step_duration	The pointed memory area will be allocated. 
 * @param duration	The sum of every step duration
 * @param step_count
 */
short
duration_descending_2 (int * step_duration, int duration, int step_count)
{
  return _duration_geometric (
    step_duration,
    duration,
    step_count,
    STEP_REPARTITION_DESCENDING_2_COMMON_RATIO
  ) ; 
}

/**
 * Gives a time repartition with fast descending step duration.
 * Its values belongs to a geometric progression which sums to the given duration argument.
 * The common ratio is 0.2.
 *
 * @param step_duration	The pointed memory area will be allocated. 
 * @param duration	The sum of every step duration
 * @param step_count
 */
short
duration_descending_3 (int * step_duration, int duration, int step_count)
{
  return _duration_geometric (
    step_duration,
    duration,
    step_count,
    STEP_REPARTITION_DESCENDING_3_COMMON_RATIO
  ) ; 
}

/**
 * Gives a time repartition with a pseudo normal distribution.
 * Low slope.
 *
 * @param step_duration	The pointed memory area will be allocated. 
 * @param duration	The sum of every step duration
 * @param step_count
 */
short
duration_normal_1 (int * step_duration, int duration, int step_count)
{
  return _duration_normal (
    step_duration,
    duration,
    step_count,
    STEP_REPARTITION_ASCENDING_1_COMMON_RATIO
  ) ;
}

/**
 * Gives a time repartition with a pseudo normal distribution.
 * Medium slope.
 *
 * @param step_duration	The pointed memory area will be allocated. 
 * @param duration	The sum of every step duration
 * @param step_count
 */
short
duration_normal_2 (int * step_duration, int duration, int step_count)
{
  return _duration_normal (
    step_duration,
    duration,
    step_count,
    STEP_REPARTITION_ASCENDING_2_COMMON_RATIO
  ) ;
}

/**
 * Gives a time repartition with a pseudo normal distribution.
 * High slope.
 *
 * @param step_duration	The pointed memory area will be allocated. 
 * @param duration	The sum of every step duration
 * @param step_count
 */
short
duration_normal_3 (int * step_duration, int duration, int step_count)
{
  return _duration_normal (
    step_duration,
    duration,
    step_count,
    STEP_REPARTITION_ASCENDING_3_COMMON_RATIO
  ) ;
}

static short
_duration_normal (int * step_duration, int duration, int step_count, float ratio)
{
  int i, interval, half_step_count, difference ;
  double half_duration ;
  interval = duration & 1 ? 2 : 1 ;
  half_step_count = step_count & 1 ? (step_count / 2 + 1) : step_count / 2 ; 
  half_duration = (double) half_step_count / (double) step_count * (double) duration ;
  _populate_duration_geometric_progression (
    step_duration,
    (int) ceil (half_duration),
    half_step_count,
    ratio
  ) ;
  difference = step_count - half_step_count ;
  for (i = 0 ; i < (step_count - half_step_count) ; i ++)
    step_duration[half_step_count + i] = step_duration[half_step_count - i - interval] ;
  return 1;
}

static short
_duration_geometric (int * step_duration, int duration, int step_count, float ratio)
{
  _populate_duration_geometric_progression (
    step_duration,
    duration,
    step_count,
    ratio
  ) ;
  return 1 ;
}

static void
_populate_duration_geometric_progression (
  int * step_duration,
  int duration,
  int step_count,
  float ratio
)
{ 
  double first_duration, temp ;
  int i ;
  first_duration = ((double) duration) * (1.0 - ratio) / (1.0 - pow ((double) ratio, (double) step_count)) ;
  step_duration[0] = (int) ceil (first_duration) ;
  for (i = 1 ; i < step_count ; i++) 
    {
      temp = first_duration * pow ((double) ratio, (double) i) ;
      step_duration[i] = (int) ((i & 1) ? ceil(temp) : ceil(temp)) ;
    }
}
