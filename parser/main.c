/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <st.linsio@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 02:27:46 by hyeondle          #+#    #+#             */
/*   Updated: 2023/07/07 08:26:04 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "./libft/mylibft.h"

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

typedef struct s_ambient
{
	double		ratio;
	t_vector	color;
}				t_ambient;

typedef struct s_camera
{
	t_vector	origin;
	t_vector	orientation;
	double		fov;
}				t_camera;

typedef struct	s_light
{
	t_vector	point;
	double		brightness;
	t_vector	color;
}				t_light;

typedef struct 	s_sphere
{
	t_vector	origin;
	double		diameter;
	t_vector	color;
}				t_sphere;

typedef struct	s_plane
{
	t_vector	point;
	t_vector	normal;
	t_vector	color;
}				t_plane;

typedef struct	s_cylinder
{
	t_vector	origin;
	t_vector	axis;
	double		diameter;
	double		height;
	t_vector	color;
}				t_cylinder;

typedef struct	s_setting
{
	char				*type;
	void				*object;
	struct s_setting	*next;
}						t_setting;

t_vector	vector(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;

	return (v);
}

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

t_ambient	*i_ambient(char **info)
{
	t_ambient *ambient;

	ambient = (t_ambient *)malloc(sizeof(t_ambient));
	ambient->ratio = atof(info[1]);
	ambient->color = mv(info[2]);

	return (ambient);
}

t_camera	*i_camera(char **info)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	camera->origin = mv(info[1]);
	camera->orientation = mv(info[2]);
	camera->fov = atof(info[3]);

	return (camera);
}

t_light	*i_light(char **info)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	light->point = mv(info[1]);
	light->brightness = atof(info[2]);
	light->color = mv(info[3]);

	return (light);
}

t_sphere	*i_sphere(char **info)
{
	t_sphere *sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->origin = mv(info[1]);
	sphere->diameter = atof(info[2]);
	sphere->color = mv(info[3]);

	return (sphere);
}

t_plane	*i_plane(char **info)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	plane->point = mv(info[1]);
	plane->normal = mv(info[2]);
	plane->color = mv(info[3]);

	return (plane);
}

t_cylinder	*i_cylinder(char **info)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
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

	while (set->next == NULL)
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
	set->type = ft_strdup(info[0]);
	set->object = object_set(info);
	if (set->object == NULL)
	{
		printf("file error\n");
		exit(1);
	}
}

int main(int argc, char **argv)
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
}

//need to make atof()
//need to modify error handlers (not just exit)
