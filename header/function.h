#include "../header/common.h"

#ifndef FUNCTION_H
  #define FUNCTION_H

short 
print_results (t_gap_instance *gap_i,t_gap_solution *gap_r) ;

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


// <[Start]> Memory allocation

short
memory_allocation_gap_instance (t_gap_instance *, int, int) ;

short
memory_allocation_gap_solution (t_gap_solution *, int, int) ;

short 
memory_free_gap_instance (t_gap_instance *) ;

short
memory_free_gap_solution (t_gap_solution *) ;

// <[End]> Memory allocation


// <[Start]> Input file 

short 
read_orlibrary_input_file (char *, t_gap_instance *, t_gap_solution *) ;

// <[End]> Input file 


// <[Start]> CLI

short
parse_cli_arguments (int, char **, t_gap_solver_context *);

// <[End]> CLI

# endif;

