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

/** extremum : calcul des majorants / minorants pour une instance
 * @param : instance
 */
void 
extremum(t_gap_solution *s, t_gap_instance *i, t_gap_solver_registry *r ) ;

// <[Start]> fonctions de ponderation

/** uniform : fonction de pondération uniforme (pour take_choice) agent ou tache
 * @param : instance
 * @param : solution
 * @param : registre
 * @param : élément
 * @return : entier
 */

int 
_uniform(t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, t_elt ) ;

/* capacity_left : fonction de pondération basée sur la capacité résiduelle des agents (pour take_choice sur agent) 
 * @param : instance
 * @param : solution
 * @param : registre
 * @param : élément
 * @return : entier
 */

int 
_capacity_left(t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, t_elt ) ;

/* capacity : fonction de pondération basée sur la capacité des agents (pour take_choice sur agent)
 * @param : instance
 * @param : solution
 * @param : registre
 * @param : élément
 * @return : entier
 */

int 
_capacity(t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, t_elt ) ;

/* assignments : fonction de pondération basée sur le nombre de tâches assignées à l'agent (pour take_choice sur agent)
 * @param : instance
 * @param : solution
 * @param : registre
 * @param : élément
 * @return : entier
 */

int 
_assignment(t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, t_elt ) ;

// <[End]> fonctions de ponderation


void
memorize_solution(t_gap_instance *, t_gap_solution *, t_gap_solver_registry * ) ;

short
solution_evaluation (int, t_problem_type, float);

// <[Start]> stochastic neighbourhood

/* à partir d'une solution réalisable, fournit une autre solution réalisable aléatoirement dans le voisinage */
t_bool
stochastic_next_solution (t_solution_change * change, t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, t_bool) ;

// <[End]> stochastic neighbourhood


// <[Start]> Determinist neighbourhood

t_bool
next_solution_sequential (
  t_solution_change * change,
  t_gap_instance * instance,
  t_gap_solution * current,
  t_gap_solver_registry * registry,
  t_bool improvement
) ;

// <[End]> Determinist neighbourhood


// <[Start]> Solution 0

short
search_solution_0 (t_gap_instance *, t_gap_solution *) ;

// <[End]> Solution 0


// <[Start]> Memory allocation

short
alloc_gap_instance (t_gap_instance *, int, int) ;

short 
free_gap_instance (t_gap_instance *) ;

short
alloc_gap_solution (t_gap_solution *, int, int) ;

short
free_gap_solution (t_gap_solution *) ;

short
clone_gap_solution (t_gap_solution *, t_gap_solution *) ;

t_job_list *
job_list_allocate_head (void) ;

t_bool
job_list_add_job (t_job_list *, t_elt) ;

t_bool
job_list_free (t_job_list * list) ;

t_bool
job_list_clone (t_job_list * destination_head, t_job_list * source_head) ;

t_bool
job_list_delete_job (t_job_list * head, t_elt job) ;

void
memory_allocation_error () ;

t_bool
job_list_list_add_job_list (t_job_list_list * head, t_job_list * job_list) ;

t_bool
job_list_list_delete_job_list (t_job_list_list * head, t_job_list * job_list) ;

t_job_list_list *
job_list_list_allocate_head () ;

t_bool
job_list_list_free (t_job_list_list * list) ;

// <[End]> Memory allocation

// <[Start]> Input file 

short 
read_orlibrary_input_file (char *, t_gap_instance *, t_gap_solution *) ;

// <[End]> Input file 

// <[Start]> Allowed configuration values

char ** configuration_get_allowed_temperature_schedule () ;

char ** configuration_get_allowed_step_schedule () ;

char ** configuration_get_allowed_problem_type () ;

char ** configuration_get_allowed_neighbourhood_exploration () ;

char ** configuration_get_allowed_agent_ponderation () ;

// <[End]>  Allowed configuration values

// <[Start]> Generic validation

short
validate_file (char * file) ;

short validate_string (char * string, char ** allowed) ;

short validate_int (int value, int min, int max) ;

// <[End]> Generic validation

// <[Start]> Execution parameter validation

short validate_problem_type (char * value) ;

short validate_neighbourhood_exploration (char * value) ;

// <[End]> Execution parameter validation

// <[Start]> Annealing parameter validation

short validate_duration (int value) ;

short validate_step_count (int value) ;

short validate_temperature (int value) ;

short validate_temperatures (int value1, int value2) ;

short validate_step_schedule (char * value) ;

short validate_temperature_schedule (char * value) ;

// <[End]> Annealing parameter validation

// <[Start]> Step repartition function

void
duration_equal (int * step_duration, int duration, int step_count) ;

void
duration_ascending_1 (int * step_duration, int duration, int step_count) ;

void
duration_ascending_2 (int * step_duration, int duration, int step_count) ;

void
duration_ascending_3 (int * step_duration, int duration, int step_count) ;

void
duration_descending_1 (int * step_duration, int duration, int step_count) ;

void
duration_descending_2 (int * step_duration, int duration, int step_count) ;

void
duration_descending_3 (int * step_duration, int duration, int step_count) ;

void
duration_normal_1 (int * step_duration, int duration, int step_count) ;

void
duration_normal_2 (int * step_duration, int duration, int step_count) ;

void
duration_normal_3 (int * step_duration, int duration, int step_count) ;

void
temperature_exponential (
  int * schedule_temperature,
  int temperature_start,
  int temperature_end,
  int step_count
) ;

void
temperature_linear (
  int * schedule_temperature,
  int temperature_start,
  int temperature_end,
  int step_count
) ;

// <[End]> Step repartition function

// <[Start]> Schedules initialization

void init_step_schedule (
  int * step,
  t_step_schedule schedule,
  int duration,
  int step_count
) ;

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
print_result (FILE *, t_gap_instance *,t_gap_solution *) ;

// <[End]> CLI

// <[Start]> Configuration file

short
load_configuration_annealing (
  t_configuration_annealing * configuration,
  char * file
);

short
load_configuration_execution (
  t_configuration_execution * configuration,
  char * file
) ;

// <[End]> Configuration file

// <[Start]> Thread

void 
* thread_operator (void * ) ;
 
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

// <[Start]> Search

void simple_search (
  t_gap_instance * instance,
  t_gap_solution * solution,
  t_gap_solver_registry * registry
) ;

void annealing (
  t_gap_instance * instance,
  t_gap_solution * solution,
  t_gap_solver_registry * registry
) ;

// <[End]> Search

#endif
