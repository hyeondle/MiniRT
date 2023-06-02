/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:00:16 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/03 05:20:12 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"

typedef int	t_object_type;
#  define	LIGHT_POINT	0
#  define	SP			1

/*			object_list					*/
typedef struct	s_object
{
	t_object_type   type;
	void            *element;
	t_vector		albedo;
	void            *next;
}				t_object;

typedef struct	s_sphere
{
	t_vector    center;
	double      radius;
	double      radius2;
}				t_sphere;

typedef struct	s_light
{
	t_vector	origin;
	t_vector	color;
	double		brightness;
}				t_light;

/*			object_list_control			*/
t_object    *object(t_object_type type, void *element, t_vector albedo);
void        oadd(t_object **list, t_object *newo);
t_object    *olast(t_object *list);
/*			objects						*/
t_light     *light_point(t_vector origin, t_vector color, double brightness);
t_sphere    *sphere(t_vector center, double radius);

#endif
