/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <st.linsio@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:52:50 by hyeondle          #+#    #+#             */
/*   Updated: 2023/07/10 12:54:15 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "vector.h"

typedef int	t_object_type;
#  define	LIGHT_POINT	0
#  define	SP			1
#  define	PL			2
#  define	CY			3
/*			object_list					*/
typedef struct	s_object
{
	t_object_type   type;
	void            *element;
	t_vector		albedo;
	void            *next;
}				t_object;

typedef struct	s_sphere
{
	t_vector    center;
	double      radius;
	double      radius2;
}				t_sphere;

typedef struct	s_light
{
	t_vector	origin;
	t_vector	color;
	double		brightness;
}				t_light;

typedef struct	s_plane
{
	t_vector	origin;
	t_vector	normal;
}				t_plane;

typedef struct	s_cylinder
{
	t_vector	origin;
	t_vector	axis;
	double		radius;
	double		height;
}				t_cylinder;

/*			viewport			*/

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

/*			map.h						*/
t_canvas	canvas(int width, int height);
t_camera	camera(t_canvas *canvas, t_vector origin, double fov);
/*			object_list_control			*/
t_object    *object(t_object_type type, void *element, t_vector albedo);
void        oadd(t_object **list, t_object *newo);
t_object    *olast(t_object *list);
/*			objects						*/
t_light     *light_point(t_vector origin, t_vector color, double brightness);
t_sphere    *sphere(t_vector center, double radius);
t_plane     *plane(t_vector origin, t_vector normal);
t_cylinder  *cylinder(t_vector origin, t_vector axis, double radius, double height);


#endif