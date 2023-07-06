/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 02:27:46 by hyeondle          #+#    #+#             */
/*   Updated: 2023/07/07 04:32:53 by hyeondle         ###   ########.fr       */
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

void	parse(t_setting *set, char *line)
{
	
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