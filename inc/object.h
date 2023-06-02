/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:00:16 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/02 16:41:43 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"

typedef int	t_object_type;
#  define SP 0

/*			object_list					*/
typedef struct	s_object
{
	t_object_type   type;
	void            *element;
	void            *next;
}				t_object;

typedef struct	s_sphere
{
	t_vector    center;
	double      radius;
	double      radius2;
}				t_sphere;

/*			object_list_control			*/
t_object    *object(t_object_type type, void *element);
void        oadd(t_object **list, t_object *newo);
t_object    *olast(t_object *list);
/*			objects						*/
t_sphere    *sphere(t_vector center, double radius);

#endif
