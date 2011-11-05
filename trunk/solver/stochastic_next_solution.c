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
static t_list 
_agent_list (t_gap_instance *gap_inst);

/** subtract_elt_from_list : permet d'enlever un élément dans la liste  
 * @param : adresse de la liste à examiner
 * @return : rien
 */
static void
_subtract_elt_from_list (t_list *, t_elt ) ;

/** job_agt_list : retourne la liste des taches pour un agent1 donné, acceptable par un agent2 cible 
 * @param : instance
 * @param : solution
 * @param : agent1
 * @param : agent2
 * @return : liste de taches
 */
static t_list
_job_agt_list (t_gap_instance *, t_gap_solution *, t_agent , t_agent ) ;

/** job_swap0_list : retourne la liste des taches pour un agent1 donné, sans condition 
 * @param : instance
 * @param : solution
 * @param : agent1
 * @param : agent2 (ne sert à rien pour le moment
 * @return : liste de tâches
 */
static t_list
_job_swap0_list (t_gap_instance *, t_gap_solution *, t_agent , t_agent ) ;

/** job_swap0_list : pour un agent1 et une tache job donnée, retourne la liste des taches acceptables par un agent2 
 * @param : instance
 * @param : solution
 * @param : agent1
 * @param : agent2
 * @param : tache
 * @return : liste de tâches 
 */
static t_list
_job_swap_list (t_gap_instance *, t_gap_solution *, t_agent , t_agent , t_job ) ;

/** take_choice : tirage aléatoire d'un élément dans une liste, pondéré selon une fonction 
 * @param : instance
 * @param : solution
 * @param : registre
 * @param : liste
 * @param : fonction
 * @return : un élément
 */

static t_elt
_take_choice(t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, 
            t_list *, int (*ponderate)()) ;


/* unavailable : fonction appelée pour chaque occurrence d'une impossibilité d'avoir un élement dans une liste */

static void 
_unavailable (t_error ) ;

/** increasing: fonction déterminant la meilleure tâche à trasnférer de agt1 à agt2 
 * @param : instance
 * @param : solution
 * @param : registre
 * @param : agent1
 * @param : agent2
 * @param : liste
 * @return : job
 */

static t_job
_increasing(t_gap_instance *, t_gap_solution *, t_gap_solver_registry *, t_agent , t_agent , t_list *) ;

/* fonction de calcul de la solution suivante dans un voisinage de la solution précédente */
/*
 * attention je construis la fonction au fur et à mesure en ajoutant des paramètres ..
 * 
*/

