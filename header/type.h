#ifndef TYPE_H
  #define TYPE_H
/* ============================ */
#define UNEVALUATED 	2  	// valeur de travail; ne doit pas apparaître en début ou fin d'itération 
/* Structures de voisinage      */
#define TRANSFERT	1
#define SWAP		2
#define ROTATION	3
/* liste des codes erreurs possibles */
#define NO_JOB		1	// pas de tâche disponible pour le calcul du voisinage 
#define NO_AGT 		2	// pas de d'agent disponible pour le calcul du voisinage 

/* ============================ */
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
  t_cost *capacity ;
  t_gain **gain ;
  t_cost **cost ;
} t_gap_instance ;	
			
typedef struct {
  char name[50] ;
  int job_count ;
  int agent_count ;
  t_gain value ;
  t_bool **assignment ;
  t_cost *capacity_left ;
} t_gap_solution ;

#endif
