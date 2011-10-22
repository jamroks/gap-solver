short
memory_allocation_gap_instance (t_gap_instance * instance, int agent_count, int job_count)
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
memory_allocation_gap_solution (t_gap_solution * solution, int agent_count, int job_count)
{
  int i;
  solution->agent_count = agent_count ;
  solution->job_count = job_count ;
  solution->capacity_left = (t_cost *) calloc (sizeof (t_cost *), agent_count) ;
  if ( ! solution->capacity_left)
    return 0 ;
  solution->assignment = (t_bool **) calloc (sizeof (t_bool *), agent_count) ;
  if ( ! solution->assignment)
    return 0 ;
  for (i = 0 ; i < agent_count ; i ++)
    {
      solution->assignment[i] = (t_cost *) calloc (sizeof (t_cost), job_count) ;
      if ( ! solution->assignment[i])
        return 0;
    }
}

short
memory_free_gap_instance (t_gap_instance * instance)
{
  int i;
  free (instance->capacity) ;
  for (i = 0 ; i < agent_count ; i ++)
    {
      free (instance->cost[i]) ;
      free (instance->gain[i]) ;
    }
  free (instance->cost) ;
  free (instance->gain) ;
  return;
}

short
memory_free_gap_solution (t_gap_instance * solution)
{
  int i ;
  free (solution->capacity_left) ;
  for (i = 0; i < solution->agent_count; i ++)
    free (solution->assignment[i]) ;
  free (solution->assignment) ;
  return 1 ;
}
