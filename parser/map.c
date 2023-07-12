/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <st.linsio@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:05:21 by hyeondle          #+#    #+#             */
/*   Updated: 2023/07/12 19:06:07 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdlib.h>
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

t_object    *object(t_object_type type, void *element, t_vector albedo)
{
    t_object    *new;

    if (!(new = (t_object *)malloc(sizeof(t_object))))
        return (NULL);
    new->type = type;
    new->element = element;
    new->albedo = albedo;
    new->next = NULL;
    return (new);
}

void        oadd(t_object **list, t_object *newo)
{
    t_object    *cur;

    if (*list == NULL)
    {
        *list = newo;
        return ;
    }
    cur = *list;
    while (cur->next)
        cur = cur->next;
    cur->next = newo;
}

t_object    *olast(t_object *list)
{
    if (list == NULL)
        return (NULL);
    while (list->next)
        list = list->next;
    return (list);
}

t_light     *light_point(t_vector origin, t_vector color, double brightness)
{
    t_light *light;

    if(!(light = (t_light *)malloc(sizeof(t_light))))
        return (NULL);
    light->origin = origin;
    light->color = color;
    light->brightness = brightness;
    return (light);
}

t_sphere    *sphere(t_vector center, double radius)
{
    t_sphere *sp;

    if(!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
        return (NULL);
    sp->center = center;
    sp->radius = radius;
    sp->radius2 = radius * radius;
    return (sp);
}

t_plane     *plane(t_vector origin, t_vector normal)
{
    t_plane *pl;

    if(!(pl = (t_plane *)malloc(sizeof(t_plane))))
        return (NULL);
    pl->origin = origin;
    pl->normal = normal;
    return (pl);
}

t_cylinder  *cylinder(t_vector origin, t_vector axis, double radius, double height)
{
    t_cylinder  *cy;

    if(!(cy = (t_cylinder *)malloc(sizeof(t_cylinder))))
        return (NULL);
    cy->origin = origin;
    cy->axis = axis;
    cy->radius = radius;
    cy->height = height;

    return (cy);
}