short 
stochastic_next_solution (
  t_solution_change * change,
  t_gap_instance * gap_inst,
  t_gap_solution * gap_cur, 
  t_gap_solver_registry * registry) 
{
t_list values_list ;
int agt_1 , agt_2 , job , job2 ;
int ind ;
int try_count=0 ;
t_bool new_found=FALSE ;
t_method method=registry->method ;
if (registry->verbosity == TRUE) printf("=> début de calcul de voisinage ...\n") ;
/* copie de la solution de départ vers la solution suivante , avant modification */
/* Sélection de la structure de voisinage */ 
if (registry->verbosity == TRUE) printf("=> bouclage\n") ;
while ((new_found == FALSE) && (try_count < registry->max_try_count))
{
try_count++ ;
switch (method) 
  {
  case SOLUTION_CHANGE_TRANSFER :/* selon un transfert d'une tâche entre deux agents */
      {
      if (registry->verbosity == TRUE) printf("\tméthode par transfert ...\n") ;
      /* constituer la liste pondérée des agents */
      values_list=_agent_list(gap_inst) ;
      /* tirer au sort un élément dans la liste */
      if (values_list.nb_elt == 0)
        { 
        /* pas de tâche possible : saturation de agt_2 */
        if (registry->verbosity == TRUE) printf("aucun agent 1\n") ;
        _unavailable(NO_AGT) ;
        registry->memorization.unavailable_count++ ;
        method=SOLUTION_CHANGE_SWAP ;
        break ;
        } ;      
      if (registry->verbosity == TRUE) printf("\t\ttirage au sort un agent\n") ;
      agt_1 = _take_choice(gap_inst , gap_cur , registry , &values_list , registry->agtponderate) ;
      if (registry->verbosity == TRUE) printf("\tagent origine ... %d\t" , agt_1) ;
      /* enlever agt_1 de la liste */
      if (registry->verbosity == TRUE) printf("\tretrait de l'agent ...\n") ;
      _subtract_elt_from_list(&values_list , agt_1) ;
      if (values_list.nb_elt == 0)
        { 
        // pas d'agent disponible ?
        if (registry->verbosity == TRUE) printf("aucun agent 2\n") ;
        _unavailable(NO_AGT) ;
        registry->memorization.unavailable_count++ ;
        break ;
        } ;      
      /* tirer au sort un autre agent dans la liste */
      agt_2 = _take_choice(gap_inst , gap_cur , registry , &values_list , registry->agtponderate) ;
      if (registry->verbosity == TRUE) printf("\tagent cible ... %d\t" , agt_2) ;
      /* idem pour choisir une tâche admissible de agt_1 vers agt_2 */
      values_list=_job_agt_list(gap_inst , gap_cur , agt_1 , agt_2) ;
      if (values_list.nb_elt == 0)
        { 
        // pas de tâche possible : saturation de agt_2 
        if (registry->verbosity == TRUE) printf("\n mal barré\n") ;
        _unavailable(NO_JOB) ;
        /* CAS A VOIR : VOISINAGE VIDE ! */
        registry->memorization.unavailable_count++ ;
        method=SOLUTION_CHANGE_SWAP ;
        break ;
        }
      else
        {
        /* tirer au sort un élément dans la liste ou montée */
        if (registry->verbosity == TRUE) printf("\n\ttirage au sort d'une tâche parmi %d...\n",values_list.nb_elt) ;
        if (MONTEE) 
           {
           /* choisir la tâche qui rapporte le plus  */
           job = _increasing(gap_inst , gap_cur , registry , agt_1 , agt_2 , &values_list) ;
           }
        else
           {
           job = _take_choice(gap_inst , gap_cur , registry , &values_list , registry->jobponderate) ;
           } ;
        if (registry->verbosity == TRUE) printf("\t tache n°%d.\n" , job) ;
        /* transférer la tâche de agt_1 vers agt_2 */
        change->type= SOLUTION_CHANGE_TRANSFER ;
        change->contents.transfer.source=agt_1 ;
        change->contents.transfer.destination=agt_2 ;
        change->contents.transfer.job=job ;
        change->delta_value= gap_inst->gain[agt_2][job] - gap_inst->gain[agt_1][job];
        new_found=TRUE ;
        registry->memorization.transfert_count++ ;
        } ;      
      if (registry->verbosity == TRUE) printf("\tfin de méthode par transfert ...\n") ;
      } ;
      break ;
  case SOLUTION_CHANGE_SWAP :  /* selon un transfert d'une tâche entre deux agents */
      {
      if (registry->verbosity == TRUE) printf("\tméthode par SWAP ...\n") ;
      /* constituer la liste pondérée des agents */
      values_list=_agent_list(gap_inst) ;
      /* tirer au sort un élément dans la liste */
      if (values_list.nb_elt == 0)
        { 
        /* pas de tâche possible : saturation de agt_2 */
        if (registry->verbosity == TRUE) printf("aucun agent 1\n") ;
        _unavailable(NO_AGT) ;
        registry->memorization.unavailable_count++ ;
        method=SOLUTION_CHANGE_SWAP ;
        break ;
        } ;      
      agt_1 = _take_choice(gap_inst , gap_cur , registry , &values_list , registry->agtponderate) ;
      if (registry->verbosity == TRUE) printf("\tagent origine ... %d\t" , agt_1) ;
      /* enlever agt_1 de la liste */
      if (registry->verbosity == TRUE) printf("\tretrait de l'agent ...\n") ;
      _subtract_elt_from_list(&values_list , agt_1) ;
      if (values_list.nb_elt == 0)
        { 
        // pas d'agent disponible ?
      if (registry->verbosity == TRUE) printf("aucun agent 2\n") ;
        _unavailable(NO_AGT) ;
        registry->memorization.unavailable_count++ ;
        break ;
        } ;      
      /* tirer au sort un autre agent dans la liste */
      agt_2 = _take_choice(gap_inst , gap_cur , registry , &values_list , registry->agtponderate) ;
      if (registry->verbosity == TRUE) printf("\tagent cible ... %d\t" , agt_2) ;
      /* idem pour choisir une tâche chez agent 1 */
      if (agt_1 == agt_2) printf("bug negatif agent swap\n") ;
      values_list=_job_swap0_list(gap_inst , gap_cur , agt_1 , agt_2) ; //agt2 ne sert à rien
      if (values_list.nb_elt == 0)
        { 
        // pas de tache ?
        if (registry->verbosity == TRUE) printf("\n mal barré20\n") ;
        _unavailable(NO_JOB) ;
        /* CAS A VOIR : VOISINAGE VIDE ! */
        registry->memorization.unavailable_count++ ;
        method=SOLUTION_CHANGE_SWAP ;
        break ;
        };
      /* tirer au sort une tache à échanger */
      job = _take_choice(gap_inst , gap_cur , registry , &values_list , registry->jobponderate) ;
      if (registry->verbosity == TRUE) printf("\t tache n°%d.\n" , job) ;
      /* idem pour choisir une tâche admissible chez agent 2 */
      values_list=_job_swap_list(gap_inst , gap_cur , agt_1 , agt_2 , job) ;
      if (values_list.nb_elt == 0)
        { 
        // pas de tâche possible : agent sans tache
        if (registry->verbosity == TRUE) printf("\n mal barré21\n") ;
        _unavailable(NO_JOB) ;
        /* CAS A VOIR : VOISINAGE VIDE ! */
        registry->memorization.unavailable_count++ ;
        method=SOLUTION_CHANGE_SWAP ;
        break ;
        };
      /* tirer au sort une seconde tache à échanger */
      if (registry->verbosity == TRUE) printf("\ttirage au sort d'une tâche ...\n") ;
      job2 = _take_choice(gap_inst , gap_cur , registry , &values_list , registry->jobponderate) ;
      if (registry->verbosity == TRUE) printf("\t tache n°%d.\n" , job) ;
      /* faire l'échange la tâche de agt_1 et agt_2 */
      if (registry->verbosity == TRUE) printf("\nSWAP:: agt=%d(%d)  pour job=%d(%d) // agt =%d(%d) pour job=%d(%d)\n",
          agt_1,gap_cur->capacity_left[agt_1], job, gap_inst->cost[agt_1][job], 
          agt_2,gap_cur->capacity_left[agt_2], job2, gap_inst->cost[agt_2][job2]) ; 
      change->type= SOLUTION_CHANGE_SWAP ;
      change->contents.swap.source=agt_1 ;
      change->contents.swap.destination=agt_2 ;
      change->contents.swap.source_swapped_job=job ;
      change->contents.swap.destination_swapped_job=job2 ;
      change->delta_value= gap_inst->gain[agt_2][job] - gap_inst->gain[agt_1][job] + gap_inst->gain[agt_1][job2] - gap_inst->gain[agt_2][job2] ;
      new_found=TRUE ;
      registry->memorization.swap_count++ ;
      if (registry->verbosity == TRUE) printf("\tfin de méthode par échange ...\n") ;
      } ;
      break ;
  case SOLUTION_CHANGE_MULTI_SWAP :  /* selon un transfert d'une tâche entre plusieurs agents */
      {
      } ;
      break ;
  default :  /* cas d'un bug */
    {
    printf("bug n°1") ;
    return(FALSE) ;
    } ;
    break ;
  } ;
} ; // fin de boucle sur récidive en cas de blocage
if (try_count == registry->max_try_count)
  {
  registry->memorization.max_try_count_failure++ ;
  return FALSE ;
  } ;
return TRUE ;
if (registry->verbosity == TRUE) printf("fin voisinage.\n") ;
}

