#include "../header/common.h"
short
alloc_gap_instance (t_gap_instance * instance, int agent_count, int job_count)
{
  int i;
  instance->agent_count = agent_count ;
  instance->job_count = job_count ;
  instance->capacity = (t_cost *) calloc (sizeof (t_cost), agent_count) ;
  if ( ! instance->capacity)
    return 0 ;
  instance->cost = (t_cost **) calloc (sizeof (t_cost *), agent_count) ;
  if ( ! instance->cost)
    return 0 ;
  instance->gain = (t_gain **) calloc (sizeof (t_gain *), agent_count) ;
  if ( ! instance->gain)
    return 0 ;
  for (i = 0 ; i < agent_count; i ++)
    {
      instance->cost[i] = (t_cost *) calloc (sizeof (t_cost), job_count) ;
      if ( ! instance->cost[i])
        return 0;
      instance->gain[i] = (t_gain *) calloc (sizeof (t_gain), job_count) ;
      if ( ! instance->gain[i])
        return 0;
    }
  return 1;
}

short
free_gap_instance (t_gap_instance * instance)
{
  int i;
  free (instance->capacity) ;
  for (i = 0 ; i < instance->agent_count ; i ++)
    {
      free (instance->cost[i]) ;
      free (instance->gain[i]) ;
    }
  free (instance->cost) ;
  free (instance->gain) ;
  return;
}
