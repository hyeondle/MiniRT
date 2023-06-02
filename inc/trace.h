/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:16:08 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/03 05:00:20 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include "vector.h"
# include "viewport.h"
# include "object.h"

typedef int	t_bool;
#  define FALSE 0
#  define TRUE 1

#  define EPSILON	1e-6 // 0.000001
#  define LUMEN		3

typedef struct	s_hit_record
{
	t_vector	p;
	t_vector	normal;
	double		tmin;
	double		tmax;
	double		t;
	t_bool		front_face;
	t_vector	albedo;
}				t_hit_record;

typedef struct	s_map
{
	t_canvas		canvas;
	t_camera		camera;
	t_object		*world;
	t_object		*light;
	t_vector		ambient;
	t_ray			ray;
	t_hit_record	rec;
}				t_map;

t_map			*map_init(void);
/*			ray			*/
t_ray			ray_primary(t_camera *cam, double u, double v);
t_vector		ray_color(t_map	*map);
/*			hit			*/
t_hit_record	record_init(void);
t_bool			hit(t_object *world, t_ray *ray, t_hit_record *rec);
t_bool			hit_obj(t_object *world, t_ray *ray, t_hit_record *rec);
void			set_face_normal(t_ray *r, t_hit_record *rec);
/*			hit_object		*/
t_bool			hit_sphere(t_object *sp, t_ray *ray, t_hit_record *rec);
/*			phong_lighting	*/
t_vector		phong_lighting(t_map *map); // ambient
t_vector		point_light_get(t_map *map, t_light *light); // diffuse
t_vector		reflect(t_vector v, t_vector n);
t_bool			in_shadow(t_object *objects, t_ray light_ray, double light_length);

#endif
