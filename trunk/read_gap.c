/* fonction de lecture de l'instance */
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "structures.c"
/* ============================ */
short 
read_gap(S_gap_instance *gap)
{
char fichier[80] ;
FILE *fic ;
int valeur ;
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
	fscanf (fic, "%f", gap->agent_count);
	if (gap->agent_count >= MAX_AGENT) return 2 ;
	fscanf (fic, "%f", gap->job_count);
	if (gap->job_count >= MAX_JOB) return 3 ;
	
	while(!feof(fic)) 
		{
		fscanf (fic, "%f", &valeur);
		}
	}
fclose(fic) ;
}
