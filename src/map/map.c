/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:08:55 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/03 05:01:19 by hyeondle         ###   ########.fr       */
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
	map->canvas = canvas(400, 300);
	map->camera = camera(&map->canvas, vector(0, 0, 0));
	world = object(SP, sphere(vector(-2, 0, -5), 2), vector(0.5, 0, 0));
	oadd(&world, object(SP, sphere(vector(2, 0, -5), 2), vector(0, 0.5, 0)));
	oadd(&world, object(SP, sphere(vector(0, -1000, 0), 995), vector(1, 1, 1)));
	map->world = world;
	light = object(LIGHT_POINT, light_point(vector(0, 20, 0), vector(1, 1, 1), 0.5), vector(0, 0, 0));
	map->light = light;
	ka = 0.1;
	map->ambient = vmult(vector(1, 1, 1), ka);
	return (map);
}
