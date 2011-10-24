CC=gcc

all: solver

solver : cli_parser cli_print_result input_orlibrary\
 memory_gap_instance memory_gap_solution solver_solution_0\
 neighbourhood_determinist solution_evaluation thread_countdown\
 thread_temperature
	$(CC) -D_REENTRANT gap_solver.c cli_parser.o cli_print_result.o\
 input_orlibrary.o memory_gap_instance.o memory_gap_solution.o\
 solver_solution_0.o neighbourhood_determinist.o solution_evaluation.o\
 thread_countdown.o thread_temperature.o\
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

solver_solution_0:
	$(CC) -c solver/solution_0.c -o solver_solution_0.o

neighbourhood_determinist:
	$(CC) -c solver/neighbourhood_determinist.c -o neighbourhood_determinist.o	

solution_evaluation:
	$(CC) -c solver/solution_evaluation.c -o solution_evaluation.o

thread_countdown:
	$(CC) -c thread/countdown.c -o thread_countdown.o

thread_temperature:
	$(CC) -c thread/temperature.c -o thread_temperature.o
clean :
	rm *\.o

