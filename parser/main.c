/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <st.linsio@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 02:27:46 by hyeondle          #+#    #+#             */
/*   Updated: 2023/07/12 08:04:08 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "./libft/mylibft.h"
#include <math.h>
#include "vector.h"
#include "map.h"
#include "trace.h"
/*										*/
/*		basic structure for parser		*/
/*										*/

typedef struct s_ambient2
{
	double		ratio;
	t_vector	color;
}				t_ambient2;

typedef struct s_camera2
{
	t_vector	origin;
	t_vector	orientation;
	double		fov;
}				t_camera2;

typedef struct	s_light2
{
	t_vector	point;
	double		brightness;
	t_vector	color;
}				t_light2;

typedef struct 	s_sphere2
{
	t_vector	origin;
	double		diameter;
	t_vector	color;
}				t_sphere2;

typedef struct	s_plane2
{
	t_vector	point;
	t_vector	normal;
	t_vector	color;
}				t_plane2;

typedef struct	s_cylinder2
{
	t_vector	origin;
	t_vector	axis;
	double		diameter;
	double		height;
	t_vector	color;
}				t_cylinder2;

typedef struct	s_setting
{
	char				*type;
	void				*object;
	struct s_setting	*next;
}						t_setting;

t_vector	mv(char *dot)
{
	char **tab;

	tab = ft_split(dot, ',');
	if (!tab || !tab[0] || !tab[1] || !tab[2] || tab[3])
	{
		printf("invalid input\n");
		exit(1);
	}
	return (vector(atof(tab[0]), atof(tab[1]), atof(tab[2])));
}

t_setting	*init_setting(void)
{
	t_setting	*set;

	set = (t_setting *)malloc(sizeof(t_setting));
	if (!set)
	{
		printf("malloc error");
		exit(1);
	}
	set->type = NULL;
	set->object = NULL;
	set->next = NULL;
	return (set);
}

t_ambient2	*i_ambient(char **info)
{
	t_ambient2 *ambient;

	ambient = (t_ambient2 *)malloc(sizeof(t_ambient2));
	ambient->ratio = atof(info[1]);
	ambient->color = mv(info[2]);

	return (ambient);
}

t_camera2	*i_camera(char **info)
{
	t_camera2	*camera;

	camera = (t_camera2 *)malloc(sizeof(t_camera2));
	camera->origin = mv(info[1]);
	camera->orientation = mv(info[2]);
	camera->fov = atof(info[3]);

	return (camera);
}

t_light2	*i_light(char **info)
{
	t_light2	*light;

	light = (t_light2 *)malloc(sizeof(t_light2));
	light->point = mv(info[1]);
	light->brightness = atof(info[2]);
	light->color = mv(info[3]);

	return (light);
}

t_sphere2	*i_sphere(char **info)
{
	t_sphere2 *sphere;

	sphere = (t_sphere2 *)malloc(sizeof(t_sphere2));
	sphere->origin = mv(info[1]);
	sphere->diameter = atof(info[2]);
	sphere->color = mv(info[3]);

	return (sphere);
}

t_plane2	*i_plane(char **info)
{
	t_plane2	*plane;

	plane = (t_plane2 *)malloc(sizeof(t_plane2));
	plane->point = mv(info[1]);
	plane->normal = mv(info[2]);
	plane->color = mv(info[3]);

	return (plane);
}

t_cylinder2	*i_cylinder(char **info)
{
	t_cylinder2	*cylinder;

	cylinder = (t_cylinder2 *)malloc(sizeof(t_cylinder2));
	cylinder->origin = mv(info[1]);
	cylinder->axis = mv(info[2]);
	cylinder->diameter = atof(info[3]);
	cylinder->height = atof(info[4]);
	cylinder->color = mv(info[5]);

	return (cylinder);
}

void	*object_set(char **info)
{
	char	*type;

	type = info[0];
	if (type[0] == 'A' && type[1] == '\0')
		return ((void *)i_ambient(info));
	else if (type[0] == 'C' && type[1] == '\0')
		return ((void *)i_camera(info));
	else if (type[0] == 'L' && type[1] == '\0')
		return ((void *)i_light(info));
	else if (type[0] == 's' && type[1] == 'p' && type[2] == '\0')
		return ((void *)i_sphere(info));
	else if (type[0] == 'p' && type[1] == 'l' && type[2] == '\0')
		return ((void *)i_plane(info));
	else if (type[0] == 'c' && type[1] == 'y' && type[2] == '\0')
		return ((void *)i_cylinder(info));
	else
		return (NULL);
}

void	parse(t_setting *set, char *line)
{
	t_setting	*temp;
	char		**info;

	while (set->next != NULL)
		set = set->next;
	if (set->type == NULL && set->object == NULL)
		temp = set;
	else
	{
		temp = init_setting();
		set->next = temp;
	}
	info = ft_split(line, ' ');
	if (info == NULL)
	{
		printf("file error\n");
		exit(1);
	}
	temp->type = ft_strdup(info[0]);
	temp->object = object_set(info);
	if (set->object == NULL)
	{
		printf("file error\n");
		exit(1);
	}
}

t_setting *parser(int argc, char **argv)
{
	int			fd;
	char		*line;
	t_setting	*set;


	if (argc != 2)
	{
		printf("input error\n");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("wrong file\n");
		exit(1);
	}
	set = init_setting();
	line = get_next_line(fd);
	while (line != NULL)
	{
		parse(set, line);
		line = get_next_line(fd);
	}
	return (set);
}

