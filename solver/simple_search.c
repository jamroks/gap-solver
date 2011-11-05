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

void simple_search (
  t_gap_instance * instance,
  t_gap_solution * solution,
  t_gap_solver_registry * registry
)
{
  t_solution_change change ;
  while (TRUE)
    {
      if (
        next_solution_sequential (
          & change,
          instance,
          solution,
          registry,
          TRUE
        )
      )
        {
          solution_apply_change ( instance, solution , & change) ;
        }
      else
        break ;
    }
}
