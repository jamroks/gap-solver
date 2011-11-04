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
 * Add a job at end of the given linked list.
 *
 * @param head	Linked list head
 * @param job	Job index
 */
t_bool
job_list_add_job (t_job_list * head, t_job job)
{
  t_job_list * new_element, * i;
  if (NULL == (new_element = (t_job_list *) malloc (sizeof (t_job_list))))
    return 0 ;
  i = head ;
  while (i->next)
    i = i->next ;
  i->next = new_element ;
  new_element->next = NULL ;
  new_element->job = job ;
  return 1 ;
}

/**
 * Removes the given job from the linked list
 *
 * @param head	Linked list head
 *
 * @param job	Job to remove
 */
t_bool
job_list_delete_job (t_job_list * head, t_job job)
{
  t_job_list * i, * j ;
  i = j = head ;
  while (i = i->next)
    {
      if (i->job == job)
        {
          i = i->next ;
          free (j->next) ;
          j->next = i ;
          return 1 ;
        }
      j = i ;
    }
  return 0 ;
}

/**
 * Creates the linked list head,
 * and gives it the NULL value.
 */
t_job_list *
job_list_allocate_head ()
{
  t_job_list * head;
  if (NULL == (head = (t_job_list *) malloc (sizeof (t_job_list))))
    return NULL ;
  head->next = NULL ;
  return head ;
}

/**
 * Free the memory allocated to job element.
 * Doesn't free the linked list head.
 */
t_bool
job_list_free (t_job_list * list)
{
  t_job_list * elt, * tmp ;
  tmp = elt = list ;
  while (tmp = elt = tmp->next)
    free (elt) ;
}

/**
 * Clone the job elements from a given list.
 *
 * @param destination_head	Destination linked list head
 *
 * @param source_head		Source linked list head
 */
t_bool
job_list_clone (t_job_list * destination_head, t_job_list * source_head)
{
  t_job_list * iterator = source_head ;
  while (iterator = iterator->next)
    job_list_add_job (destination_head, iterator->job) ;
}
