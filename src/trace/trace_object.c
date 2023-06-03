/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:31:26 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/03 17:59:19 by hyeondle         ###   ########.fr       */
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

t_bool hit_plane(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	t_plane		*pl;
	double		t;
	t_vector	p;
	double		denominator;
	t_vector	oc;

	pl = obj->element;
	denominator = vdot(pl->normal, ray->d_unit);
	if (denominator > EPSILON || denominator < -EPSILON)
	{
		oc = vminus(pl->origin, ray->origin);
		t = vdot(oc, pl->normal) / denominator;
		if (t > rec->tmin && t < rec->tmax)
		{
			rec->t = t;
			rec->p = ray_at(ray, t);
			rec->normal = vunit(pl->normal);
			set_face_normal(ray, rec);
			rec->albedo = obj->albedo;
			return (TRUE);
		}
	}
	return (FALSE);
}

t_bool	hit_cylinder(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	double a, b, c, discriminant;
	double t1, t2;

	cy = obj->element;
	t_vector oc = vminus(ray->origin, cy->origin);
	a = vdot(ray->d_unit, ray->d_unit) - pow(vdot(ray->d_unit, cy->axis), 2);
	b = 2 * (vdot(ray->d_unit, oc) - vdot(ray->d_unit, cy->axis) * vdot(oc, cy->axis));
	c = vdot(oc, oc) - pow(vdot(oc, cy->axis), 2) - pow(cy->radius, 2);

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return FALSE;

	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);

	double t = fmin(t1, t2);
	double y = vdot(vminus(ray_at(ray, t), cy->origin), cy->axis);
	if (y < 0 || y > cy->height)
	{
		if (t1 > rec->tmin && t1 < rec->tmax)
			t = t1;
		else if (t2 > rec->tmin && t2 < rec->tmax)
			t = t2;
		else
			return FALSE;
		y = vdot(vminus(ray_at(ray, t), cy->origin), cy->axis);
		if (y < 0 || y > cy->height)
			return FALSE;
	}

	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->normal = vunit(vminus(vminus(rec->p, cy->origin), vmult(cy->axis, (y / vlength(cy->axis)))));
	set_face_normal(ray, rec);
	rec->albedo = obj->albedo;
	return TRUE;
}

// t_bool		hit_plane(t_object *obj, t_ray *ray, t_hit_record *rec)
// {
// 	t_plane		*pl;
// 	t_vector	oc;
// 	double		cosine;
// 	double		root;
// 	double		t;

// 	pl = obj->element;
// 	oc = vminus(pl->origin, ray->origin);
// 	cosine = vdot(oc, pl->normal) / vlength(oc);
// 	if (cosine == 0)
// 		return (FALSE);
// 	root = vdot(ray->d_unit, pl->normal) / cosine;
// 	if (root != 0)
// 		return (FALSE);
// 	rec->t = t;
// 	rec->p = ray_at(ray, t);
// 	rec->normal = pl->normal;
// 	set_face_normal(ray, rec);
// 	rec->albedo = obj->albedo;
// 	return (TRUE);
// }