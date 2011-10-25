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
load_configuration_annealing (
  t_configuration_annealing * configuration,
  char * file
)
{
  dictionary * dictionary = iniparser_load (file);
  configuration->duration = iniparser_getint (
    dictionary,
    "duration",
    10
  ) ;
  configuration->step_count = iniparser_getint (
    dictionary,
    "step_count",
    10
  ) ;
  configuration->step_max_duration = iniparser_getint (
    dictionary,
    "step_max_duration",
    10
  ) ;
  configuration->step_repartition ;
  configuration->temperature_max = iniparser_getint (
    dictionary,
    "temperature_max",
    10
  ) ;
  configuration->temperature_min = iniparser_getint (
    dictionary,
    "temperature_min",
    10
  ) ;
  configuration->temperature_decrease ;
  configuration->problem_type ;
  configuration->neighbourhood_exploration ;
}
