/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:18:55 by hyeondle          #+#    #+#             */
/*   Updated: 2023/06/03 17:45:42 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/object.h"
#include <stdlib.h>

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
