/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <st.linsio@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:12:59 by hyeondle          #+#    #+#             */
/*   Updated: 2023/07/04 05:41:54 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vector.h"
#include "../../inc/viewport.h"
#include <math.h>

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
