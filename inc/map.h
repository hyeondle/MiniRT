/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:07:17 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/02 16:41:43 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "vector.h"

typedef struct s_canvas
{
	int		width; //canvas width
	int		height; //canvas height;
	double 	aspect_ratio; //종횡비
}			t_canvas;

typedef struct s_camera
{
	t_vector	origin;  // 카메라 원점(위치)
	double		viewport_height; // 뷰포트 세로길이
	double		viewport_width; // 뷰포트 가로길이
	t_vector	horizontal; // 수평길이 벡터
	t_vector	vertical; // 수직길이 벡터
	double		focal_length; // focal length
	t_vector	left_bottom; // 왼쪽 아래 코너점
}				t_camera;

t_canvas	canvas(int width, int height);
t_camera	camera(t_canvas *canvas, t_vector origin);

#endif