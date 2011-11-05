
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

/** function_root_name : permet de retourner le nom simple du fichier d'instance
 * @param : adresse de la chaine de caractère en retour
 * @param : adresse du nom
 * @return : rien
 *    */
static void
_function_root_name (char *root_name, char *name )
{
  char *ptr ;
  ptr=strrchr(name,'/') ;
  if (ptr != NULL)
    strcpy(root_name, ptr+1) ;;
} ;

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
  if (ponderate == _assignment)
    strcpy(f_name, "assignment") ;
} ;

/** step_schedule_name : permet de retourner le nom en clair du mode de planification
 * @param : nom en clair
 * @param : structure à examiner
 * @return : rien
 *    */
static void
_step_schedule_name (char *f_step, t_step_schedule step )
{
  if (step == STEP_SCHEDULE_UNASSIGNED )
    strcpy(f_step, "non assigné") ;
  if (step  == STEP_SCHEDULE_EQUAL  )
    strcpy(f_step, "equal") ;
  if (step  == STEP_SCHEDULE_ASCENDING_1 )
    strcpy(f_step, "ascendante 1") ;
  if (step  == STEP_SCHEDULE_ASCENDING_2 )
    strcpy(f_step, "ascendante 2") ;
  if (step  == STEP_SCHEDULE_ASCENDING_3 )
    strcpy(f_step, "ascendante 3") ;
  if (step  == STEP_SCHEDULE_DESCENDING_1 )
    strcpy(f_step, "descendante 1") ;
  if (step  == STEP_SCHEDULE_DESCENDING_2 )
    strcpy(f_step, "descendante 2") ;
  if (step  == STEP_SCHEDULE_DESCENDING_3 )
    strcpy(f_step, "descendante 3") ;
  if (step  == STEP_SCHEDULE_NORMAL_1 )
    strcpy(f_step, "normal 1") ;
  if (step  == STEP_SCHEDULE_NORMAL_2 )
    strcpy(f_step, "normal 2") ;
  if (step  == STEP_SCHEDULE_NORMAL_3 )
    strcpy(f_step, "normal 3") ;
} ;

/** ng_struct_name : permet de retourner le nom en clair de la structure de voisinage
 * @param : nom en clair
 * @param : structure à examiner
 * @return : rien
 *    */
static void
_ng_struct_name (char *f_name, t_solution_change_type ng_s )
{
  if (ng_s == SOLUTION_CHANGE_TRANSFER )
    strcpy(f_name, "TRANSFERT") ;
  if (ng_s == SOLUTION_CHANGE_SWAP )
    strcpy(f_name, "ECHANGE") ;
  if (ng_s == SOLUTION_CHANGE_MULTI_SWAP )
    strcpy(f_name, "MULTI SWAP") ;
} ;

/** neighbourhood_name : permet de retourner le nom en clair du type de probleme
 * @param : nom en clair
 * @param : méthode à examiner
 * @return : rien
 *    */
static void
_neighbourhood_name (char *f_name, t_problem_type_exploration t_ng)
{
  if (t_ng == NEIGHBOURHOOD_EXPLORATION_DETERMINIST )
    strcpy(f_name, "déterministe") ;
  if (t_ng == NEIGHBOURHOOD_EXPLORATION_STOCHASTIC)
    strcpy(f_name, "stochastique") ;
  if (t_ng == NEIGHBOURHOOD_EXPLORATION_UNASSIGNED)
    strcpy(f_name, "n.déf.") ;
} ;

/** problem_type_name : permet de retourner le nom en clair du type de probleme
 * @param : nom en clair
 * @param : méthode à examiner
 * @return : rien
 *    */
static void
_problem_type_name (char *f_name, t_problem_type t_problem)
{
  if (t_problem == MAXIMIZATION )
    strcpy(f_name, "MAX") ;
  if (t_problem == MINIMIZATION)
    strcpy(f_name, "MIN") ;
  if (t_problem == UNASSIGNED)
    strcpy(f_name, "n.déf.") ;
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
  char ng_struct_name[20] ;
  char problem_type_name[20] ;
  char ng_name[20] ;
  char temp_schedule[20] ;
  char step_schedule[20] ;
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
      _ng_struct_name(ng_struct_name, reg->memorization.ng_structure) ;
      _problem_type_name(problem_type_name, reg->memorization.problem_type) ;
//printf("\n nom=%s\n",ng_struct_name) ;
      _temp_schedule_name(temp_schedule, reg->memorization.temperature_schedule) ;
//printf("\n T° nom=%s\n",temp_schedule) ;
      _step_schedule_name(step_schedule, reg->memorization.step_schedule) ;
      _neighbourhood_name(ng_name, reg->memorization.neighbourhood_exploration) ;  
      fprintf(fic, "%s ; %s ; %d ; %d ; %d ;",inst->name , problem_type_name , inst->agent_count , inst->job_count , reg->memorization.current_solution->value) ;
//printf("\n nom=%s",inst->name) ;
      fprintf(fic, "%s ; %s ; %d ; %d ; %s ; ",
              ng_name ,step_schedule , reg->memorization.temperature_first , reg->memorization.temperature_last , temp_schedule) ;
      fprintf(fic, " %s ; %s ; %s ; ", agt_function , job_function , ng_struct_name) ;
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
  char ng_struct_name[20] ;
  char problem_type_name[20] ;
  char ng_name[20] ;
  char temp_schedule[20] ;
  char r_name[20] ;
  char step_schedule[20] ;
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
      _function_name(job_function , reg->memorization.jobponderate) ;
      _ng_struct_name(ng_struct_name, reg->memorization.ng_structure) ;
      _temp_schedule_name(temp_schedule, reg->memorization.temperature_schedule) ;
      _function_root_name(r_name , inst->name ) ;
      _problem_type_name(problem_type_name, reg->memorization.problem_type) ;
      _step_schedule_name(step_schedule, reg->memorization.step_schedule) ;
      _neighbourhood_name(ng_name, reg->memorization.neighbourhood_exploration) ;
      fprintf(shot_file, "%s ; %s ; %d ; %d ; %d ;",r_name , problem_type_name , inst->agent_count , inst->job_count , reg->memorization.current_solution->value) ;
      fprintf(shot_file, "%s ; %s ; %d ; %d ; %s ; ",
              ng_name ,step_schedule , reg->memorization.temperature_first , reg->memorization.temperature_last , temp_schedule) ;
      fprintf(shot_file, " %s ; %s ; %s ; ", agt_function , job_function , ng_struct_name) ;
      fprintf(shot_file,"%ld ;", reg->memorization.iteration_count) ;
      fprintf(shot_file,"%ld ;", reg->memorization.unavailable_count) ;
      fprintf(shot_file,"%d ;", reg->memorization.max_try_count_failure) ;
      fprintf(shot_file,"%ld ;", reg->memorization.transfert_count) ;
      fprintf(shot_file,"%ld ;", reg->memorization.swap_count) ;
      for (agt = 0 ; agt < inst->agent_count ; agt++)
        {
          fprintf(shot_file," %d ;",sol->capacity_left[agt]) ;
        } ;
      fprintf(shot_file, "\n") ;
      fclose(shot_file) ;
    } ;
}

