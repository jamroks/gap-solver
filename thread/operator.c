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

void *
thread_operator (void * arg)
{
  int step ;
  t_gap_solver_registry * registry = (t_gap_solver_registry *) arg ;
  for (
    ; registry->step_current < registry->step_count
    ; registry->step_current ++
  )
    {
      if (registry->verbose)
        printf (
          "entering step %d out of %d, temperature: %d, duration: %d\n",
          registry->step_current + 1,
          registry->step_count,
          registry->step_temperature[registry->step_current],
          registry->step_duration[registry->step_current]
        ) ;
      sleep (registry->step_duration[registry->step_current]) ;
      registry->step_timeout = TRUE ;
    }
  registry->timeout = TRUE ;
}
