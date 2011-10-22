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

short
solution_allocate_memory(t_gap_solution * solution)
{

}
