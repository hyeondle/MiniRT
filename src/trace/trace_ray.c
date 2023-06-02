/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:16:42 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/02 16:41:38 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/trace.h"
#include <math.h>

t_ray		ray_primary(t_camera *cam, double u, double v)
{
	t_ray   ray;

	ray.origin = cam->origin;
	ray.d_unit = vunit(vminus(vplus(cam->left_bottom, (vplus(vmult(cam->horizontal, u), vmult(cam->vertical, v)))), cam->origin));
	return (ray);
}

t_vector	ray_color(t_ray *ray, t_object *world)
{
	double  		t;
	t_vector		n;
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = INFINITY;
	if (hit(world, ray, &rec))
		return (vmult(vplus(rec.normal, vector(1, 1, 1)), 0.5));
	else
	{
		t = 0.5 * (ray->d_unit.y + 1.0);
		return (vplus(vmult(vector(1, 1, 1), 1.0 - t), vmult(vector(0.5, 0.7, 1.0), t)));
	}
}