//
//	programme minimum pour tester les fonctions
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "annealing_structures.c"
/* ============================ */
#include "annealing_headers.h"
/* ============================ */
S_gap_instance gap_inst ;
S_gap_solution gap_res ;
short i ;
/* ============================ */ 
int 
main()
/* ============================ */ 
{
i=read_gap(&gap_inst) ;
switch (i) 
	{
	case 1 : { printf("\n Fichier non trouvé\n")    ; } break ;
	case 2 : { printf("\n trop d'agents\n")    ; } break ;
	case 3 : { printf("\n trop de taches\n")  ; } break ;
	case 4 : { printf("\n Paramétrage incomplet\n")  ; } break ;
	} ;
/* _____________________________ */
/* traitement de l'instance ...  */
gap_res.assignment[0][0]=1 ;
gap_res.assignment[0][2]=1 ;
gap_res.assignment[4][99]=1 ;
gap_res.capacity_left[0]=13 ;
gap_res.capacity_left[4]=123 ;
/* _____________________________ */
// affichage du résultat
//printf("nombre d'agents  : %2d\n",gap_inst.agent_count) ;
//printf("nombre de tâches : %2d\n",gap_inst.job_count) ;
print_results(&gap_inst,&gap_res) ;
}	// fin du pgm principal

