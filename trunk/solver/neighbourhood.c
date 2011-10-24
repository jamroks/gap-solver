/* fonction de calcul de la solution suivante dans un voisinage de la solution précédente */
/*
 * attention je construis la fonction au fur et à mesure en ajoutant des paramètres ..
 * 
*/
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "../header/type.h"
/* ============================ */
#include "../header/function.h"
/* ============================ */
short 
neighbourhood(t_gap_instance *gap_inst, t_gap_solution *gap_cur, t_gap_solution *gap_next, 
		t_method method, void (*f_evaluation)() , t_elt (*take_choice)() )
/* f_evaluation : fonction d'evaluation influençant la distribution de probabilité d'un élément agt ou job */
/* take_choice : fonction de calcul d'un élément, sur tirage aléatoire (usage de f_evaluation)  */
/* list_of_agents(void (*f_evaluation)()) : liste pondérée des agents, selon f_evaluation */
/* subtract_elt_from_list(list,elt) : enlève l'élément elt de la liste */ 
/* list_of_jobs_agt(agt_1, agt_2) : liste les taches affectées à agt_1 et affectable à agt_2 */
/* unavailable(err) : fonction appelée lors d'une impossibilité, cause n°err */
{
t_list list_of_values ;
int agt_1, agt_2,job ;
/* copie de la solution de départ vers la solution suivante, avant modification */
memcpy(gap_cur, gap_next, sizeof(t_gap_solution)) ;
/* Sélection de la structure de voisinage */ 
switch (method) 
	{
	case TRANSFERT :/* selon un transfert d'une tâche entre deux agents */
			{
			/* constituer la liste pondérée des agents */
			list_of_values=list_of_agents(gap_inst,f_evaluation) ;
			/* tirer au sort un élément dans la liste */
			agt_1 = take_choice(list_of_values) ;
			if (agt_1 == NULL) 
				{ /* pas de tâche possible : saturation de agt_2 */
				unavailable(NO_AGT) ;
				} ;			
			/* enlever agt_1 de la liste */
			subtract_elt_from_list(list_of_values,agt_1) ;
			/* tirer au sort un autre agent dans la liste */
			agt_2 = take_choice(list_of_values) ;

			/* idem pour choisir une tâche admissible de agt_1 vers agt_2 */
			list_of_values=list_of_jobs_agt(gap_cur, agt_1, agt_2) ;
			/* tirer au sort un élément dans la liste */
			job = take_choice(list_of_values) ;
			/* transférer la tâche de agt_1 vers agt_2 */
			if (job == NULL) 
				{ /* pas de tâche possible : saturation de agt_2 */
				unavailable(NO_JOB) ;
				/* CAS A VOIR : VOISINAGE VIDE ! */
				} 
			else
				{
				gap_next->assignment[agt_1][job]=0 ;
				gap_next->assignment[agt_2][job]=1 ;
				} ;			
			} ;
			break ;
	case SWAP :	/* selon un transfert d'une tâche entre deux agents */
			{
			} ;
			break ;
	case ROTATION :	/* selon un transfert d'une tâche entre deux agents */
			{
			} ;
			break ;
	default :	/* cas d'un bug */
		{
		printf("bug n°1") ;
		exit(0) ;
		} ;
		break ;
	} ;
return 0 ;
}
