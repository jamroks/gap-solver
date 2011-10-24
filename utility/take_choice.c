
/* fonction de tirage au sort d'un élément dans la liste */
/* renvoit le rang de l'élément tiré au sort : entre 1 et nb_elt */
/* ============================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* ============================ */
#include "../header/type.h"
/* ============================ */
/* INCOMPLET
*/
t_elt 
take_choice(t_list list_of_elt)
{
int agt,job ;
float rnd_value ;
t_elt elt ;
t_list list_of_jobs ;
// une valeur aléatoire 
srand(time(NULL));
// ici non pondérée :
rnd_value = (rand() % list_of_elt.nb_elt) + 1 ;
elt=rnd_value ;
/*   ici pondérée : valeurs cumulées
rnd_value = (rand() % list_of_elt.list[nb_elt]) + 1 ;
while (rnd_value > list_of_elt.list[elt])
  { elt++ ; } ;
*/
return (t_elt) elt ;
}
