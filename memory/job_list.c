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
 * Add a job to the given linked list.
 *
 * @param head	Linked list head
 * @param job	Job index
 */
short
add_job_to_job_list (t_job_list * head, t_elt job)
{
  t_job_list * new_element ;
  if (NULL == (new_element = (t_job_list *) malloc (sizeof (t_job_list))))
    return 0 ;
  new_element->job = job ;
  new_element->next = head->next ;
  head->next = new_element ;
  return 1 ;
}

/**
 * Removes the given job from the linked list
 * @param head	Linked list head
 * @param job	Job to remove
 */
short
remove_job_from_job_list (t_job_list * head, t_elt job)
{
  t_job_list * i, * tmp ;
  i = head ;
  while (i->next)
    {
      if (i->next->job == job)
        {
          if (tmp = i->next->next)         
            free (i->next) ;
          i->next = tmp ;
          return 1 ;
        }
    }
  return 0 ;
}

/**
 * Creates the linked list head,
 * and gives it the NULL value.
 */
t_job_list *
alloc_job_list_head ()
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
short
free_job_list (t_job_list * list)
{
  t_job_list * elt, * tmp ;
  tmp = elt = list ;
  while (tmp = elt = tmp->next)
    free (elt) ;
}

/**
 * Clone the job element from a given list.
 * Works from a given head.
 *
 * @param destination_head	Destination linked list head
 * @param source_head		Source linked list head
 */
short
clone_job_list (t_job_list * destination_head, t_job_list * source_head)
{
  t_job_list * iterator = source_head ;
  while (iterator = iterator->next)
    add_job_to_job_list (destination_head, iterator->job) ;
}
