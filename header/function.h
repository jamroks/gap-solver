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

#ifndef FUNCTION_H

#define FUNCTION_H
#include "../header/common.h"

short 
neighbourhood (t_gap_instance *gap_inst, t_gap_solution *gap_cur, t_gap_solution *gap_next, 
                t_method method, void (*f_evaluation)() , t_elt (*f_take_choice)());

t_list 
list_of_agents (void (*f_evaluation)());

t_list
subtract_value_from_list (t_list, t_elt elt) ;

t_list
list_of_jobs_agt (t_agent agt_1, t_agent agt_2) ;

void 
unavailable (t_error err) ;

// <[Start]> Solution 0

short
search_solution_0 (t_gap_instance *, t_gap_solution *);

// <[End]> Solution 0


// <[Start]> Memory allocation

short
alloc_gap_instance (t_gap_instance *, int, int) ;

short
alloc_gap_solution (t_gap_solution *, int, int) ;

short 
free_gap_instance (t_gap_instance *) ;

short
free_gap_solution (t_gap_solution *) ;

// <[End]> Memory allocation


// <[Start]> Input file 

short 
read_orlibrary_input_file (char *, t_gap_instance *, t_gap_solution *) ;

// <[End]> Input file 


// <[Start]> CLI

short
parse_cli_arguments (t_gap_solver_registry *, int, char **) ;

short 
print_result (t_gap_instance *,t_gap_solution *) ;

// <[End]> CLI

#endif
