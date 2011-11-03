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

int 
equity(t_gap_instance *inst, t_gap_solution *sol, t_gap_solver_registry *reg, t_elt elt) ;

/**
 *  agent_list : permet de lister dans un tableau (de type t_list) les agents disponibles 
 *  @param : instance
 *  @ return : liste des agents disponibles 
 */
t_list 
agent_list (t_gap_instance *gap_inst);

/** subtract_elt_from_list : permet d'enlever un élément dans la liste  
 * @param : adresse de la liste à examiner
 * @return : rien
 */
void
subtract_elt_from_list (t_list *, t_elt ) ;

/** job_agt_list : retourne la liste des taches pour un agent1 donné, acceptable par un agent2 cible 
 * @param : instance
 * @param : solution
 * @param : agent1
 * @param : agent2
 * return : liste de taches
 */
t_list
job_agt_list (t_gap_instance *, t_gap_solution *, t_agent , t_agent ) ;

/** job_swap0_list : retourne la liste des taches pour un agent1 donné, sans condition 
 * param : instance
 * param : solution
 * param : agent1
 * param : agent2 (ne sert à rien pour le moment
 * return : liste de tâches
 */
t_list
job_swap0_list (t_gap_instance *, t_gap_solution *, t_agent , t_agent ) ;

/** job_swap0_list : pour un agent1 et une tache job donnée, retourne la liste des taches acceptable par un agent2 
 * param : instance
 * param : solution
 * param : agent1
 * param : agent2
 * param : tache
 * return : liste de tâches 
 */
t_list
job_swap_list (t_gap_instance *, t_gap_solution *, t_agent , t_agent , t_job ) ;

/** take_choice : tirage aléatoire d'un élément dans une liste, pondéré selon une fonction 
 * param : instance
 * param : solution
 * param : registre
 * param : liste
 * param : fonction
 * return : un élément
 */

t_elt
take_choice(t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, 
            t_list *, int (*ponderate)()) ;

// <[Start]> fonctions de ponderation

/** uniform : fonction de pondération uniforme (pour take_choice) 
 * param : instance
 * param : solution
 * param : registre
 * param : élément
 * return : entier
 */

int 
uniform(t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, t_elt ) ;

/* capacity_left : fonction de pondération basée sur la capacité résiduelle des agents (pour take_choice sur agent) 
 * param : instance
 * param : solution
 * param : registre
 * param : élément
 * return : entier
 */
int 
capacity_left(t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, t_elt ) ;

/* capacity : fonction de pondération basée sur la capacité des agents (pour take_choice sur agent)
 * param : instance
 * param : solution
 * param : registre
 * param : élément
 * return : entier
 */
int 
capacity(t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, t_elt ) ;

// <[End]> fonctions de ponderation

/* unavailable : fonction appelée pour chaque occurrence d'une impossibilité d'avoir un élement dans une liste */
void 
unavailable (t_error ) ;

/** increasing: fonction déterminant la meilleure tâche à trasnférer de agt1 à agt2 
 * param : instance
 * param : solution
 * param : registre
 * param : agent1
 * param : agent2
 * param : liste
 * return : job
 */
t_job
increasing(t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, t_agent , t_agent , t_list *) ;

void
memorize_solution(t_gap_instance *, t_gap_solution *, t_gap_solver_registry * ) ;

short
solution_evaluation (int, int, t_problem_type, float);

// <[Start]> stochastic neighbourhood

/* à partir d'une solution réalisable, fournit une autre solution réalisable aléatoirement dans le voisinage */
short
stochastic_next_solution (t_gap_solution *, t_gap_instance *, t_gap_solution *, t_gap_solver_registry *) ;

// <[End]> stochastic neighbourhood


// <[Start]> Determinist neighbourhood

short
determinist_next_solution (
  t_solution_change * change,
  t_gap_instance * instance,
  t_gap_solution * current,
  t_gap_solver_registry * registry
) ;

