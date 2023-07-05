/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <st.linsio@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 03:24:18 by hyeondle          #+#    #+#             */
/*   Updated: 2023/07/04 07:34:29 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/viewport.h"
#include <math.h>

t_canvas	canvas(int width, int height)
{
	t_canvas	canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.aspect_ratio = (double)width / (double)height;

	return (canvas);
}

t_camera	camera(t_canvas *canvas, t_vector origin, double fov)
{
	t_camera	camera;
	double		focal_length;
	double		half_height;
	double		half_width;

	camera.origin = origin;
	half_height = tan((fov * M_PI / 180) / 2);
	half_width = half_height * canvas->aspect_ratio;
	camera.viewport_height = 2.0 * half_height;
	camera.viewport_width = 2.0 * half_width;
	// camera.viewport_height = 2.0;
	// camera.viewport_width = camera.viewport_height * canvas->aspect_ratio;
	camera.focal_length = 1.0;
	camera.horizontal = vector(camera.viewport_width, 0, 0);
	camera.vertical = vector(0, camera.viewport_height, 0);
	camera.left_bottom = vminus(vminus(vminus(camera.origin, \
		vdivide(camera.horizontal, 2)), vdivide(camera.vertical, 2)),
		vector(0, 0, camera.focal_length));
	camera.fov = fov;
	return (camera);
}
