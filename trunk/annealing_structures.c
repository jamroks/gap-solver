/* ============================ */
#define MAX_AGENT 	50  
#define MAX_JOB 	500  

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
typedef int t_elt ;
typedef t_elt t_agent ;
typedef t_elt t_job ;
typedef short t_method ;
typedef int t_gain ;
typedef int t_cout ;
typedef short t_bool ;
typedef struct {
	t_elt list[MAX_JOB] ;
	} t_list ;
typedef struct { 			
	char name[50] ; 			// nom de l'instance				:selon Yagiura
	int job_count ;				// nombre de tâches 				:T
	int agent_count ;			// nombre d'agent  				:I
	t_cout capacity[MAX_AGENT] ;		// capacité de chaque agent			:b(i)
	t_gain gain[MAX_AGENT][MAX_JOB] ;	// gain de la tache t affectée à l'agent i	:c(i,t)		
	t_cout cost[MAX_AGENT][MAX_JOB] ;	// coût de la tache t affectée à l'agent i	:r(i,t)		
	} S_gap_instance ;	
			
typedef struct {
	t_gain value ; 				// valeur de l'instance
	t_bool assignment[MAX_AGENT][MAX_JOB] ;	// affectation de la tache t affectée à l'agent i :x(i,t)
						// 1-> affectée  0-> non affectée  unevaluated-> non évaluée
	t_cout capacity_left[MAX_AGENT] ;	// capacité de chaque agent			
	} S_gap_solution ;

