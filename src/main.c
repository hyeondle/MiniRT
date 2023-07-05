/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <st.linsio@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:32:59 by hyeondle          #+#    #+#             */
/*   Updated: 2023/07/04 05:41:55 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/trace.h"
#include <stdio.h>
#include <math.h>

void    write_color(t_vector pixel_color)
{
	printf("%d %d %d\n", (int)(255.999 * pixel_color.x),
						(int)(255.999 * pixel_color.y),
						(int)(255.999 * pixel_color.z));
}

// t_vector get_corrected_uv(double u, double v, double viewport_height, double viewport_width) {
//     // Calculate the center of the viewport
//     double half_width = viewport_width / 2.0;
//     double half_height = viewport_height / 2.0;

//     // Calculate the distances from the center of the viewport to the point (u, v)
//     double x_dist = u - half_width;
//     double y_dist = v - half_height;

//     // Calculate the distances in terms of the angle from the center of the viewport to the point (u, v)
//     double angle_x = atan2(x_dist, half_width);
//     double angle_y = atan2(y_dist, half_height);

//     // Recalculate the distances from the center of the viewport to the point (u, v) using the angles
//     double corrected_x_dist = tan(angle_x) * half_width;
//     double corrected_y_dist = tan(angle_y) * half_height;

//     // Recalculate the point (u, v) using the corrected distances
//     double corrected_u = half_width + corrected_x_dist;
//     double corrected_v = half_height + corrected_y_dist;

//     return (vector(corrected_u, corrected_v, 0));
// }

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
			map->ray = ray_primary(&map->camera, u, v); //viewport의 각 픽셀에 쏠 방향벡터 구하기
			pixel_color = ray_color(map); //방향벡터로 나가는 광선 추적
			write_color(pixel_color);
			++i;
		}
		--j;
	}
	return (0);
}