/* fonction de listage des agents */
static t_list 
_agent_list (t_gap_instance *gap_inst)
{
t_list list_agents ;
int agt ;
int nb_elt=0 ;
for (agt=0; agt < gap_inst->agent_count ; agt++)
  {
  list_agents.list[nb_elt++]=agt ;
  } ;
list_agents.nb_elt=gap_inst->agent_count ;
return list_agents ;
}


/* fonction déterminant la meilleur tâche à transférer entre 2 agents */
static t_job
_increasing(t_gap_instance *inst, t_gap_solution *sol, t_gap_solver_registry *reg, t_agent agt_1 , t_agent agt_2 , t_list *list_of_values) 
{
int job=NO_VALUE ;
int n_elt ;
t_job best_job=NO_VALUE ;
t_gain value ;
t_gain best_value=0 ;

//printf("Montée sur %d élts  de %d à %d \n",list_of_values->nb_elt,agt_1,agt_2) ;
for (n_elt=0; n_elt < list_of_values->nb_elt; n_elt++)
  {
  job=list_of_values->list[n_elt] ;
//printf("\njob n° %d\t",job); 
  value = inst->gain[agt_2][job] - inst->gain[agt_1][job] ;
//printf("value %d - %d = %d\t",inst->gain[agt_2][job] ,inst->gain[agt_1][job] , value);
  if (reg->problem_type == MAXIMIZATION)
    {
//printf("en maxi ") ;
    if ((best_job == NO_VALUE) || (value >= best_value))
      {
      best_job = job ;
      best_value = value ;
//printf("affectation MAXI\n") ;
      } ;
    }
  else
    {
    if (reg->problem_type == MINIMIZATION)
      {
//printf("en mini %d  ",job) ;
      if ((best_job == NO_VALUE) || (value <= best_value))
        {
        best_job = job ;
        best_value = value ;
//printf("affectation MINI\n") ;
        } ;
      } ;
    } ;
  } ;
//best_job=list_of_values->list[0] ;
if (reg->verbosity == TRUE) printf("\nmontée/descente sur %d élts :: %d - %d meilleur=%d job=%d\n",
        list_of_values->nb_elt, inst->gain[agt_2][best_job],inst->gain[agt_1][best_job], best_value, best_job) ;
if (best_job == NO_VALUE) printf("NO_VALUE !\n") ;	
//printf("fin de Montée ->%d\n",best_job) ;
return (t_job) best_job ;
}

