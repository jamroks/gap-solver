
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
list_of_agents (t_gap_instance *gap_inst,void (*f_evaluation)())
{
t_list list_agents ;
int agt ;
for (agt=0; agt < gap_inst->agent_count ; agt++)
	{
	list_agents.list[agt]=1 ;
	} ;
return list_agents ;
}
