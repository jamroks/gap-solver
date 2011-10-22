#include "../header/common.h"
#include "../header/type.h"
#include "../header/function.h"

short 
read_orlibrary_input_file(char * file_name, t_gap_instance * instance, t_gap_solution * solution)
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
  memory_allocation_gap_instance (instance, instance->agent_count, instance->job_count);
  memory_allocation_gap_solution (solution, instance->agent_count, instance->job_count);
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
