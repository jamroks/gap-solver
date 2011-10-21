/* fonction de lecture de l'instance */
short read_gap(S_gap_instance *gap)
{
char fichier[80] ;
FILE *fic ;

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
	fscanf (fic, "%f", &gap.agent_count);
	if (gap.agent_count >= max_agent) return 2 ;
	fscanf (fic, "%f", &gap.job_count);
	if (gap.job_count >= max_job) return 3 ;
	
	while(!feof(fic)) 
		{
		fscanf (fic, "%f", &);
		}
	}
fclose(fic) ;
}
