CC=gcc

all: solver
solver : cli_parser input_orlibrary memory_gap_instance memory_gap_solution solver_solution_0
	$(CC) gap_solver.c cli_parser.o input_orlibrary.o memory_gap_instance.o memory_gap_solution.o
cli_parser : cli/parser.c
	$(CC) -c cli/parser.c -o cli_parser.o
input_orlibrary : input/orlibrary.c
	$(CC) -c input/orlibrary.c -o input_orlibrary.o
memory_gap_instance : 
	$(CC) -c memory/gap_instance.c -o memory_gap_instance.o
memory_gap_solution : 
	$(CC) -c memory/gap_solution.c -o memory_gap_solution.o
solver_solution_0:
	$(CC) -c solver/solution_0.c -o solver_solution_0.o
clean :
	rm *\.o

