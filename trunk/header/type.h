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
#include "../header/constant.h"

#ifndef TYPE_H
#define TYPE_H

typedef short t_error ;

typedef unsigned int t_elt ;

typedef t_elt t_agent ;

typedef t_elt t_job ;

typedef short t_method ;

typedef int t_gain ;

typedef int t_cost ;

typedef unsigned short t_bool ;

typedef struct {
  t_elt *list ;
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
  MAXIMIZATION ,
  MINIMIZATION ,
} t_problem_type ;

typedef struct {
  t_problem_type problem_type ;
  short ( * get_next_solution) (t_gap_solution *, t_gap_instance *, t_gap_solution *) ;
  float * step_temperature ;
  int *  step_duration ;
  int step_current ;
  int step_count ;
  short verbosity ;
  short timeout ;
  int duration ;
  int temperature ;
  long transfert_count ;
  long swap_count ;
  t_gap_solution * best_solution ;
  t_gap_solution * current_solution ;
} t_gap_solver_registry ;

typedef enum {
  STEP_REPARTITION_LOGARITHMIC_1 ,
  STEP_REPARTITION_LOGARITHMIC_2 ,
  STEP_REPARTITION_LOGARITHMIC_3 ,
  STEP_REPARTITION_SQUARE_ROOT_1 ,
  STEP_REPARTITION_SQUARE_ROOT_2 ,
  STEP_REPARTITION_SQUARE_ROOT_3 ,
  STEP_REPARTITION_LINEAR_1 ,
  STEP_REPARTITION_LINEAR_2 ,
  STEP_REPARTITION_LINEAR_3 ,
  STEP_REPARTITION_QUADRATIC_1 ,
  STEP_REPARTITION_QUADRATIC_2 ,
  STEP_REPARTITION_QUADRATIC_3
} t_step_repartition ;

typedef enum {
  TEMPERATURE_DECREASE_LOGARITHMIC_1 ,
  TEMPERATURE_DECREASE_LOGARITHMIC_2 ,
  TEMPERATURE_DECREASE_LOGARITHMIC_3 ,
  TEMPERATURE_DECREASE_SQUARE_ROOT_1 ,
  TEMPERATURE_DECREASE_SQUARE_ROOT_2 ,
  TEMPERATURE_DECREASE_SQUARE_ROOT_3 ,
  TEMPERATURE_DECREASE_LINEAR_1 ,
  TEMPERATURE_DECREASE_LINEAR_2 ,
  TEMPERATURE_DECREASE_LINEAR_3 ,
  TEMPERATURE_DECREASE_QUADRATIC_1 ,
  TEMPERATURE_DECREASE_QUADRATIC_2 ,
  TEMPERATURE_DECREASE_QUADRATIC_3
} t_temperature_decrease ;

typedef enum {
  NEIGHBOURHOOD_EXPLORATION_DETERMINIST ,
  NEIGHBOURHOOD_EXPLORATION_STOCHASTIC
} t_neighbourhood_exploration ;

typedef enum {
  INPUT_SOURCE_FILE ,
  INPUT_SOURCE_STDIN
} t_input_source ;

typedef struct {
  int duration ;
  int step_count ;
  int step_max_duration ;
  t_step_repartition step_repartition ;
  float temperature_max ;
  float temperature_min ;
  t_temperature_decrease temperature_decrease ;
  t_problem_type problem_type ;
  t_neighbourhood_exploration neighbourhood_exploration ;
} t_configuration_annealing ;

typedef struct {
  char * input_file ;
  t_input_source input_source ;
} t_configuration_execution ;
#endif
