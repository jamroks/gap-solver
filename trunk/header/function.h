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

t_list 
list_of_agents (t_gap_instance *gap_inst);

void
subtract_elt_from_list (t_list *, t_elt elt) ;

t_list
list_of_jobs_agt (t_gap_instance *, t_gap_solution *, t_agent , t_agent ) ;

t_list
list_of_jobs_swap0 (t_gap_instance *, t_gap_solution *, t_agent , t_agent ) ;

t_list
list_of_jobs_swap (t_gap_instance *, t_gap_solution *, t_agent , t_agent , t_job ) ;

t_elt
take_choice(t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, 
            t_list *, int (*ponderate)()) ;
// ponderate est une fonction de ponderation des éléments évalués; de profil :

// <[Start]> fonctions de ponderation
// ponderate(t_gap_instance inst, t_gap_solution sol, equity_gap_solver_registry reg, t_elt elt)

int 
equity(t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, t_elt ) ;

int 
capacity_left(t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, t_elt ) ;

int 
capacity(t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, t_elt ) ;

// <[End]> fonctions de ponderation

void 
unavailable (t_error ) ;

short
solution_evaluation (int, int, t_problem_type, float);

// <[Start]> stochastic neighbourhood

short
stochastic_next_solution (t_gap_solution *, t_gap_instance *, t_gap_solution *, t_gap_solver_registry *) ;

// <[End]> stochastic neighbourhood


// <[Start]> Determinist neighbourhood

short
determinist_next_solution (t_gap_solution *, t_gap_instance *, t_gap_solution *) ;

// <[End]> Determinist neighbourhood


// <[Start]> Solution 0

short
search_solution_0 (t_gap_instance *, t_gap_solution *) ;

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

short
clone_gap_solution (t_gap_solution *, t_gap_solution *) ;

t_job_list *
alloc_job_list_head (void) ;

short
add_job_to_job_list (t_job_list *, t_elt) ;

// <[End]> Memory allocation


// <[Start]> Input file 

short 
read_orlibrary_input_file (char *, t_gap_instance *, t_gap_solution *) ;

// <[End]> Input file 

// <[Start]> Allowed configuration values

/**
 * Initialize an array holding allowed values for the *TEMPERATURE* schedule string parameter.
 * This array is indexed by enum values, and contains char array pointers.
 * The pointed string are the expected values.
 *
 * @param	allowed	An in/out argument
 */
void configuration_get_allowed_temperature_schedule (char **) ;

/**
 * Initialize an array holding allowed values for the *STEP* schedule string parameter.
 * This array is indexed by enum values, and contains char array pointers.
 * The pointed string are the expected values.
 *
 * @param	allowed	An in/out argument
 */
void configuration_get_allowed_step_schedule (char **) ;

/**
 * Initialize an array holding allowed values for the problem type string parameter.
 * This array is indexed by enum values, and contains char array pointers.
 * The pointed string are the expected values.
 *
 * @param	allowed	An in/out argument
 */
void configuration_get_allowed_problem_type (char **) ;

/**
 * Initialize an array holding allowed values for the neighbourhood exploration string parameter.
 * This array is indexed by enum values, and contains char array pointers.
 * The pointed string are the expected values.
 *
 * @param	allowed	An in/out argument
 */
void configuration_get_allowed_neighbourhood_exploration (char **) ;

// <[End]>  Allowed configuration values

// <[Start]> CLI

short
parse_cli_arguments (
  t_configuration_annealing *,
  t_configuration_execution *,
  int,
  char **
) ;

short 
print_result (t_gap_instance *,t_gap_solution *) ;

// <[End]> CLI

// <[Start]> Configuration file

/*
 * Parse the simulated annealing parameter file, expected in INI format.
 * The parameters control the annealing process.
 * They define the temperature schedule and the step schedule,
 * which are later computed from them.
 *
 * @param	configuration	An in/out parameter which holds the annealing settings.
 * @param	file		The INI file to parse the parameter from.
 * @return	A numeric value, 1 for success, 0 for failure	
 */
short
load_configuration_annealing (
  t_configuration_annealing * configuration,
  char * file
);

/*
 * Parse the execution parameter file, expected in INI format.
 * The parameters control some of the execution process.
 *
 * @param	configuration	An in/out parameter which holds the execution settings.
 * @param	file		The INI file to parse the parameter from.
 * @return	A numeric value, 1 for success, 0 for failure	
 */
short
load_configuration_execution (
  t_configuration_execution * configuration,
  char * file
) ;

// <[End]> Configuration file

// <[Start]> Thread

void 
* thread_countdown (void * ) ;

void 
* thread_temperature (void * ) ;
 
// <[End]> Thread

// <[Start]> Configuration annealing

short
parse_configuration_annealing (t_configuration_annealing *, char *) ;

// <[End]> Configuration annealing

#endif
