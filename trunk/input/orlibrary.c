#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../header/type.h"
#include "memory_allocation.h"

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
