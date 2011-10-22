#include "../header/common.h"

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
  SOLVE ;
  VERSION ;
  HELP ;
} t_gap_solver_action;

typedef struct {
  long max_execution_time ;
  long max_iteration_count ;
  long start_time ;
  short ( * input_function) (char *, t_gap_instance *, t_gap_solution *) ;
  t_gap_solver_action action ;
} t_gap_solver_context ;

#endif
