/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:08:55 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/03 17:59:19 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/trace.h"
#include <stdlib.h>

t_map	*map_init(void)
{
	t_map		*map;
	t_object	*world;
	t_object	*light;
	double		ka;

	if(!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	map->canvas = canvas(1280, 720);
	map->camera = camera(&map->canvas, vector(0, 10, 20));
	world = object(SP, sphere(vector(-2, 0, -5), 2), vector(0.5, 0, 0));
	oadd(&world, object(SP, sphere(vector(2, 0, -5), 1), vector(0, 0.5, 0)));
	oadd(&world, object(SP, sphere(vector(1, -1, -7), 2), vector(0, 0, 0.5)));
	oadd(&world, object(SP, sphere(vector(7, 2, -6), 0.4), vector(0.2, 0.5, 0.3)));
	oadd(&world, object(SP, sphere(vector(3, 4, -3), 1.3), vector(0.1, 0.1, 0.1)));
	oadd(&world, object(SP, sphere(vector(0, -1000, 0), 995), vector(1, 1, 1)));
	oadd(&world, object(PL, plane(vector(0,0,-1000), vector(0,0.4,0.7)), vector(0.3,0.5,0.7)));
	oadd(&world, object(CY, cylinder(vector(10, 10, -15), vector(0.3, 1, 0), 5, 14), vector(0.1, 0.45, 0.6)));
	oadd(&world, object(CY, cylinder(vector(-20, 10, -15), vector(1, 0, 0), 3.5, 20), vector(0.5, 0.45, 0.6)));
	map->world = world;
	light = object(LIGHT_POINT, light_point(vector(0, 20, 20), vector(1, 1, 1), 0.5), vector(0, 0, 0));
	map->light = light;
	ka = 0.2;
	map->ambient = vmult(vector(1, 1, 1), ka);
	return (map);
}
