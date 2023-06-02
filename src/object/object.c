/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:06:10 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/02 16:41:40 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/object.h"
#include <stdlib.h>

t_object    *object(t_object_type type, void *element)
{
    t_object    *new;

    if (!(new = (t_object *)malloc(sizeof(t_object))))
        return (NULL);
    new->type = type;
    new->element = element;
    new->next = NULL;
    return (new);
}

void        oadd(t_object **list, t_object *newo)
{
    t_object    *cur;

    if (*list == NULL)
    {
        *list = newo;
        return ;
    }
    cur = *list;
    while (cur->next)
        cur = cur->next;
    cur->next = newo;
}

t_object    *olast(t_object *list)
{
    if (list == NULL)
        return (NULL);
    while (list->next)
        list = list->next;
    return (list);
}
