/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:16:08 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/02 16:45:41 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include "vector.h"
# include "map.h"
# include "object.h"

typedef int	t_bool;
#  define FALSE 0
#  define TRUE 1

typedef struct	s_hit_record
{
	t_vector    p;
	t_vector    normal;
	double      tmin;
	double      tmax;
	double      t;
	t_bool      front_face;
}				t_hit_record;

/*			ray			*/
t_ray		ray_primary(t_camera *cam, double u, double v);
t_vector	ray_color(t_ray *ray, t_object *world);
/*			hit	*/
t_bool      hit(t_object *world, t_ray *ray, t_hit_record *rec);
t_bool      hit_obj(t_object *world, t_ray *ray, t_hit_record *rec);
void    set_face_normal(t_ray *r, t_hit_record *rec);
/*			hit_object		*/
t_bool      hit_sphere(t_object *sp, t_ray *ray, t_hit_record *rec);

#endif
