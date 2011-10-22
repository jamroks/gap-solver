short 
read_gap(S_gap_instance *gap) ;

short 
print_results(S_gap_instance *gap_i,S_gap_solution *gap_r) ;

short 
neighbourhood(S_gap_instance *gap_inst, S_gap_solution *gap_cur, S_gap_solution *gap_next, 
                t_method method, void (*f_evaluation)() , t_elt (*f_take_choice)());

t_list 
list_of_agents(void (*f_evaluation)());

t_list
subtract_value_from_list(t_list, t_elt elt) ;

t_list
list_of_jobs_agt(t_agent agt_1, t_agent agt_2) ;

void 
unavailable(t_error err) ;

