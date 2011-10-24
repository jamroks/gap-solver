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
} t_list ;

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
} t_gap_solution ;

typedef enum {
  MAXIMIZATION ,
  MINIMIZATION ,
} t_problem_type ;

typedef struct {
  t_problem_type problem_type ;
  int initial_temperature ;
  char * input_file ;
  short ( * get_input) (char *, t_gap_instance *, t_gap_solution *) ;
  short ( * get_next_solution) (t_gap_solution *, t_gap_instance *, t_gap_solution *) ;
  float ( * get_next_temperature) (float *) ;
  short verbosity ;
  short timeout ;
  int duration ;
  int temperature ;
  long transfert_count ;
  long swap_count ;
  t_gap_solution * best_solution ;
  t_gap_solution * current_solution ;
} t_gap_solver_registry ;



#endif
