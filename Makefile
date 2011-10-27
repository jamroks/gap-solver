CC=gcc

all: solver

solver : cli_parser cli_print_result input_orlibrary\
 memory_gap_instance memory_gap_solution memory_job_list\
 solver_solution_0 neighbourhood_determinist solution_evaluation\
 configuration_annealing thread_countdown\
 thread_temperature lib_ini_parser lib_ini_parser_dictionary \
 stochastic_next_solution utility_list_of_agents utility_take_choice\
 utility_unavailable utility_subtract_elt_from_list utility_list_of_jobs_agt\
 utility_equity utility_capacity utility_capacity_left utility_list_of_jobs_swap\
 utility_list_of_jobs_swap0 utility_objective_cost
	$(CC) -D_REENTRANT gap_solver.c cli_parser.o cli_print_result.o\
 input_orlibrary.o memory_gap_instance.o memory_gap_solution.o\
 memory_job_list.o solver_solution_0.o neighbourhood_determinist.o\
 stochastic_next_solution.o solution_evaluation.o\
 thread_countdown.o thread_temperature.o list_of_agents.o take_choice.o\
 unavailable.o subtract_elt_from_list.o list_of_jobs_swap.o list_of_jobs_agt.o equity.o\
 capacity.o capacity_left.o list_of_jobs_swap0.o objective_cost.o\
 configuration_annealing.o lib_ini_parser.o lib_ini_parser_dictionary.o\
 -o gap_solver -lm -lpthread; make clean

cli_parser : cli/parser.c
	$(CC) -c cli/parser.c -o cli_parser.o

cli_print_result : cli/print_result.c
	$(CC) -c cli/print_result.c -o cli_print_result.o

input_orlibrary : input/orlibrary.c
	$(CC) -c input/orlibrary.c -o input_orlibrary.o

memory_gap_instance : 
	$(CC) -c memory/gap_instance.c -o memory_gap_instance.o

memory_gap_solution : 
	$(CC) -c memory/gap_solution.c -o memory_gap_solution.o

memory_job_list: 
	$(CC) -c memory/job_list.c -o memory_job_list.o

solver_solution_0:
	$(CC) -c solver/solution_0.c -o solver_solution_0.o

neighbourhood_determinist:
	$(CC) -c solver/neighbourhood_determinist.c -o neighbourhood_determinist.o	

stochastic_next_solution:
	$(CC) -c solver/stochastic_next_solution.c -o stochastic_next_solution.o	

utility_list_of_jobs_swap0: utility/list_of_jobs_swap0.c
	$(CC) -c utility/list_of_jobs_swap0.c -o list_of_jobs_swap0.o	

utility_list_of_jobs_swap: utility/list_of_jobs_swap.c
	$(CC) -c utility/list_of_jobs_swap.c -o list_of_jobs_swap.o	

utility_list_of_jobs_agt: utility/list_of_jobs_agt.c
	$(CC) -c utility/list_of_jobs_agt.c -o list_of_jobs_agt.o	

utility_list_of_agents: utility/list_of_agents.c
	$(CC) -c utility/list_of_agents.c -o list_of_agents.o	

utility_take_choice: utility/take_choice.c
	$(CC) -c utility/take_choice.c -o take_choice.o

utility_subtract_elt_from_list: utility/subtract_elt_from_list.c
	$(CC) -c utility/subtract_elt_from_list.c -o subtract_elt_from_list.o

utility_capacity: utility/capacity.c
	$(CC) -c utility/capacity.c -o capacity.o

utility_capacity_left: utility/capacity_left.c
	$(CC) -c utility/capacity_left.c -o capacity_left.o

utility_equity: utility/equity.c
	$(CC) -c utility/equity.c -o equity.o

utility_unavailable: utility/unavailable.c
	$(CC) -c utility/unavailable.c -o unavailable.o

utility_objective_cost: utility/objective_cost.c
	$(CC) -c utility/objective_cost.c -o objective_cost.o

solution_evaluation:
	$(CC) -c solver/solution_evaluation.c -o solution_evaluation.o

thread_countdown:
	$(CC) -c thread/countdown.c -o thread_countdown.o

thread_temperature:
	$(CC) -c thread/temperature.c -o thread_temperature.o
configuration_annealing:
	$(CC) -c configuration/annealing.c -o configuration_annealing.o

lib_ini_parser_dictionary:
	$(CC) -c lib/iniparser/dictionary.c -o lib_ini_parser_dictionary.o

lib_ini_parser:
	$(CC) -c lib/iniparser/iniparser.c -o lib_ini_parser.o

clean :
	rm *\.o

