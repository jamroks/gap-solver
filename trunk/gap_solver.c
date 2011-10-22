#include "header/common.h"

t_gap_solver_context gap_solver_context ;
t_gap_instance gap_instance ;
t_gap_solution gap_solution ;

int 
main(int argc, char ** argv)
{
  parse_cli_arguments (argc, argv, & gap_solver_context);
  gap_solver_context.get_input (
    gap_solver_context.input_file,
    & gap_instance,
    & gap_solution
  );
}
