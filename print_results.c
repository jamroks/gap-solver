/* fonction d'affichage du résultat */
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "annealing_structures.c"
/* ============================ */
short 
print_results(S_gap_instance *gap_instance, S_gap_solution *gap_solution)
{
char file_name[80] ;
FILE *res_file ;
int valeur ;
int agt,job ;
int nb_line=0 ;
int agt_num ;				/*  un agent  */
int ass_num ;				/*  nombre de tâches affectées à un agent  */
strcpy(file_name,gap_instance->name) ;
printf("Nom du fichier de résultat :%s\n",file_name) ; 
strcat(file_name,".res") ;
printf("Nom du fichier de résultat :%s\n",file_name) ; 
res_file=fopen(file_name, "w"); 
if (res_file==NULL)
	{ 
	return 1 ; 
	} 
  else
	{
	fprintf(res_file, "============================\n");
	fprintf(res_file, "Nombre d'agents  %d\n", gap_instance->agent_count);
	fprintf(res_file, "Nombre de tâches %d\n", gap_instance->job_count);
	/* écriture des affectations (x(it)) */
	for (agt=0;agt < gap_instance->agent_count;agt++)
		{
		/* pour chaque agent agt */
		fprintf(res_file, "Agent n°%d\n", agt+1);
		/* capacité initiale et résiduelle */
		for (job=0;job < gap_instance->job_count;job++)
			{
			if (gap_solution->assignment[agt][job] == 1)
				{
				ass_num++ ;
				} ;
			} ;
		fprintf(res_file, "\tcapacité initiale: %3d\t résiduelle: %3d\tnb tâches: %3d\n", 
			gap_instance->capacity[agt], gap_solution->capacity_left[agt], ass_num);
		/* pour chaque tache : affectée à cet agent ?  */
		ass_num=0 ;
		fprintf(res_file, "\tliste des tâches affectées:\n");
		for (job=0;job < gap_instance->job_count;job++)
			{
			if (gap_solution->assignment[agt][job] == 1)
				{
				fprintf (res_file, "%3d  ", job+1);
				} ;
			}
		fprintf(res_file, "\n_____________________________________________________________________\n") ;
		};
	fprintf(res_file, "============================\n");
	fclose(res_file) ;
	};
return 0 ;
}
