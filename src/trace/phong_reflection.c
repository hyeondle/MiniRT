/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <st.linsio@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 03:50:50 by hyeondle          #+#    #+#             */
/*   Updated: 2023/07/04 05:41:50 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/trace.h"
#include <math.h>

t_vector	phong_lighting(t_map *map)
{
	t_vector	light_color;
	t_object	*light;

	light_color = vector(0, 0, 0);
	light = map->light;
	while (light)	//각 광원마다 반사 계산
	{
		if (light->type == LIGHT_POINT)
			light_color = vplus(light_color, point_light_get(map, light->element));
		light = light->next;
	}
	light_color = vplus(light_color, map->ambient);	//ambient 합
	return (vmin(vmult_2(light_color, map->rec.albedo), vector(1, 1, 1))); // 광원의 합이 1 넘을 경우 1로 내려줌(맥시멈 고정)
}

t_vector	point_light_get(t_map *map, t_light *light)
{
	t_vector	diffuse;
	t_vector	light_direction;
	double		kd; // diffuese의 강도
	t_vector	specular;
	double		light_length;
	t_ray		light_ray;
	t_vector	view_direction;
	t_vector	reflect_direction;
	double		spec;
	double		ksn; //shineness value
	double		ks;	//specular strength
	double		brightness;

	light_direction = vminus(light->origin, map->rec.p);
	light_length = vlength(light_direction);
	light_ray = ray(vplus(map->rec.p, vmult(map->rec.normal, EPSILON)), light_direction);
	if (in_shadow(map->world, light_ray, light_length))
		return (vector(0, 0, 0));
	light_direction = vunit(light_direction);
	kd = fmax(vdot(map->rec.normal, light_direction), 0.0);
	diffuse = vmult(light->color, kd);
	view_direction = vunit(vmult(map->ray.d_unit, -1));
	reflect_direction = reflect(vmult(light_direction, -1), map->rec.normal);
	ksn = 64;
	ks = 0.5;
	spec = pow(fmax(vdot(view_direction, reflect_direction), 0.0), ksn);
	specular = vmult(vmult(light->color, ks), spec);
	brightness = light->brightness * LUMEN;
	return (vmult(vplus(diffuse, specular), brightness));
}

t_vector	reflect(t_vector v, t_vector n)
{
	return (vminus(v, vmult(n, vdot(v, n) * 2)));
}

t_bool	 in_shadow(t_object *objects, t_ray light_ray, double light_length)
{
	t_hit_record	record;

	record.tmin = 0;
	record.tmax = light_length;
	if (hit(objects, &light_ray, &record))
		return (TRUE);
	return (FALSE);
}