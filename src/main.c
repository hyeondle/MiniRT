/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:32:59 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/02 20:40:38 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/trace.h"
#include <stdio.h>

void    write_color(t_vector pixel_color)
{
	printf("%d %d %d\n", (int)(255.999 * pixel_color.x),
						(int)(255.999 * pixel_color.y),
						(int)(255.999 * pixel_color.z));
	// printf("%f %f %f\n", pixel_color.x, pixel_color.y, pixel_color.z);
}
int main(void)
{
	int         i;
	int         j;
	/* * * * 추가 * * * */
	double      u;
	double      v;
	/* * * * 추가 끝 * * * */

	t_vector    pixel_color;
	/* * * * 수정 * * * */
	t_canvas    canv;
	t_camera    cam;
	t_ray       ray;
	t_object	*world;
	//Scene setting;
	canv = canvas(400, 300);
	cam = camera(&canv, vector(0, 0, 0));
	world = object(SP, sphere(vector(-2, 0, -5), 2));
	oadd(&world, object(SP, sphere(vector(2, 0, -5), 2)));
	oadd(&world, object(SP, sphere(vector(0, -1000, 0), 990)));
	/* * * * 수정 끝 * * * */

	// 랜더링
	// P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀 수, 마지막은 사용할 색상값
	/* * * * 수정 * * * */
	printf("P3\n%d %d\n255\n", canv.width, canv.height);
	j = canv.height - 1;
	/* * * * 수정 끝 * * * */
	while (j >= 0)
	{
		i = 0;
		/* * * * 수정 * * * */
		while (i < canv.width)
		{
			u = (double)i / (canv.width - 1);
			v = (double)j / (canv.height - 1);
			//ray from camera origin to pixel
			ray = ray_primary(&cam, u, v);
			pixel_color = ray_color(&ray, world);
		/* * * * 수정 끝 * * * */
			// printf("%f %f\n", u, v);
			write_color(pixel_color);
			++i;
		}
		--j;
	}
}