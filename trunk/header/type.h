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

typedef struct {
  long iterations ;
  long temperature_start ;
  long temperature_decrease_function ;
  long time_start ;
  long time_max_duration ;
  short neighborhood_exploration_mode ;
  short verbosity ;
  char * input_file ;
  short ( * get_input) (char *, t_gap_instance *, t_gap_solution *) ;
} t_gap_solver_context ;

#endif
