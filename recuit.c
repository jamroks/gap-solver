//
//	programme minimum pour tester les fonctions
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "structures.c"
/* ============================ */
#include "recuit.h"
/* ============================ */
S_gap_instance gap ;
S_gap_solution solution_gap ;
short i ;
/* ============================ */ 
int 
main()
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

