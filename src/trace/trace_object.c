/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:31:26 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/02 16:41:38 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/trace.h"
#include <math.h>

t_bool      hit_sphere(t_object *sp, t_ray *ray, t_hit_record *rec)
{
	t_vector  oc; //방향벡터로 나타낸 구의 중심.
	//a, b, c는 각각 t에 관한 2차 방정식의 계수
	double  a;
	double  half_b;
	double  c;
	double  discriminant; //판별식
	double	sqrtd;
	double	root;

	oc = vminus(ray->origin, ((t_sphere *)(sp->element))->center);
	a = vlength_pow2(ray->d_unit);
	half_b = vdot(oc, ray->d_unit);
	c = vlength_pow2(oc) - ((t_sphere *)(sp->element))->radius2;
	// discriminant 는 판별식
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
	rec->normal = vdivide(vminus(rec->p, ((t_sphere *)(sp->element))->center), ((t_sphere *)(sp->element))->radius);
	set_face_normal(ray, rec);
	return (TRUE);
}