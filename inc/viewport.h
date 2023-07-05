/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <st.linsio@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:07:17 by hyeondle          #+#    #+#             */
/*   Updated: 2023/07/04 05:41:47 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWPORT_H
# define VIEWPORT_H

# include "object.h"
# include "vector.h"

typedef struct s_canvas
{
	int		width;
	int		height;
	double 	aspect_ratio;
}			t_canvas;

typedef struct s_camera
{
	t_vector	origin;
	double		viewport_height;
	double		viewport_width;
	t_vector	horizontal;
	t_vector	vertical;
	double		focal_length;
	t_vector	left_bottom;
	// added
	t_vector	lookfrom;
	t_vector	lookat;
	t_vector	upvector;
	double		fov;
}				t_camera;

t_canvas	canvas(int width, int height);
t_camera	camera(t_canvas *canvas, t_vector origin, double fov);

#endif