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

#ifndef TYPE_H
#define TYPE_H

#include "../header/constant.h"

typedef short t_error ;

typedef unsigned int t_elt ;

typedef t_elt t_agent ;

typedef t_elt t_job ;

typedef short t_method ;

typedef int t_gain ;

typedef int t_cost ;

typedef unsigned short t_bool ;

typedef struct {
  t_elt list[MAX_JOB] ;
  int nb_elt ;
} t_list ;

struct t_job_list {
  t_elt job ;
  struct t_job_list * next ;
} ;

typedef struct t_job_list t_job_list;

typedef struct { 
  char name[50] ;
  int job_count ;
  int agent_count ;
  t_cost * capacity ;  // D1 : agent
  t_gain ** gain ; // D1 : agent, D2 : job
  t_cost ** cost ; // D1 : agent, D2 : job
} t_gap_instance ;

typedef struct {
  char name[50] ;
  int job_count ;
  int agent_count ;
  t_gain value ;
  t_cost * capacity_left ;  // D1 : agent
  t_bool ** assignment ; // D1 : agent, D2 : job
  t_job_list ** ll_assignment ; //linked list array
} t_gap_solution ;

typedef enum {
  TRANSFERT ,
  SWAP ,
  ROTATION ,
} t_neighbourhood ;

typedef enum {
  STEP_SCHEDULE_UNASSIGNED ,
  STEP_SCHEDULE_EQUAL ,
  STEP_SCHEDULE_ASCENDING_1 ,
  STEP_SCHEDULE_ASCENDING_2 ,
  STEP_SCHEDULE_ASCENDING_3 ,
  STEP_SCHEDULE_DESCENDING_1 ,
  STEP_SCHEDULE_DESCENDING_2 ,
  STEP_SCHEDULE_DESCENDING_3 ,
  STEP_SCHEDULE_NORMAL_1 ,
  STEP_SCHEDULE_NORMAL_2 ,
  STEP_SCHEDULE_NORMAL_3
} t_step_schedule ;

typedef enum {
  TEMPERATURE_SCHEDULE_UNASSIGNED ,
  TEMPERATURE_SCHEDULE_LINEAR ,
  TEMPERATURE_SCHEDULE_EXPONENTIAL ,
} t_temperature_schedule ;

typedef enum {
  NEIGHBOURHOOD_EXPLORATION_UNASSIGNED ,
  NEIGHBOURHOOD_EXPLORATION_DETERMINIST ,
  NEIGHBOURHOOD_EXPLORATION_STOCHASTIC
} t_neighbourhood_exploration ;

typedef enum {
  UNASSIGNED ,
  MAXIMIZATION ,
  MINIMIZATION ,
} t_problem_type ;

typedef enum {
  INPUT_SOURCE_FILE ,
  INPUT_SOURCE_STDIN
} t_input_source ;

typedef struct {
  int duration ;
  int step_count ;
  t_step_schedule step_schedule ;
  int temperature_first ;
  int temperature_last ;
  t_temperature_schedule temperature_schedule ;
  t_problem_type problem_type ;
  t_neighbourhood_exploration neighbourhood_exploration ;
} t_configuration_annealing ;

typedef struct {
  char * input_file ;
  t_input_source input_source ;
  t_neighbourhood_exploration neighbourhood_exploration ;
  t_problem_type problem_type ;
  t_bool verbose ;
} t_configuration_execution ;

typedef struct {
  t_problem_type problem_type ;
  short ( * get_next_solution) (t_gap_solution *, t_gap_instance *, t_gap_solution *) ;
  int * step_temperature ;
  int * step_duration ;
  int step_current ;
  int step_count ;
  short verbosity ;
  short timeout ;
  long transfert_count ;
  long iteration_count ;
  long unavailable_count ;
  long swap_count ;
  int max_try_count_failure ;
  int max_try_count ;
  t_gap_solution * best_solution ;
  t_gap_solution * current_solution ;
  int (*agtponderate)() ; 	// intance + solution + registre
  int (*jobponderate)() ; 	// intance + solution + registre
  t_neighbourhood method ;
} t_gap_solver_registry ;

typedef enum {
  SOLUTION_CHANGE_SWAP,
  SOLUTION_CHANGE_TRANSFER
} t_solution_change_type ;

typedef struct {
  t_agent source ;
  t_agent destination ;
  t_job job ;
} t_solution_change_transfer ;

typedef struct {
  t_agent source ;
  t_agent destination ;
  t_job source_swapped_job ;
  t_job destination_swapped_job ;
} t_solution_change_swap ;

typedef union {
  t_solution_change_transfer transfer ;
  t_solution_change_swap swap ;
} t_solution_change_contents ;

typedef struct {
  t_solution_change_type type ;
  t_solution_change_contents contents ;
  int delta_value ;
} t_solution_change ;

#endif