t_camera	set_camera(t_setting *set, t_canvas canvas)
{
	t_camera	cam;
	t_camera2	*s_cam;
	double		focal_length;

	s_cam = (t_camera2 *)set->object;
	cam.origin = s_cam->origin;
	cam.fov = s_cam->fov;
	cam.viewport_height = 2.0 * tan((cam.fov * M_PI / 180) / 2);
	cam.viewport_width = cam.viewport_height * canvas.aspect_ratio;
	cam.focal_length = 1.0;
	cam.horizontal = vector(cam.viewport_width, 0, 0);
	cam.vertical = vector(0, cam.viewport_height, 0);
	cam.left_bottom = vminus(vminus(vminus(cam.origin, vdivide(cam.horizontal, 2)), vdivide(cam.vertical, 2)), vector(0, 0, cam.focal_length));
	return (cam);
}

t_vector	set_ambient(t_setting *set)
{
	t_ambient2	*a_info;
	t_vector	normalized_color;
	t_vector	ambient;

	a_info = (t_ambient2 *)set->object;
	normalized_color = vdivide(a_info->color, 255);
	ambient = vmult(normalized_color, a_info->ratio);
	return (ambient);
}

t_object		*set_light(t_setting *set)
{
	t_object	*light;
	t_light2	*l_info;

	light = (t_object *)malloc(sizeof(t_object));
	if (!light)
	{
		printf("malloc failed\n");
		exit(1);
	}
	l_info = (t_light2 *)set->object;
	light = object(LIGHT_POINT, light_point(l_info->point, vdivide(l_info->color, 255), l_info->brightness), vector(0, 0, 0));
	return (light);
}

int	get_type(t_setting *set)
{
	char	f;
	char	s;
	char	t;

	f = set->type[0];
	s = set->type[1];
	t = set->type[2];
	if (f == 's' && s == 'p' && t == '\0')
		return (SP);
	if (f == 'p' && s == 'l' && t == '\0')
		return (PL);
	if (f == 'c' && s == 'y' && t == '\0')
		return (CY);
	return (0);
}

t_object	*primary_object(t_setting *set, int type)
{
	t_sphere2	*sp;
	t_plane2	*pl;
	t_cylinder2	*cy;

	if (type == SP)
	{
		sp = (t_sphere2 *)set->object;
		return (object(SP, sphere(sp->origin, sp->diameter), sp->color));
	}
	if (type == PL)
	{
		pl = (t_plane2 *)set->object;
		return (object(PL, plane(pl->point, pl->normal), pl->color));
	}
	if (type == CY)
	{
		cy = (t_cylinder2 *)set->object;
		return (object(CY, cylinder(cy->origin, cy->axis, cy->diameter, cy->height), cy->color));
	}
	return (NULL);
}

void	object_add(t_setting *set, int type, t_object *world)
{
	t_sphere2	*sp;
	t_plane2	*pl;
	t_cylinder2	*cy;

	if (type == SP)
	{
		sp = (t_sphere2 *)set->object;
		oadd(&world, (object(SP, sphere(sp->origin, sp->diameter), sp->color)));
	}
	if (type == PL)
	{
		pl = (t_plane2 *)set->object;
		oadd(&world, (object(PL, plane(pl->point, pl->normal), pl->color)));
	}
	if (type == CY)
	{
		cy = (t_cylinder2 *)set->object;
		oadd(&world, (object(CY, cylinder(cy->origin, cy->axis, cy->diameter, cy->height), cy->color)));
	}
}

t_object	*set_world(t_setting *set)
{
	t_setting	*set_t;
	t_object	*world;
	int			object_type;

	object_type = 0;
	world = NULL;
	set_t = set;
	while (set_t->next != NULL)
	{
		if (set_t->type[0] == 'C' || set_t->type[0] == 'A' || set_t->type[0] == 'L')
		{
			set_t = set_t->next;
			continue;
		}
		object_type = get_type(set);
		if (world == NULL && object_type != 0)
			world = primary_object(set, object_type);
		else if (object_type != 0)
			object_add(set, object_type, world);
		else
		{
			printf("wrong map file\n");
			exit(1);
		}
		set_t = set_t->next;
	}
}

t_map	*map_init2(t_setting *set)
{
	t_map	*map;
	t_setting	*set_t;

	set_t = set;
	if(!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	map->canvas = canvas(1280, 720);
	while (set_t->next != NULL)
	{
		if (set_t->type[0] == 'C' && set_t->type[1] == '\0')
			map->camera = set_camera(set_t, map->canvas); // camera -- 1 ,
		else if (set->type[0] == 'A' && set_t->type[1] == '\0')
			map->ambient = set_ambient(set_t);
		else if (set->type[0] == 'L' && set_t->type[1] == '\0')
			map->light = set_light(set_t);
		//light, object --> many
		// abient -> diff
		set_t = set_t->next;
	}
	map->world = set_world(set_t);
	return (map);
}

int	main(int argc, char **argv)
{
	t_setting	*set;
	t_map		*map;

	set = parser(argc, argv);
	map = map_init2(set);
	//mlx init
	while (1)
	{
		draw(map, window); //write_color -> draw pixel on mlx_window
		//mlx_hook events
		//mlx_loop
	}
	return (0);
}

//need to make atof()
//need to modify error handlers (not just exit)
