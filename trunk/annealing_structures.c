/* ============================ */
#define MAX_AGENT 	50  
#define MAX_JOB 	500  
#define UNEVALUATED 	2  
/* ============================ */
typedef int t_gain ;
typedef int t_cout ;
typedef short t_bool ;
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

