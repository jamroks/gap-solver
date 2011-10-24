
/* fonction de traitement d'une erreur */
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "../header/type.h"
/* ============================ */
void 
unavailable(t_error error)
{
printf("Erreur irrécupérable, blocage voisinage n°%d\n",error) ; 
exit(error) ;
}
