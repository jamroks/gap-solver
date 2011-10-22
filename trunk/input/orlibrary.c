#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../header/type.h"

short
instance_allocate_memory(t_gap_instance *, int, int);

short 
read_gap(t_gap_instance * instance, char * file_name)
{
  FILE *file ;
  int value ;
  int agent, job ;
  file = fopen(file_name, "rt"); 
  if (file == NULL)
    return 1 ; 
  strcpy (instance->name, file_name) ;
  fscanf (file, "%d", & instance->agent_count);
  fscanf (file, "%d", & instance->job_count);
  instance_allocate_memory(instance, instance->agent_count, instance->job_count);
  for (agent = 0; agent < instance->agent_count; agent ++)
    {
      for (job = 0; job < instance->job_count; job ++)
      {
        fscanf (file, "%d", &value) ;
        instance->cost[agent][job] = value ;
      }
    };
  for (agent = 0; agent < instance->agent_count ; agent++)
    {
      for (job = 0 ; job < instance->job_count ; job++)
      {
        fscanf (file, "%d", &value);
        instance->gain[agent][job] = value ;
      }
    };
  for (agent = 0 ; agent < instance->agent_count ; agent++)
    {
      fscanf (file, "%d", &value);
      instance->capacity[agent] = value ;
    };
  fclose (file) ;
  return 0 ;
}

short
instance_allocate_memory(t_gap_instance * instance, int agent_count, int job_count)
{
  int i;
  // Memory allocation
  instance->agent_count = agent_count;
  instance->job_count = job_count;
  if ( ! instance->capacity)
    return 0;
  instance->capacity = calloc (sizeof(t_cost*), instance->agent_count);
  instance->cost = (t_cost**) calloc (sizeof(t_cost*), instance->agent_count);
  if ( ! instance->cost)
    return 0;
  instance->gain = (t_gain**) calloc (sizeof(t_gain*), instance->agent_count);
  if ( ! instance->gain)
    return 0;
  for (i = 0; i < instance->agent_count; i ++)
    {
      instance->cost[i] = (t_cost*) calloc (sizeof(t_cost), instance->job_count);
      if ( ! instance->cost[i])
        return 0;
      instance->gain[i] = (t_gain*) calloc (sizeof(t_gain), instance->job_count);
      if ( ! instance->gain[i])
        return 0;
    }
  return 1;
}

int main()
{
  t_gap_instance instance;
  read_gap(&instance, "fixtures/a05100");
  return 0;
}
