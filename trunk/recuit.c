//
//	programme minimum pour tester les fonctions
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
const short max_agent=50 ;
const int max_job=500 ;
const short unevaluated=2 ;
/* ============================ */
typedef int t_gain ;
typedef int t_cout ;
typedef short t_bool ;
typedef struct {				
	char name[50] ; 			// nom de l'instance				:selon Yagiura
	int job_count ;				// nombre de tâches 				:T
	int agent_count ;			// nombre d'agent  				:I
	t_cout capacity[max_agent] ;		// capacité de chaque agent			:b(i)
	t_gain gain[max_agent][max_job] ;	// gain de la tache t affectée à l'agent i	:c(i,t)		
	t_cout cost[max_agent][max_job] ;	// coût de la tache t affectée à l'agent i	:r(i,t)		
	} S_gap_instance ;	
			
typedef struct {
	t_gain value ; 				// valeur de l'instance
	t_bool assignment[max_agent][max_job] ;	// affectation de la tache t affectée à l'agent i :x(i,t)
						// 1-> affectée  0-> non affectée  unevaluated-> non évaluée
	t_cout capacity_left[max_agent] ;	// capacité de chaque agent			
	} S_gap_solution ;
/* ============================ */
#include <./recuit.h>
/* ============================ */
S_gap_instance gap ;
short i ;
/* ============================ */ 
int main()
/* ============================ */ 
{
i=read_gap(&gap) ;
switch (i) 
	{
	case 1 : { printf("\n Fichier non trouvé\n")    ; } break ;
	case 2 : { printf("\n trop d'agents\n")    ; } break ;
	case 3 : { printf("\n trop de taches\n")  ; } break ;
	case 4 : { printf("\n Paramétrage incomplet\n")  ; } break ;
	} ;
// affichage du résultat
printf("nombre d'agents\t: %2d\n",gap.agent_count) ;
printf("nombre de tâches\t: %2d\n",gap.job_count) ;
}	// fin du pgm principal

