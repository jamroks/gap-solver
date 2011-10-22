/* fonction de lecture de l'instance */
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "annealing_structures.c"
/* ============================ */
short 
read_gap(S_gap_instance *gap)
{
char fichier[80] ;
FILE *fic ;
int valeur ;
int agt,job ;
printf("Nom du fichier de paramètrage ? :") ; 
scanf("%s",&fichier); 
printf("lecture du fichier %s ...\n",fichier) ;  
fic=fopen(fichier, "rt"); 
if (fic==NULL)
	{ 
	return 1 ; 
	} 
  else
	{
	strcpy(gap->name,fichier) ;
	fscanf (fic, "%d", &gap->agent_count);
	if (gap->agent_count >= MAX_AGENT) return 2 ;
	fscanf (fic, "%d", &gap->job_count);
	if (gap->job_count >= MAX_JOB) return 3 ;
	printf("nb agents=%d  & nb jobs=%d\n",gap->agent_count,gap->job_count);
	/* lecture des couts (c(it)) */
	for (agt=0;agt < gap->agent_count;agt++)
		{
		for (job=0;job < gap->job_count;job++)
			{
			fscanf (fic, "%d", &valeur);
	// printf("cout[%d,%d]=%d   ",agt,job,valeur) ;
			gap->cost[agt][job]=valeur ;
			}
	// printf("\n") ;
		};
	/* lecture des ressources (r(it)) */
	for (agt=0; agt < gap->agent_count;agt++)
		{
		for (job=0;job < gap->job_count;job++)
			{
			fscanf (fic, "%d", &valeur);
			gap->gain[agt][job]=valeur ;
			}
	// printf("\n") ;
		};
	/* lecture des capacités des agents (b(i)) */
	for (agt=0;agt < gap->agent_count;agt++)
		{
		fscanf (fic, "%d", &valeur);
		gap->capacity[agt]=valeur ;
	// printf("b[%d]=%d   ",agt,valeur) ;
		};
	// while(!feof(fic)) { return 4 ;} ;
	fclose(fic) ;
	};
return 0 ;
}