// <[End]> Determinist neighbourhood


// <[Start]> Solution 0

short
search_solution_0 (t_gap_instance *, t_gap_solution *) ;

// <[End]> Solution 0


// <[Start]> Memory allocation

/**
 * Allocates memory for the nested objects.
 *
 * @param agent_count	Instance agent count
 * @param job_count	Instance job count
 */
short
alloc_gap_instance (t_gap_instance *, int, int) ;

/**
 * Free memory allocated to the nested objects.
 */
short 
free_gap_instance (t_gap_instance *) ;

/**
 * Allocates memory for the nested objects.
 *
 * @param agent_count	Instance agent count
 * @param job_count	Instance job count
 */
short
alloc_gap_solution (t_gap_solution *, int, int) ;

/**
 * Free memory allocated to the nested objects.
 */
short
free_gap_solution (t_gap_solution *) ;

/**
 * Recursively copy the given source.
 * Memory for nested objects will be allocated.
 *
 * @param destination	
 * @param source
 */
short
clone_gap_solution (t_gap_solution *, t_gap_solution *) ;

/**
 * Creates the linked list head,
 * and gives it the NULL value.
 */
t_job_list *
alloc_job_list_head (void) ;

/**
 * Add a job to the given linked list.
 *
 * @param head	Linked list head
 * @param job	Job index
 */
short
add_job_to_job_list (t_job_list *, t_elt) ;

/**
 * Free the memory allocated to job element.
 * Doesn't free the linked list head.
 */
short
free_job_list (t_job_list * list) ;

/**
 * Clone the job element from a given list.
 * Works from a given head.
 *
 * @param destination_head	Destination linked list head
 * @param source_head		Source linked list head
 */
short
clone_job_list (t_job_list * destination_head, t_job_list * source_head) ;

/**
 * Removes the given job from the linked list
 *
 * @param head	Linked list head
 *
 * @param job	Job to remove
 *
 */
short
remove_job_from_job_list (t_job_list * head, t_elt job) ;

void
memory_allocation_error () ;

// <[End]> Memory allocation


// <[Start]> Input file 

/**
 * Scan an instance file in the operational research library format,
 * and populate the given structures with its values.
 * http://people.brunel.ac.uk/~mastjjb/jeb/orlib/gapinfo.html
 *
 * @param file_name
 * @param instance	Memory for nested objects will be allocated in this function
 * @param solution	Memory for nested objects will be allocated in this function
 */
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

// <[Start]> Step repartition function

/**
 * The following functions have an in/out array parameter,
 * which holds every step duration for the given step count.
 */

/**
 * Gives a time repartition with equal step.
 */
void
duration_equal (int * step_duration, int duration, int step_count) ;

/**
 * Gives a time repartition with slowly ascending step duration.
 * Its values belongs to a geometric progression which sums
 * to the given duration argument.
 * The common ratio is 1.3.
 *
 * @param step_duration	Array
 * @param duration	The sum of every step duration
 * @param step_count
 */
void
duration_ascending_1 (int * step_duration, int duration, int step_count) ;

/**
 * Gives a time repartition with medium ascending step duration.
 * Its values belongs to a geometric progression which sums to
 * the given duration argument.
 * The common ratio is 1.6.
 *
 * @param step_duration	Array
 * @param duration	The sum of every step duration
 * @param step_count
 */
void
duration_ascending_2 (int * step_duration, int duration, int step_count) ;

/**
 * Gives a time repartition with fast ascending step duration.
 * Its values belongs to a geometric progression which sums
 * to the given duration argument.
 * The common ratio is 1.9.
 *
 * @param step_duration	Array
 * @param duration	The sum of every step duration
 * @param step_count
 */
void
duration_ascending_3 (int * step_duration, int duration, int step_count) ;

/**
 * Gives a time repartition with slow descending step duration.
 * Its values belongs to a geometric progression which sums
 * to the given duration argument.
 * The common ratio is 0.7.
 *
 * @param step_duration	Array
 *
 * @param duration	The sum of every step duration
 *
 * @param step_count
 */