/* fonction de listage des taches pour un agent avec plafond */
static t_list 
_job_agt_list(t_gap_instance *inst, t_gap_solution *gap, t_agent agt_1, t_agent agt_2)
{
t_job job ;
t_list job_list ;
//printf("\njob_agt_list %d -> %d\n",agt_1,agt_2) ;
job_list.nb_elt=0 ;
for (job=0; job < gap->job_count; job++)
  {
  if (gap->assignment[agt_1][job] == 1)
    {
    // il faut de la place ...
    if (inst->cost[agt_2][job] <= gap->capacity_left[agt_2])
       {
       // ajout de la tâche dans la liste
       job_list.list[job_list.nb_elt++]=job ;
       } ;
    } ;
  } ;
//for (job=0 ; job < job_list.nb_elt ; job++)
//   printf("[%d]->%d\n",job,job_list.list[job]) ;
//printf("\n") ;
return (t_list) job_list ;
}

/* fonction de listage des taches pour un agent SANS plafond */
static t_list 
_job_swap0_list(t_gap_instance *inst, t_gap_solution *gap, t_agent agt_1, t_agent agt_2)
{
t_job job ;
t_list job_list ;
job_list.nb_elt=0 ;
//printf("\t extraction de taches de l'agent %d pour l'agent %d\n", agt_1, agt_2) ;
for (job=0; job < gap->job_count; job++)
  {
  if (gap->assignment[agt_1][job] == 1)
    {
    // il faut de la place ...
       // ajout de la tâche dans la liste
//       printf("ajout de %d pour un cout de %d\n",job,inst->cost[agt_2][job]) ;
       job_list.list[job_list.nb_elt++]=job ;
    } ;
  } ;
return (t_list) job_list ;
}

