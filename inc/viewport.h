/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:07:17 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/03 03:15:28 by hyeondle         ###   ########.fr       */
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
}				t_camera;

t_canvas	canvas(int width, int height);
t_camera	camera(t_canvas *canvas, t_vector origin);

#endif