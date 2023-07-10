/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <st.linsio@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:49:48 by hyeondle          #+#    #+#             */
/*   Updated: 2023/07/10 12:51:12 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

t_vector	vplus(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;

	return (v);
}

t_vector	vminus(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;

	return (v);
}

t_vector	vmult(t_vector v, double t)
{
	t_vector	v_;

	v_.x = v.x * t;
	v_.y = v.y * t;
	v_.z = v.z * t;

	return (v_);
}

t_vector	vdivide(t_vector v, double t)
{
	t_vector	v_;

	if (t == 0)
		return (vector(0, 0, 0));

	v_.x = v.x * (1.0 / t);
	v_.y = v.y * (1.0 / t);
	v_.z = v.z * (1.0 / t);

	return (v_);
}


t_vector	vplus_2(t_vector v, double x, double y, double z)
{
	t_vector	v_;

	v_.x = v.x + x;
	v_.y = v.y + y;
	v_.z = v.z + z;

	return (v_);
}

t_vector	vminus_2(t_vector v, double x, double y, double z)
{
	t_vector	v_;

	v_.x = v.x - x;
	v_.y = v.y - y;
	v_.z = v.z - z;

	return (v_);
}

t_vector	vmult_2(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

t_vector	vmin(t_vector vec1, t_vector vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}

double		vlength(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double      vlength_pow2(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double		vdot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	vcross(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;

	return (v);
}

t_vector	vunit(t_vector v)
{
	t_vector	v_;
	double		length;

	length = vlength(v);
	if (length == 0)
	{
		printf("Error : 0 devide\n");
		exit(0);
	}
	v_.x = v.x / length;
	v_.y = v.y / length;
	v_.z = v.z / length;

	return (v_);
}

t_ray	ray(t_vector o, t_vector d)
{
	t_ray	ray;

	ray.origin = o;
	ray.d_unit = vunit(d);

	return (ray);
}

t_vector	ray_at(t_ray *ray, double t)
{
	t_vector	at;

	at = vplus(ray->origin, vmult(ray->d_unit, t));

	return (at);
}

t_vector	vector(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;

	return (v);
}

void		vector_set(t_vector *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}