/* fonction de listage des taches pour un échange de job1 (venant de agt1) */
static t_list 
_job_swap_list(t_gap_instance *inst, t_gap_solution *gap, t_agent agt_1, t_agent agt_2 , t_job job_1)
{
t_job job ;
t_list job_list ;
job_list.nb_elt=0 ;
//printf("\t extraction de taches de l'agent %d pour l'agent %d\n", agt_1, agt_2) ;
for (job=0; job < gap->job_count; job++)
  {
  if (gap->assignment[agt_2][job] == 1)
    {
    // il faut de la place ...
    if ((inst->cost[agt_1][job] <= (gap->capacity_left[agt_1]+inst->cost[agt_1][job_1])) 
        && (inst->cost[agt_2][job_1] <= (gap->capacity_left[agt_2]+inst->cost[agt_2][job]))) 
       {
       // ajout de la tâche dans la liste
//       printf("ajout de %d pour un cout de %d\n",job,inst->cost[agt_2][job]) ;
       job_list.list[job_list.nb_elt++]=job ;
       } ;
    } ;
  } ;
return (t_list) job_list ;
}

/* fonction pour enlever un élément d'une liste */
static void 
_subtract_elt_from_list(t_list *list_of_values,t_elt agt_1) 
{
int n_elt=0 ;
while (list_of_values->list[n_elt] != agt_1)
  {
  n_elt++ ;
  } ;
// décalage des suivants 
while (n_elt < list_of_values->nb_elt)
  {
  list_of_values->list[n_elt] = list_of_values->list[n_elt+1] ;
  n_elt++ ;
  } ;
list_of_values->nb_elt-- ;
}

/* fonction de tirage au sort d'un élément dans la liste */
/* renvoit le rang le n° de l'élément tiré au sort : entre 1 et nb_elt */
#define max(a,b) (a<=b?b:a)
static t_elt 
_take_choice(t_gap_instance *inst, t_gap_solution *sol, t_gap_solver_registry *reg,
            t_list *list_of_elt,int (*ponderate)())
{
int n_elt , sum=0 ;
int rnd_value ;
t_elt elt ;
t_list ponderate_list ;
if (list_of_elt->nb_elt <=0) printf("take choice : ZERO\n") ;
if (reg->verbosity == TRUE) printf("\t\ttake_choice ...%d élts\n",list_of_elt->nb_elt) ;
// calculer la ponderation pour chaque élément de la liste
for (n_elt=0; n_elt < list_of_elt->nb_elt; n_elt++)
  {
  if (reg->verbosity == TRUE) printf("\t\t[%d]",n_elt) ;
  elt = list_of_elt->list[n_elt] ;
  sum+=ponderate(inst , sol , reg , elt) ;
  ponderate_list.list[n_elt]=sum ;  
  if (reg->verbosity == TRUE) printf(" objet n°%d  pondération cumulée=%d\n",elt,ponderate_list.list[n_elt]) ;
  } ;
ponderate_list.nb_elt=list_of_elt->nb_elt ;
// une valeur aléatoire 
// ici pondérée : valeurs cumulées
if (reg->verbosity == TRUE) printf("\t\taléatoire") ;
n_elt=list_of_elt->nb_elt ;
if (reg->verbosity == TRUE) printf("\t avec %d élts\n",n_elt) ;
  if (ponderate_list.list[n_elt-1] == 0) 
  { 
  rnd_value = rand() % n_elt ;
  if (reg->verbosity == TRUE) printf("\t\tlinéaire ...%d",rnd_value) ;
  n_elt=rnd_value ;
  }
  else
  {
  rnd_value = (rand() % ponderate_list.list[n_elt-1]) + 1 ;
  if (reg->verbosity == TRUE) printf("\t\tpondérée ...%d sur %d",rnd_value,ponderate_list.list[n_elt-1]) ;
  n_elt=0;
  while (rnd_value > ponderate_list.list[n_elt])
    { n_elt++ ; } ;
  } ;
if (reg->verbosity == TRUE) printf("\t\tvaleur aléatoire position=%d \n",n_elt) ;
return (t_elt) list_of_elt->list[n_elt] ;
}

