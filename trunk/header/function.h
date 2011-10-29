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
#include "../header/type.h"

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
 * Return an array holding allowed values for the *TEMPERATURE* schedule string parameter.
 * This array is indexed by enum values, and contains char array pointers.
 * The pointed string are the expected values.
 */
char ** configuration_get_allowed_temperature_schedule () ;

/**
 * Return an array holding allowed values for the *STEP* schedule string parameter.
 * This array is indexed by enum values, and contains char array pointers.
 * The pointed string are the expected values.
 */
char ** configuration_get_allowed_step_schedule () ;

/**
 * Return an array holding allowed values for the problem type string parameter.
 * This array is indexed by enum values, and contains char array pointers.
 * The pointed string are the expected values.
 */
char ** configuration_get_allowed_problem_type () ;

/**
 * Return an array holding allowed values for the neighbourhood exploration string parameter.
 * This array is indexed by enum values, and contains char array pointers.
 * The pointed string are the expected values.
 */
char ** configuration_get_allowed_neighbourhood_exploration () ;

// <[End]>  Allowed configuration values

// <[Start]> Generic validation

/**
 * Returns 1 if the given file exists and can be open,
 * 0 otherwise
 * @param file File path
 */
short
validate_file (char * file) ;

/**
 * Return the position of the searched string in the allowed array,
 * -1 if it is not present.
 * @param string Searched string
 * @param string Allowed strings
 */
short validate_string (char * string, char ** allowed) ;

/**
 * Return 1 if the given int is in the given range,
 * 0 otherwise
 * @param min Range start inclusive
 * @param max Range end inclusive
 */
short validate_int (int value, int min, int max) ;

// <[End]> Generic validation

// <[Start]> Execution parameter validation

// <[End]> Execution parameter validation

/**
 * Checks if the given input string value is valid for a problem type,
 * and returns the scalar value to which it is mapped.
 * The expected values are defined as constants.
 *
 * @param value A string that should match the expected param value (ie. equ li1 ex1 lo1 ...)
 * @return The t_problem_type enum value of the given string if correct, -1 otherwise.
 */
short validate_problem_type (char * value) ;

/**
 * Checks if the given input string value is valid for a neighbourhood exploration,
 * and returns the scalar value to which it is mapped.
 * The expected values are defined as constants.
 *
 * @param value A string that should match the expected param value (ie. equ no1 as1 de1 ...)
 * @return The t_neighbourhood_exploration enum value of the given string if correct, -1 otherwise.
 */
short validate_neighbourhood_exploration (char * value) ;

// <[Start]> Annealing parameter validation

/**
 * Checks if the given input int value is valid for a duration.
 * @param value Given duration
 */
short validate_duration (int value) ;

/**
 * Checks if the given input int value is valid for a step count.
 * @param value Given step count
 */
short validate_step_count (int value) ;

/**
 * Checks if the given temperature is valid
 * @param value Given temperature
 */
short validate_temperature (int value) ;

/**
 * Checks if the given temperature bounds are valid as a range
 * @param value1 Lower bound
 * @param value2 Upper bound
 */
short validate_temperatures (int value1, int value2) ;

/**
 * Checks if the given input string value is valid for a *STEP* schedule,
 * and returns the scalar value to which it is mapped.
 * The expected values are defined as constants.
 *
 * @param value A string that should match the expected param value (ie. equ no1 as1 de1 ...)
 * @return The t_step_schedule enum value of the given string if correct, -1 otherwise.
 */
short validate_step_schedule (char * value) ;

/**
 * Checks if the given input string value is valid for a *TEMPERATURE* schedule,
 * and returns the scalar value to which it is mapped.
 * The expected values are defined as constants.
 *
 * @param value A string that should match the expected param value (ie. equ li1 ex1 lo1 ...)
 * @return The t_temperature_schedule enum value of the given string if correct, -1 otherwise.
 */
short validate_temperature_schedule (char * value) ;

// <[End]> Annealing parameter validation

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