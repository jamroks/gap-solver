
/* fonction de memorisation d'une solution */
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "../header/common.h"
/* ============================ */
/** function_name : permet de retourner le nom en clair d'une fonction de pondération  
 * @param : adresse de la chaine de caractère en retour
 * @param : adresse de la fonction
 * @return : rien
 *    */
static void
_function_name (char *f_name, int (*ponderate)() ) 
{
if (ponderate == _uniform)
      strcpy(f_name, "uniform") ;
if (ponderate == _capacity_left)
      strcpy(f_name, "capacity_left") ;
if (ponderate == _capacity)
      strcpy(f_name, "capacity") ;
if (ponderate == _assignments)
      strcpy(f_name, "assignments") ;
} ;

/** method_name : permet de retourner le nom en clair de la structure de voisinage
 * @param : nom en clair
 * @param : structure à examiner
 * @return : rien
 *    */
static void
_method_name (char *f_name, t_problem_type method ) 
{
if (method == SOLUTION_CHANGE_TRANSFER )
      strcpy(f_name, "TRANSFERT") ;
if (method == SOLUTION_CHANGE_SWAP )
      strcpy(f_name, "ECHANGE") ;
if (method == SOLUTION_CHANGE_MULTI_SWAP )
      strcpy(f_name, "MULTI SWAP") ;
} ;

/** temp_schedule_name : permet de retourner le nom en clair de la méthode de décroissance de T°
 * @param : nom en clair
 * @param : méthode à examiner
 * @return : rien
 *    */
static void
_temp_schedule_name (char *f_name, t_temperature_schedule t_schedule) 
{
if (t_schedule == TEMPERATURE_SCHEDULE_LINEAR )
      strcpy(f_name, "LINEAIRE") ;
if (t_schedule == TEMPERATURE_SCHEDULE_EXPONENTIAL)
      strcpy(f_name, "EXPONENTIELLE") ;
if (t_schedule == TEMPERATURE_SCHEDULE_UNASSIGNED )
      strcpy(f_name, "non assignée") ;
} ;

/** memorize_solution : permet de mémoriser les solutions intermédiaires dans un tir.
 * @param : nom en clair
 * @param : méthode à examiner
 * @return : rien
 *    */

void 
memorize_solution(t_gap_instance *inst, t_gap_solution *sol, t_gap_solver_registry *reg )
{
char fichier[80] ;
t_job job ;
t_agent agt ;
char job_function[20] ;
char agt_function[20] ;
char method_name[20] ;
char temp_schedule[20] ;
FILE *fic ;
if (reg->verbosity == TRUE) printf("\tmemorize_solution ...\n") ;
fic=fopen("detail_tir.csv", "a"); 
if (fic==NULL)
  {
    printf("Impossible d'ouvrir le fichier detail_tir.csv\n") ;
  } 
  else
  {
  _function_name(agt_function , reg->memorization.agtponderate) ;
//printf("\n nom=%s\n",agt_function) ;
  _function_name(job_function , reg->memorization.jobponderate) ;
//printf("\n nom=%s\n",job_function) ;
  _method_name(method_name, reg->memorization.method) ;
//printf("\n nom=%s\n",method_name) ;
  _temp_schedule_name(temp_schedule, reg->memorization.temperature_schedule) ;
//printf("\n T° nom=%s\n",temp_schedule) ;
  fprintf(fic, "%s ; %d ; %d ; ",inst->name , inst->agent_count , inst->job_count) ;
//printf("\n nom=%s",inst->name) ;
fprintf(fic, "%d ; %d ; %s ; ",
    reg->memorization.temperature_first , reg->memorization.temperature_last , temp_schedule) ;
  fprintf(fic, " %s ; %s ; %s ; ", agt_function , job_function , method_name) ; 
//printf("\n nom=%d",reg->memorization.iteration_count) ;
  fprintf(fic,"%ld ;", reg->memorization.iteration_count) ;
//printf("\n nom=%d",reg->memorization.unavailable_count) ;
  fprintf(fic,"%ld ;", reg->memorization.unavailable_count) ;
//printf("\n nom=%d",reg->memorization.max_try_count_failure) ;
  fprintf(fic,"%d ;", reg->memorization.max_try_count_failure) ;
//printf("\n nom=%d",reg->memorization.transfert_count) ;
  fprintf(fic,"%ld ;", reg->memorization.transfert_count) ;
//printf("\n nom=%d",reg->memorization.swap_count) ;
  fprintf(fic,"%ld ;", reg->memorization.swap_count) ;
  for (agt = 0 ; agt < inst->agent_count ; agt++)
    {
    fprintf(fic," %d ;",sol->capacity_left[agt]) ;
    } ;
  fprintf(fic, "\n") ;
  fclose(fic) ;
  } ;
}

/** memorize_best : mémorize le résultat final pour un tir
 * @param : nom en clair
 * @param : méthode à examiner
 * @return : rien
 *    
 */

void 
memorize_best(t_gap_instance *inst, t_gap_solution *sol, t_gap_solver_registry *reg )
{
char fichier[80] ;
t_job job ;
t_agent agt ;
char job_function[20] ;
char agt_function[20] ;
char method_name[20] ;
char temp_schedule[20] ;
FILE *shot_file ;
printf("\tmemorize_best ...\n") ;
if (reg->verbosity == TRUE) printf("\tmemorize_solution ...\n") ;
shot_file=fopen("tirs.csv", "a"); 
if (shot_file==NULL)
  { 
  printf("Impossible d'ouvrir le fichier des tirs \n") ;
  } 
  else
  {
  _function_name(agt_function , reg->memorization.agtponderate) ;
//printf("\n nom=%s\n",agt_function) ;
  _function_name(job_function , reg->memorization.jobponderate) ;
//printf("\n nom=%s\n",job_function) ;
  _method_name(method_name, reg->memorization.method) ;
//printf("\n nom=%s\n",method_name) ;
  _temp_schedule_name(temp_schedule, reg->memorization.temperature_schedule) ;
//printf("\n T° nom=%s\n",temp_schedule) ;
  fprintf(shot_file, "%s ; %d ; %d ; ",inst->name , inst->agent_count , inst->job_count) ;
//printf("\n nom=%s",inst->name) ;
fprintf(shot_file, "%d ; %d ; %s ; ",
    reg->memorization.temperature_first , reg->memorization.temperature_last , temp_schedule) ;
  fprintf(shot_file, " %s ; %s ; %s ; ", agt_function , job_function , method_name) ; 
//printf("\n nom=%d",reg->memorization.iteration_count) ;
  fprintf(shot_file,"%ld ;", reg->memorization.iteration_count) ;
//printf("\n nom=%d",reg->memorization.unavailable_count) ;
  fprintf(shot_file,"%ld ;", reg->memorization.unavailable_count) ;
//printf("\n nom=%d",reg->memorization.max_try_count_failure) ;
  fprintf(shot_file,"%d ;", reg->memorization.max_try_count_failure) ;
//printf("\n nom=%d",reg->memorization.transfert_count) ;
  fprintf(shot_file,"%ld ;", reg->memorization.transfert_count) ;
//printf("\n nom=%d",reg->memorization.swap_count) ;
  fprintf(shot_file,"%ld ;", reg->memorization.swap_count) ;
  for (agt = 0 ; agt < inst->agent_count ; agt++)
    {
    fprintf(shot_file," %d ;",sol->capacity_left[agt]) ;
    } ;
  fprintf(shot_file, "\n") ;
  fclose(shot_file) ;
  } ;
}

