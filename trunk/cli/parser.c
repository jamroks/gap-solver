#include "../header/common.h"

short
parse_cli_arguments (int argc, char ** argv, t_gap_solver_context *gap_solver_context)
{
  FILE file;
  if (argc < 2)
    {
      fprintf (stderr, "%s", "un nom de fichier est attendu\n") ;
      exit (1) ;
    }
  gap_solver_context->input_file = argv[argc - 1] ;
  if (NULL == (file = fopen (gap_solver_context->input_file)))
    {
      fprintf (
        stderr,
        "%s : \"%s\"",
        "fichier introuvable : ",
        gap_solver_context->input_file
      ) ;
      exit (1) ;
    }
  fclose (file);
  gap_solver_context->get_input = & read_orlibrary_input_file ;
}

char *
get_usage()
{
/*
--duration 
--iterations
--start-temperature
--temperature-decrease-function
--neighborhood
--verbose
--Version
--about
--help
*/
}