void
duration_descending_1 (int * step_duration, int duration, int step_count) ;

/**
 * Gives a time repartition with medium descending step duration.
 * Its values belongs to a geometric progression which sums
 * to the given duration argument.
 * The common ratio is 0.4.
 *
 * @param step_duration	Array
 *
 * @param duration	The sum of every step duration
 *
 * @param step_count
 */
void
duration_descending_2 (int * step_duration, int duration, int step_count) ;

/**
 * Gives a time repartition with fast descending step duration.
 * Its values belongs to a geometric progression which sums
 * to the given duration argument.
 * The common ratio is 0.2.
 *
 * @param step_duration	Array
 *
 * @param duration	The sum of every step duration
 *
 * @param step_count
 */
void
duration_descending_3 (int * step_duration, int duration, int step_count) ;

/**
 * Gives a time repartition with a pseudo normal distribution.
 * Low slope.
 *
 * @param step_duration	Array
 *
 * @param duration	The sum of every step duration
 *
 * @param step_count
 */
void
duration_normal_1 (int * step_duration, int duration, int step_count) ;

/**
 * Gives a time repartition with a pseudo normal distribution.
 * Medium slope.
 *
 * @param step_duration	Array
 *
 * @param duration	The sum of every step duration
 *
 * @param step_count
 */
void
duration_normal_2 (int * step_duration, int duration, int step_count) ;

/**
 * Gives a time repartition with a pseudo normal distribution.
 * High slope.
 *
 * @param step_duration	Array
 *
 * @param duration	The sum of every step duration
 *
 * @param step_count
 */
void
duration_normal_3 (int * step_duration, int duration, int step_count) ;

/**
 * Gives a temperature schedule with exponential temperature decrease.
 *
 * @param schedule_temperature	Array
 *
 * @param temperature	The sum of every step temperature
 *
 * @param step_count
 */
void
temperature_exponential (
  int * schedule_temperature,
  int temperature_start,
  int temperature_end,
  int step_count
) ;


/**
 * Gives a temperature schedule with linear temperature decrease.
 *
 * @param schedule_temperature	Array
 *
 * @param temperature	The sum of every step temperature
 *
 * @param step_count
 */
void
temperature_linear (
  int * schedule_temperature,
  int temperature_start,
  int temperature_end,
  int step_count
) ;

// <[End]> Step repartition function

// <[Start]> Schedules initialization

/**
 * Create a time repartition with the given schedule type.
 *
 * @param step		Array
 *
 * @param schedule	Step schedule type
 *
 * @param duration	The sum of every step duration
 *
 * @param step_count
 */
void init_step_schedule (
  int * step,
  t_step_schedule schedule,
  int duration,
  int step_count
) ;

/**
 * Create a temperature repartition with the given schedule type.
 *
 * @param temperature	Array
 * @param step_schedule	Temperature schedule type
 * @param start		Max temperature
 * @param end		Min temperature
 */
void init_temperature_schedule (
  int * temperature,
  t_temperature_schedule schedule,
  int start,
  int end,
  int step_count
) ;

// <[End]> Schedules initialization

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
 * @param	configuration	An in/out parameter which holds
 *				the annealing settings.
 *
 * @param	file		The INI file to parse the parameter from.
 *
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
 * @param	configuration	An in/out parameter which holds
 *				the execution settings.
 *
 * @param	file		The INI file to parse the parameter from.
 *
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

// <[Start]> Utility

void
solution_apply_change (
  t_gap_instance * instance,
  t_gap_solution * solution,
  t_solution_change * change
) ;

// <[End]> Utility

// Tests

void XAVIER_neighbourhood_determinist_try (
  t_gap_solution * _next_solution,
  t_gap_instance * _instance,
  t_gap_solver_registry * _registry) ;

//
#endif
