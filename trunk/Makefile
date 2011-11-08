CC=gcc

all: solver

solver : cli_parser cli_print_result input_orlibrary\
 memory_gap_instance memory_gap_solution memory_job_list\
 solver_solution_0 next_solution_sequential solution_evaluation\
 ini_annealing ini_execution thread_operator\
 lib_ini_parser lib_ini_parser_dictionary \
 stochastic_next_solution utility_ponderation_functions\
 utility_objective_cost configuration_allowed_annealing\
 configuration_allowed_execution configuration_validate configuration_validate_annealing\
 configuration_validate_execution step_duration step_initialization utility_memorize_solution\
 step_temperature memory_error memory_job_list_list\
 utility_solution solver_annealing solver_simple_search utility_extremum

	$(CC) gap_solver.c cli_parser.o cli_print_result.o\
 input_orlibrary.o memory_gap_instance.o memory_gap_solution.o\
 memory_job_list.o solver_solution_0.o next_solution_sequential.o\
 stochastic_next_solution.o ponderation_functions.o solution_evaluation.o\
 thread_operator.o objective_cost.o\
 ini_annealing.o ini_execution.o lib_ini_parser.o\
 lib_ini_parser_dictionary.o configuration_allowed_annealing.o\
 configuration_allowed_execution.o configuration_validate.o configuration_validate_annealing.o\
 configuration_validate_execution.o step_initialization.o memorize_solution.o\
 step_duration.o step_temperature.o memory_error.o memory_job_list_list.o\
 solution.o solver_annealing.o solver_simple_search.o extremum.o\
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

memory_job_list_list: 
	$(CC) -c memory/job_list_list.c -o memory_job_list_list.o

memory_error:
	$(CC) -c memory/error.c -o memory_error.o

solver_solution_0:
	$(CC) -c solver/solution_0.c -o solver_solution_0.o

solver_annealing:
	$(CC) -c solver/annealing.c -o solver_annealing.o

solver_simple_search:
	$(CC) -c solver/simple_search.c -o solver_simple_search.o

next_solution_sequential:
	$(CC) -c solver/next_solution_sequential.c -o next_solution_sequential.o	

stochastic_next_solution:
	$(CC) -c solver/stochastic_next_solution.c -o stochastic_next_solution.o	

utility_ponderation_functions:
	$(CC) -c utility/ponderation_functions.c -o ponderation_functions.o

utility_memorize_solution: utility/memorize_solution.c
	$(CC) -c utility/memorize_solution.c -o memorize_solution.o

utility_objective_cost: utility/objective_cost.c
	$(CC) -c utility/objective_cost.c -o objective_cost.o

utility_extremum:
	$(CC) -c utility/extremum.c -o extremum.o

utility_solution:
	$(CC) -c utility/solution.c -o solution.o

solution_evaluation:
	$(CC) -c solver/solution_evaluation.c -o solution_evaluation.o

thread_operator:
	$(CC) -c thread/operator.c -o thread_operator.o

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

