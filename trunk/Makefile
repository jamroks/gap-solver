CC=gcc

all: solver

solver : cli_parser cli_print_result input_orlibrary\
 memory_gap_instance memory_gap_solution memory_job_list\
 solver_solution_0 neighbourhood_determinist solution_evaluation\
 ini_annealing ini_execution thread_countdown\
 thread_temperature lib_ini_parser lib_ini_parser_dictionary \
 stochastic_next_solution utility_list_of_agents utility_take_choice\
 utility_unavailable utility_subtract_elt_from_list utility_list_of_jobs_agt\
 utility_uniform utility_capacity utility_capacity_left utility_list_of_jobs_swap\
 utility_list_of_jobs_swap0 utility_objective_cost configuration_allowed_annealing\
 configuration_allowed_execution configuration_validate configuration_validate_annealing\
 configuration_validate_execution step_duration step_initialization utility_memorize_solution\
 step_temperature

	$(CC) -D_REENTRANT gap_solver.c cli_parser.o cli_print_result.o\
 input_orlibrary.o memory_gap_instance.o memory_gap_solution.o\
 memory_job_list.o solver_solution_0.o neighbourhood_determinist.o\
 stochastic_next_solution.o solution_evaluation.o\
 thread_countdown.o thread_temperature.o list_of_agents.o take_choice.o\
 unavailable.o subtract_elt_from_list.o list_of_jobs_swap.o list_of_jobs_agt.o uniform.o\
 capacity.o capacity_left.o list_of_jobs_swap0.o objective_cost.o\
 ini_annealing.o ini_execution.o lib_ini_parser.o\
 lib_ini_parser_dictionary.o configuration_allowed_annealing.o\
 configuration_allowed_execution.o configuration_validate.o configuration_validate_annealing.o\
 configuration_validate_execution.o step_initialization.o memorize_solution.o\
 step_duration.o step_temperature.o\
 -o gap_solver -lm -lpthread ; make clean

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

utility_uniform: utility/uniform.c
	$(CC) -c utility/uniform.c -o uniform.o

utility_unavailable: utility/unavailable.c
	$(CC) -c utility/unavailable.c -o unavailable.o

utility_memorize_solution: utility/memorize_solution.c
	$(CC) -c utility/memorize_solution.c -o memorize_solution.o

utility_objective_cost: utility/objective_cost.c
	$(CC) -c utility/objective_cost.c -o objective_cost.o

solution_evaluation:
	$(CC) -c solver/solution_evaluation.c -o solution_evaluation.o

thread_countdown:
	$(CC) -c thread/countdown.c -o thread_countdown.o

thread_temperature:
	$(CC) -c thread/temperature.c -o thread_temperature.o

ini_annealing:
	$(CC) -c ini/annealing.c -o ini_annealing.o

ini_execution:
	$(CC) -c ini/execution.c -o ini_execution.o

configuration_allowed_annealing:
	$(CC) -c configuration/allowed_annealing.c -o configuration_allowed_annealing.o

configuration_allowed_execution:
	$(CC) -c configuration/allowed_execution.c -o configuration_allowed_execution.o

configuration_validate:
	$(CC) -c configuration/validate.c -o configuration_validate.o

configuration_validate_annealing:
	$(CC) -c configuration/validate_annealing.c -o configuration_validate_annealing.o

configuration_validate_execution:
	$(CC) -c configuration/validate_execution.c -o configuration_validate_execution.o

lib_ini_parser_dictionary:
	$(CC) -c lib/iniparser/dictionary.c -o lib_ini_parser_dictionary.o

step_duration:
	$(CC) -c step/duration.c -o step_duration.o

step_initialization:
	$(CC) -c step/initialization.c -o step_initialization.o

step_temperature:
	$(CC) -c step/temperature.c -o step_temperature.o
lib_ini_parser:
	$(CC) -c lib/iniparser/iniparser.c -o lib_ini_parser.o

clean :
	rm *\.o

