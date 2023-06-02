/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:31:26 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/03 03:40:17 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/trace.h"
#include <math.h>

t_hit_record	record_init(void)
{
	t_hit_record	record;

	record.tmin = EPSILON;
	record.tmax = INFINITY;
	return (record);
}

t_bool      hit_sphere(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sp;
	t_vector  oc;
	double  a;
	double  half_b;
	double  c;
	double  discriminant;
	double	sqrtd;
	double	root;

	sp = obj->element;
	oc = vminus(ray->origin, sp->center);
	a = vlength_pow2(ray->d_unit);
	half_b = vdot(oc, ray->d_unit);
	c = vlength_pow2(oc) - sp->radius2;
	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
	set_face_normal(ray, rec);
	rec->albedo = obj->albedo;
	return (TRUE);
}