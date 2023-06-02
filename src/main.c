/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:32:59 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/03 03:36:11 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/trace.h"
#include <stdio.h>

void    write_color(t_vector pixel_color)
{
	printf("%d %d %d\n", (int)(255.999 * pixel_color.x),
						(int)(255.999 * pixel_color.y),
						(int)(255.999 * pixel_color.z));
}

int main(void)
{
	int         i;
	int         j;
	double      u;
	double      v;
	t_vector    pixel_color;
	t_map		*map;

	map = map_init();

	printf("P3\n%d %d\n255\n", map->canvas.width, map->canvas.height);
	j = map->canvas.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < map->canvas.width)
		{
			u = (double)i / (map->canvas.width - 1);
			v = (double)j / (map->canvas.height - 1);
			map->ray = ray_primary(&map->camera, u, v);
			pixel_color = ray_color(map);
			write_color(pixel_color);
			++i;
		}
		--j;
	}
	return (0);
}