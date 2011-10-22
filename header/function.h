short 
read_gap(t_gap_instance *gap) ;

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

