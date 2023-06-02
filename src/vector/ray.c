/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:12:59 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/02 16:41:35 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vector.h"

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
