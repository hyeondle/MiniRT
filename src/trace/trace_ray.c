/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:16:42 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/03 22:20:24 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/trace.h"

t_ray		ray_primary(t_camera *cam, double u, double v)
{
	t_ray   ray;

	ray.origin = cam->origin;
	ray.d_unit = vunit(vminus(vplus(cam->left_bottom, (vplus(vmult(cam->horizontal, u), vmult(cam->vertical, v)))), cam->origin));
	return (ray);
}

t_vector	ray_color(t_map	*map)
{
	double  		t;
	t_vector		n;

	map->rec = record_init(); //P = O + v*t의 t값 초기 범위 설정
	if (hit(map->world, &map->ray, &map->rec)) //광선이 물체에 맞았다면
		return (phong_lighting(map));	//퐁 라이트닝 모델 적용
	else	//아닐경우 배경 적용
	{
		t = 0.5 * (map->ray.d_unit.y + 1.0);
		return (vplus(vmult(vector(1, 1, 1), 1.0 - t), vmult(vector(0.0, 0.0, 0.0), t)));
	}
}