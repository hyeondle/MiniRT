/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <st.linsio@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:31:26 by hyeondle          #+#    #+#             */
/*   Updated: 2023/07/04 05:41:51 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/trace.h"
#include <math.h>

t_hit_record	record_init(void)
{
	t_hit_record	record;

	record.tmin = EPSILON;	//극소치
	record.tmax = INFINITY;	//극대치
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

// t_bool hit_cylinder(t_object *obj, t_ray *ray, t_hit_record *rec)
// {
//     t_cylinder *cy = obj->element;
//     t_vector oc = vminus(ray->origin, cy->origin);

//     double a = vdot(ray->d_unit, ray->d_unit) - pow(vdot(ray->d_unit, cy->axis), 2);
//     double b = vdot(oc, ray->d_unit) - vdot(ray->d_unit, cy->axis) * vdot(oc, cy->axis);
//     double c = vdot(oc, oc) - pow(vdot(oc, cy->axis), 2) - pow(cy->radius, 2);

//     double discriminant = b * b - a * c;
//     if (discriminant < 0)
//         return FALSE;

//     double t = (-b - sqrt(discriminant)) / a;
//     t_vector p = ray_at(ray, t);
//     t_vector op = vminus(p, cy->origin);

//     double proj1 = vdot(op, cy->axis);
//     double proj2 = vdot(ray->d_unit, cy->axis);

//     if (proj1 < 0 || proj1 > cy->height || proj2 == 0)
//     {
//         t = (-b + sqrt(discriminant)) / a;
//         p = ray_at(ray, t);
//         op = vminus(p, cy->origin);
//         proj1 = vdot(op, cy->axis);
//         proj2 = vdot(ray->d_unit, cy->axis);

//         if (proj1 < 0 || proj1 > cy->height || proj2 == 0)
//             return FALSE;
//     }

//     if (vlength(op) <= cy->radius && vdot(op, cy->axis) >= 0 && vdot(op, cy->axis) <= cy->height)
//     {
//         rec->t = t;
//         rec->p = p;
//         rec->normal = vunit(vminus(op, vmult(cy->axis, proj1 / vlength(cy->axis))));
//         set_face_normal(ray, rec);
//         rec->albedo = obj->albedo;
//         return TRUE;
//     }

//     return FALSE;
// }

// t_bool	hit_cap(t_ray *ray, t_hit_record *rec, t_vector center, double radius, t_vector axis, double min_t)
// {
// 	double t = (vdot(axis, vminus(center, ray->origin)) / vdot(axis, ray->d_unit));
// 	if (t < min_t || t > rec->tmax)
// 		return FALSE;
// 	t_vector p = ray_at(ray, t);
// 	t_vector dist = vminus(p, center);
// 	if (vdot(dist, dist) > pow(radius, 2))
// 		return FALSE;
// 	rec->t = t;
// 	rec->p = p;
// 	rec->normal = axis;
// 	set_face_normal(ray, rec);
// 	return TRUE;
// }

t_bool	hit_cap(t_ray *ray, t_hit_record *rec, t_vector center, double radius, t_vector axis, double min_t)
{
	double t = (vdot(axis, vminus(center, ray->origin)) / vdot(axis, ray->d_unit));
	if (t < min_t || t > rec->tmax)
		return FALSE;
	t_vector p = ray_at(ray, t);
	t_vector dist = vminus(p, center);
	if (vdot(dist, dist) > pow(radius, 2))
		return FALSE;
	rec->t = t;
	rec->p = p;
	if (vdot(vminus(ray->origin, center), axis) < 0)
		rec->normal = axis;
	else
		rec->normal = vmult(axis, -1);
	set_face_normal(ray, rec);
	return TRUE;
}

t_bool	hit_cylinder(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	double a, b, c, discriminant;
	double t1, t2;
	double hit_t = INFINITY;
	t_bool hit = FALSE;

	cy = obj->element;
	t_vector oc = vminus(ray->origin, cy->origin);
	a = vdot(ray->d_unit, ray->d_unit) - pow(vdot(ray->d_unit, cy->axis), 2);
	b = 2 * (vdot(ray->d_unit, oc) - vdot(ray->d_unit, cy->axis) * vdot(oc, cy->axis));
	c = vdot(oc, oc) - pow(vdot(oc, cy->axis), 2) - pow(cy->radius, 2);

	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0)
	{
		t1 = (-b - sqrt(discriminant)) / (2 * a);
		t2 = (-b + sqrt(discriminant)) / (2 * a);
		double y1 = vdot(vminus(ray_at(ray, t1), cy->origin), cy->axis);
		double y2 = vdot(vminus(ray_at(ray, t2), cy->origin), cy->axis);

		if (y1 > 0 && y1 < cy->height && t1 > rec->tmin && t1 < rec->tmax)
		{
			hit = TRUE;
			hit_t = t1;
		}
		if (y2 > 0 && y2 < cy->height && t2 > rec->tmin && t2 < rec->tmax)
		{
			hit = TRUE;
			hit_t = (t2 < hit_t) ? t2 : hit_t;
		}
	}

	// check for hit on cap ends
	if (hit_cap(ray, rec, cy->origin, cy->radius, cy->axis, 0) && rec->t < hit_t)
	{
		hit = TRUE;
		hit_t = rec->t;
	}
	t_vector top_centroid = vplus(cy->origin, vmult(cy->axis, cy->height));
	if (hit_cap(ray, rec, top_centroid, cy->radius, cy->axis, 0) && rec->t < hit_t)
	{
		hit = TRUE;
		hit_t = rec->t;
	}

	if (hit)
	{
		rec->t = hit_t;
		rec->p = ray_at(ray, hit_t);
		t_vector op = vminus(rec->p, cy->origin);
		rec->normal = vunit(vminus(op, vmult(cy->axis, vdot(op, cy->axis))));
		set_face_normal(ray, rec);
		rec->albedo = obj->albedo;
	}

	return hit;
}

// t_bool	hit_cylinder(t_object *obj, t_ray *ray, t_hit_record *rec)
// {
// 	t_cylinder	*cy;
// 	double a, b, c, discriminant;
// 	double t1, t2;

// 	cy = obj->element;
// 	t_vector oc = vminus(ray->origin, cy->origin);
// 	a = vdot(ray->d_unit, ray->d_unit) - pow(vdot(ray->d_unit, cy->axis), 2);
// 	b = 2 * (vdot(ray->d_unit, oc) - vdot(ray->d_unit, cy->axis) * vdot(oc, cy->axis));
// 	c = vdot(oc, oc) - pow(vdot(oc, cy->axis), 2) - pow(cy->radius, 2);

// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant < 0)
// 		return FALSE;

// 	t1 = (-b - sqrt(discriminant)) / (2 * a);
// 	t2 = (-b + sqrt(discriminant)) / (2 * a);

// 	double t = fmin(t1, t2);
// 	double y = vdot(vminus(ray_at(ray, t), cy->origin), cy->axis);
// 	if (y < 0 || y > cy->height)
// 	{
// 		if (t1 > rec->tmin && t1 < rec->tmax)
// 			t = t1;
// 		else if (t2 > rec->tmin && t2 < rec->tmax)
// 			t = t2;
// 		else
// 			return FALSE;
// 		y = vdot(vminus(ray_at(ray, t), cy->origin), cy->axis);
// 		if (y < 0 || y > cy->height)
// 			return FALSE;
// 	}

// 	rec->t = t;
// 	rec->p = ray_at(ray, t);
// 	rec->normal = vunit(vminus(vminus(rec->p, cy->origin), vmult(cy->axis, (y / vlength(cy->axis)))));
// 	set_face_normal(ray, rec);
// 	rec->albedo = obj->albedo;
// 	return TRUE;
// }

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