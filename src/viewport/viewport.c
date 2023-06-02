/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 03:24:18 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/03 03:25:27 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/viewport.h"

t_canvas	canvas(int width, int height)
{
	t_canvas	canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.aspect_ratio = (double)width / (double)height;

	return (canvas);
}

t_camera	camera(t_canvas *canvas, t_vector origin)
{
	t_camera	camera;
	double		focal_length;

	camera.origin = origin;
	camera.viewport_height = 2.0;
	camera.viewport_width = camera.viewport_height * canvas->aspect_ratio;
	camera.focal_length = 1.0;
	camera.horizontal = vector(camera.viewport_width, 0, 0);
	camera.vertical = vector(0, camera.viewport_height, 0);
	camera.left_bottom = vminus(vminus(vminus(camera.origin, \
		vdivide(camera.horizontal, 2)), vdivide(camera.vertical, 2)),
		vector(0, 0, camera.focal_length));
	return (camera);
}
