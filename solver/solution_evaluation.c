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

short 
solution_evaluation (int new_value, int old_value, t_problem_type type, float temperature)
{
  int delta = new_value - old_value ;
  if (type == MAXIMIZATION)
    delta *= -1;
  if (delta <= 0)
    return 1 ;
  if ((float) random () / (float) RAND_MAX < pow (M_E, - (delta / temperature)))
    return 1 ;
  return 0;
}
