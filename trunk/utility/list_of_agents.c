
/* fonction de listage des agents */
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "../header/type.h"
/* ============================ */
t_list 
list_of_agents (t_gap_instance *gap_inst)
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
