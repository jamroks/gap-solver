/*
This file is part of gap_solver.

gap_solver is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

gap_solver is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with gap_solver. If not, see <http://www.gnu.org/licenses/>.
*/

#include "../header/common.h"

/**
 * Add a job list at the beginning of the given linked list.
 *
 * @param head	Linked list head
 *
 * @param job	Job index
 *
 * @return	TRUE if memory successfuly allocated, FALSE otherwise
 */
t_bool
job_list_list_add_job_list (t_job_list_list * head, t_job_list * job_list)
{
  t_job_list_list * new_element, * i;
  new_element = (t_job_list_list *) malloc (sizeof (t_job_list_list)) ;
  if (NULL == new_element)
    return FALSE ;
  i = head->next ;
  head->next = new_element ;
  new_element->next = i ;
  new_element->job_list = job_list ;
  return TRUE ;
}

/**
 * Delete the linked list element containing the given job list and free its memory.
 *
 * @param head	Linked list head
 *
 * @param job	Job to remove
 *
 * @return	TRUE if found, FALSE otherwise
 */
t_bool
job_list_list_remove_job_list (t_job_list_list * head, t_job_list * job_list)
{
  t_job_list_list * i, * j ;
  i = j = head ;
  while (i = i->next)
    {
      if (i->job_list == job_list)
        {
          i = i->next ;
          free (j->next) ;
          j->next = i ;
          return FALSE ;
        }
      j = i ;
    }
  return TRUE ;
}

/**
 * Creates the linked list head,
 * and gives it the NULL value.
 */
t_job_list_list *
job_list_list_alloc_head ()
{
  t_job_list_list * head;
  if (NULL == (head = (t_job_list_list *) malloc (sizeof (t_job_list_list))))
    return NULL ;
  head->next = NULL ;
  return head ;
}

/**
 * Free the memory allocated to job element.
 * Doesn't free the linked list head.
 */
t_bool
job_list_free_list (t_job_list_list * list)
{
  t_job_list_list * elt, * tmp ;
  tmp = elt = list ;
  while (tmp = elt = tmp->next)
    free (elt) ;
}