/* fonction de traitement d'une erreur */
static void 
_unavailable(t_error error)
{
//printf("Erreur irrécupérable, blocage voisinage n°%d\n",error) ; 
//exit(error) ;
}

void ROMAIN_neighbourhood_stochastic_try (
  t_gap_solution * solution,
  t_gap_instance * instance,
  t_gap_solver_registry * registry)
{
  int test_b=100 ;
  t_bool solution_found ;
  t_solution_change change ;
//   printf("\n______________________________________\ndebut de paramétrage pour voisinage\n") ;
registry->problem_type = MINIMIZATION  ;
registry->verbosity = FALSE  ;
if (registry->problem_type == MAXIMIZATION)
  {
  printf("problème en MAXIMISATION\n") ;
  }
else
  {
  printf("problème en MINIMISATION\n") ;
  } ;
printf("ponderation agent= _capacity_left\n") ;
printf("ponderation job  = _uniform\n") ;
registry->agtponderate=&_capacity_left ;
registry->jobponderate=&_uniform ;
printf("méthode = TRANSFERT\n") ;
registry->method=SOLUTION_CHANGE_TRANSFER ;
registry->memorization.unavailable_count=0 ;
printf("échec voisinage à %d\n",registry->max_try_count) ;
registry->memorization.max_try_count_failure = 0 ;
printf("Le voisinage sera ") ;
if (registry->verbosity) printf("bavard\n") ;
if (! registry->verbosity) printf("silencieux\n") ;
printf("fin de paramétrage pour voisinage\n") ;
//  test voisinage stochastique
srand(time(NULL));
printf("solution initiale:: %d\n",solution->value) ;
printf("\n pour %d tests \n", test_b) ;
  while (test_b > 0)
    {
    registry->memorization.iteration_count++ ;
    solution_found=stochastic_next_solution ( & change ,  instance ,  solution,  registry) ;
    if (solution_found == TRUE)
      {
      printf("%3d variation proposée %d\t",test_b,change.delta_value) ;
      if (change.type == SOLUTION_CHANGE_TRANSFER) printf("par transfert\tde l'agent %d à l'agent %d de la tâche %d\t",
          change.contents.transfer.source , change.contents.transfer.destination , change.contents.transfer.job) ;
      if (change.type == SOLUTION_CHANGE_SWAP) printf("par échange\t" ) ;
      if (((change.delta_value > 0) && (registry->problem_type == MAXIMIZATION))
         || ((change.delta_value < 0) && (registry->problem_type == MINIMIZATION)))
        {
        printf("suivie\t") ;
        solution_apply_change( instance , solution , & change) ;
        printf("mémorisation pour %ld\n",solution->value) ;
        memorize_solution( instance , solution , registry ) ;     
        }
      else
        {
        printf("abandonnée\n") ;
        } ;
      test_b-- ;
      }
    else
      {
      printf(" pas de solution\n",test_b) ;
      } ;
    } ;
  printf(" nb blocages   =%d\n", registry->memorization.unavailable_count) ;
  printf(" nb échec      =%d\n", registry->memorization.max_try_count_failure) ;
  printf(" nb transferts =%d\n", registry->memorization.transfert_count) ;
  printf(" nb swap       =%d\n", registry->memorization.swap_count) ;
  memorize_best( instance , solution , registry ) ;     

//  

}






