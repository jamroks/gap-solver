short
instance_allocate_memory(t_gap_instance *, int, int) ;

short
solution_allocate_memory(t_gap_solution *, int, int) ;

short 
instance_free_memory(t_gap_instance *) ;

short
solution_free_memory(t_gap_solution *) ;

short 
read_orlibrary_input_file(char *, t_gap_instance *, t_gap_solution *) ;

short 
print_results(t_gap_instance *gap_i,t_gap_solution *gap_r) ;

short 
neighbourhood(t_gap_instance *gap_inst, t_gap_solution *gap_cur, t_gap_solution *gap_next, 
                t_method method, void (*f_evaluation)() , t_elt (*f_take_choice)());

t_list 
list_of_agents(void (*f_evaluation)());

t_list
subtract_value_from_list(t_list, t_elt elt) ;

t_list
list_of_jobs_agt(t_agent agt_1, t_agent agt_2) ;

void 
unavailable(t_error err) ;

