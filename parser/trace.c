/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <st.linsio@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:03:35 by hyeondle          #+#    #+#             */
/*   Updated: 2023/07/12 19:05:06 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"
#include <stdlib.h>
#include <math.h>

t_vector	phong_lighting(t_map *map)
{
	t_vector	light_color;
	t_object	*light;

	light_color = vector(0, 0, 0);
	light = map->light;
	while (light)	//각 광원마다 반사 계산
	{
		if (light->type == LIGHT_POINT)
			light_color = vplus(light_color, point_light_get(map, light->element));
		light = light->next;
	}
	light_color = vplus(light_color, map->ambient);	//ambient 합
	return (vmin(vmult_2(light_color, map->rec.albedo), vector(1, 1, 1))); // 광원의 합이 1 넘을 경우 1로 내려줌(맥시멈 고정)
}

t_vector	point_light_get(t_map *map, t_light *light)
{
	t_vector	diffuse;
	t_vector	light_direction;
	double		kd; // diffuese의 강도
	t_vector	specular;
	double		light_length;
	t_ray		light_ray;
	t_vector	view_direction;
	t_vector	reflect_direction;
	double		spec;
	double		ksn; //shineness value
	double		ks;	//specular strength
	double		brightness;

	light_direction = vminus(light->origin, map->rec.p);
	light_length = vlength(light_direction);
	light_ray = ray(vplus(map->rec.p, vmult(map->rec.normal, EPSILON)), light_direction);
	if (in_shadow(map->world, light_ray, light_length))
		return (vector(0, 0, 0));
	light_direction = vunit(light_direction);
	kd = fmax(vdot(map->rec.normal, light_direction), 0.0);
	diffuse = vmult(light->color, kd);
	view_direction = vunit(vmult(map->ray.d_unit, -1));
	reflect_direction = reflect(vmult(light_direction, -1), map->rec.normal);
	ksn = 64;
	ks = 0.5;
	spec = pow(fmax(vdot(view_direction, reflect_direction), 0.0), ksn);
	specular = vmult(vmult(light->color, ks), spec);
	brightness = light->brightness * LUMEN;
	return (vmult(vplus(diffuse, specular), brightness));
}

t_vector	reflect(t_vector v, t_vector n)
{
	return (vminus(v, vmult(n, vdot(v, n) * 2)));
}

t_bool	 in_shadow(t_object *objects, t_ray light_ray, double light_length)
{
	t_hit_record	record;

	record.tmin = 0;
	record.tmax = light_length;
	if (hit(objects, &light_ray, &record))
		return (TRUE);
	return (FALSE);
}


t_bool      hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool			hit_anything;
	t_hit_record	temp_rec;

	temp_rec = *rec;
	hit_anything = FALSE;
	while(world)	//world에 저장된 물체를 전부 돌아가며 광선에 부딪히는지 체크
	{
		if (hit_obj(world, ray, &temp_rec))
		{
			hit_anything = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		world = world->next;
	}
	return (hit_anything);
}

t_bool	hit_obj(t_object *world, t_ray *ray, t_hit_record *rec) //각 종류별로 체크
{
	t_bool	hit_result;

	hit_result = FALSE;
	if (world->type == SP)
		hit_result = hit_sphere(world, ray, rec);
	else if (world->type == PL)
		hit_result = hit_plane(world, ray, rec);
	else if (world->type == CY)
		hit_result = hit_cylinder(world, ray, rec);
	return (hit_result);
}

void    set_face_normal(t_ray *r, t_hit_record *rec) // 법선벡터의 방향 조정
{
	rec->front_face = vdot(r->d_unit, rec->normal) < 0;
	if (rec->front_face)
		rec->normal = rec->normal;
	else
		rec->normal = vmult(rec->normal, -1);
}

t_hit_record	record_init(void)
{
	t_hit_record	record;

	record.tmin = EPSILON;	//극소치
	record.tmax = INFINITY;	//극대치
	return (record);
}

t_bool      hit_sphere(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sp;
	t_vector  oc;
	double  a;
	double  half_b;
	double  c;
	double  discriminant;
	double	sqrtd;
	double	root;

	sp = obj->element;
	oc = vminus(ray->origin, sp->center);
	a = vlength_pow2(ray->d_unit);
	half_b = vdot(oc, ray->d_unit);
	c = vlength_pow2(oc) - sp->radius2;
	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
	set_face_normal(ray, rec);
	rec->albedo = obj->albedo;
	return (TRUE);
}

t_bool hit_plane(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	t_plane		*pl;
	double		t;
	t_vector	p;
	double		denominator;
	t_vector	oc;

	pl = obj->element;
	denominator = vdot(pl->normal, ray->d_unit);
	if (denominator > EPSILON || denominator < -EPSILON)
	{
		oc = vminus(pl->origin, ray->origin);
		t = vdot(oc, pl->normal) / denominator;
		if (t > rec->tmin && t < rec->tmax)
		{
			rec->t = t;
			rec->p = ray_at(ray, t);
			rec->normal = vunit(pl->normal);
			set_face_normal(ray, rec);
			rec->albedo = obj->albedo;
			return (TRUE);
		}
	}
	return (FALSE);
}

// t_bool hit_cylinder(t_object *obj, t_ray *ray, t_hit_record *rec)
// {
//     t_cylinder *cy = obj->element;
//     t_vector oc = vminus(ray->origin, cy->origin);

//     double a = vdot(ray->d_unit, ray->d_unit) - pow(vdot(ray->d_unit, cy->axis), 2);
//     double b = vdot(oc, ray->d_unit) - vdot(ray->d_unit, cy->axis) * vdot(oc, cy->axis);
//     double c = vdot(oc, oc) - pow(vdot(oc, cy->axis), 2) - pow(cy->radius, 2);

//     double discriminant = b * b - a * c;
//     if (discriminant < 0)
//         return FALSE;

//     double t = (-b - sqrt(discriminant)) / a;
//     t_vector p = ray_at(ray, t);
//     t_vector op = vminus(p, cy->origin);

//     double proj1 = vdot(op, cy->axis);
//     double proj2 = vdot(ray->d_unit, cy->axis);

//     if (proj1 < 0 || proj1 > cy->height || proj2 == 0)
//     {
//         t = (-b + sqrt(discriminant)) / a;
//         p = ray_at(ray, t);
//         op = vminus(p, cy->origin);
//         proj1 = vdot(op, cy->axis);
//         proj2 = vdot(ray->d_unit, cy->axis);

//         if (proj1 < 0 || proj1 > cy->height || proj2 == 0)
//             return FALSE;
//     }

//     if (vlength(op) <= cy->radius && vdot(op, cy->axis) >= 0 && vdot(op, cy->axis) <= cy->height)
//     {
//         rec->t = t;
//         rec->p = p;
//         rec->normal = vunit(vminus(op, vmult(cy->axis, proj1 / vlength(cy->axis))));
//         set_face_normal(ray, rec);
//         rec->albedo = obj->albedo;
//         return TRUE;
//     }

//     return FALSE;
// }

// t_bool	hit_cap(t_ray *ray, t_hit_record *rec, t_vector center, double radius, t_vector axis, double min_t)
// {
// 	double t = (vdot(axis, vminus(center, ray->origin)) / vdot(axis, ray->d_unit));
// 	if (t < min_t || t > rec->tmax)
// 		return FALSE;
// 	t_vector p = ray_at(ray, t);
// 	t_vector dist = vminus(p, center);
// 	if (vdot(dist, dist) > pow(radius, 2))
// 		return FALSE;
// 	rec->t = t;
// 	rec->p = p;
// 	rec->normal = axis;
// 	set_face_normal(ray, rec);
// 	return TRUE;
// }

t_bool	hit_cap(t_ray *ray, t_hit_record *rec, t_vector center, double radius, t_vector axis, double min_t)
{
	double t = (vdot(axis, vminus(center, ray->origin)) / vdot(axis, ray->d_unit));
	if (t < min_t || t > rec->tmax)
		return FALSE;
	t_vector p = ray_at(ray, t);
	t_vector dist = vminus(p, center);
	if (vdot(dist, dist) > pow(radius, 2))
		return FALSE;
	rec->t = t;
	rec->p = p;
	if (vdot(vminus(ray->origin, center), axis) < 0)
		rec->normal = axis;
	else
		rec->normal = vmult(axis, -1);
	set_face_normal(ray, rec);
	return TRUE;
}

t_bool	hit_cylinder(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	double a, b, c, discriminant;
	double t1, t2;
	double hit_t = INFINITY;
	t_bool hit = FALSE;

	cy = obj->element;
	t_vector oc = vminus(ray->origin, cy->origin);
	a = vdot(ray->d_unit, ray->d_unit) - pow(vdot(ray->d_unit, cy->axis), 2);
	b = 2 * (vdot(ray->d_unit, oc) - vdot(ray->d_unit, cy->axis) * vdot(oc, cy->axis));
	c = vdot(oc, oc) - pow(vdot(oc, cy->axis), 2) - pow(cy->radius, 2);

	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0)
	{
		t1 = (-b - sqrt(discriminant)) / (2 * a);
		t2 = (-b + sqrt(discriminant)) / (2 * a);
		double y1 = vdot(vminus(ray_at(ray, t1), cy->origin), cy->axis);
		double y2 = vdot(vminus(ray_at(ray, t2), cy->origin), cy->axis);

		if (y1 > 0 && y1 < cy->height && t1 > rec->tmin && t1 < rec->tmax)
		{
			hit = TRUE;
			hit_t = t1;
		}
		if (y2 > 0 && y2 < cy->height && t2 > rec->tmin && t2 < rec->tmax)
		{
			hit = TRUE;
			hit_t = (t2 < hit_t) ? t2 : hit_t;
		}
	}

	// check for hit on cap ends
	if (hit_cap(ray, rec, cy->origin, cy->radius, cy->axis, 0) && rec->t < hit_t)
	{
		hit = TRUE;
		hit_t = rec->t;
	}
	t_vector top_centroid = vplus(cy->origin, vmult(cy->axis, cy->height));
	if (hit_cap(ray, rec, top_centroid, cy->radius, cy->axis, 0) && rec->t < hit_t)
	{
		hit = TRUE;
		hit_t = rec->t;
	}

	if (hit)
	{
		rec->t = hit_t;
		rec->p = ray_at(ray, hit_t);
		t_vector op = vminus(rec->p, cy->origin);
		rec->normal = vunit(vminus(op, vmult(cy->axis, vdot(op, cy->axis))));
		set_face_normal(ray, rec);
		rec->albedo = obj->albedo;
	}

	return hit;
}

// t_bool	hit_cylinder(t_object *obj, t_ray *ray, t_hit_record *rec)
// {
// 	t_cylinder	*cy;
// 	double a, b, c, discriminant;
// 	double t1, t2;

// 	cy = obj->element;
// 	t_vector oc = vminus(ray->origin, cy->origin);
// 	a = vdot(ray->d_unit, ray->d_unit) - pow(vdot(ray->d_unit, cy->axis), 2);
// 	b = 2 * (vdot(ray->d_unit, oc) - vdot(ray->d_unit, cy->axis) * vdot(oc, cy->axis));
// 	c = vdot(oc, oc) - pow(vdot(oc, cy->axis), 2) - pow(cy->radius, 2);

// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant < 0)
// 		return FALSE;

// 	t1 = (-b - sqrt(discriminant)) / (2 * a);
// 	t2 = (-b + sqrt(discriminant)) / (2 * a);

// 	double t = fmin(t1, t2);
// 	double y = vdot(vminus(ray_at(ray, t), cy->origin), cy->axis);
// 	if (y < 0 || y > cy->height)
// 	{
// 		if (t1 > rec->tmin && t1 < rec->tmax)
// 			t = t1;
// 		else if (t2 > rec->tmin && t2 < rec->tmax)
// 			t = t2;
// 		else
// 			return FALSE;
// 		y = vdot(vminus(ray_at(ray, t), cy->origin), cy->axis);
// 		if (y < 0 || y > cy->height)
// 			return FALSE;
// 	}

// 	rec->t = t;
// 	rec->p = ray_at(ray, t);
// 	rec->normal = vunit(vminus(vminus(rec->p, cy->origin), vmult(cy->axis, (y / vlength(cy->axis)))));
// 	set_face_normal(ray, rec);
// 	rec->albedo = obj->albedo;
// 	return TRUE;
// }

// t_bool		hit_plane(t_object *obj, t_ray *ray, t_hit_record *rec)
// {
// 	t_plane		*pl;
// 	t_vector	oc;
// 	double		cosine;
// 	double		root;
// 	double		t;

// 	pl = obj->element;
// 	oc = vminus(pl->origin, ray->origin);
// 	cosine = vdot(oc, pl->normal) / vlength(oc);
// 	if (cosine == 0)
// 		return (FALSE);
// 	root = vdot(ray->d_unit, pl->normal) / cosine;
// 	if (root != 0)
// 		return (FALSE);
// 	rec->t = t;
// 	rec->p = ray_at(ray, t);
// 	rec->normal = pl->normal;
// 	set_face_normal(ray, rec);
// 	rec->albedo = obj->albedo;
// 	return (TRUE);
// }

t_ray		ray_primary(t_camera *cam, double u, double v)
{
	t_ray   ray;

	ray.origin = cam->origin;
	ray.d_unit = vunit(vminus(vplus(cam->left_bottom, (vplus(vmult(cam->horizontal, u), vmult(cam->vertical, v)))), cam->origin));
	//left_bottom+hor*u+ver*v - origin
	// ray.c_value = vlength(vminus(vector(u, v, cam->focal_length), cam->origin));
	return (ray);
}

// t_ray		ray_primary(t_camera *cam, double u, double v)
// {
// 	t_ray   ray;

// 	ray.origin = cam->origin;
// 	t_vector hor = vmult(cam->horizontal, u);
// 	t_vector ver = vmult(cam->vertical, v);
// 	t_vector destination = vplus(cam->left_bottom, vplus(hor, ver));
// 	ray.d_unit = vunit(vminus(destination, cam->origin));

// 	return (ray);
// }

t_vector	ray_color(t_map	*map)
{
	double  		t;
	t_vector		n;

	map->rec = record_init(); //P = O + v*t의 t값 초기 범위 설정
	if (hit(map->world, &map->ray, &map->rec)) //광선이 물체에 맞았다면
		return (phong_lighting(map));	//퐁 라이트닝 모델 적용
	else	//아닐경우 배경 적용
	{
		t = 0.5 * (map->ray.d_unit.y + 1.0);
		return (vplus(vmult(vector(1, 1, 1), 1.0 - t), vmult(vector(0.0, 0.0, 0.0), t)));
	}
}

t_map	*map_init(void)
{
	t_map		*map;
	t_object	*world;
	t_object	*light;
	double		ka;

	if(!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	map->canvas = canvas(1280, 720);
	map->camera = camera(&map->canvas, vector(0,0,0), 90);
	double r = cos(M_PI / 4);
	world = object(SP, sphere(vector(-r, 0, -1), r), vector(0,0,1));
	oadd(&world, object(SP, sphere(vector(r, 0, -1), r), vector(1,0,0)));
	// world = object(SP, sphere(vector(-2, 0, -5), 2), vector(0.5, 0, 0));
	// oadd(&world, object(SP, sphere(vector(2, 0, -5), 1), vector(0, 0.5, 0)));
	// oadd(&world, object(SP, sphere(vector(1, -1, -7), 2), vector(0, 0, 0.5)));
	// oadd(&world, object(SP, sphere(vector(7, 2, -6), 0.4), vector(0.2, 0.5, 0.3)));
	// oadd(&world, object(SP, sphere(vector(3, 4, -3), 1.3), vector(0.1, 0.1, 0.1)));
	// oadd(&world, object(SP, sphere(vector(0, -1000, 0), 995), vector(1, 1, 1)));
	// oadd(&world, object(PL, plane(vector(0,0,-1000), vector(0,0.4,0.7)), vector(0.3,0.5,0.7)));
	// oadd(&world, object(CY, cylinder(vector(10, 10, -15), vector(0.3, 1, 0), 5, 14), vector(0.1, 0.45, 0.6)));
	// oadd(&world, object(CY, cylinder(vector(-20, 10, -15), vector(1, 0, 0), 3.5, 20), vector(0.5, 0.45, 0.6)));
	map->world = world;
	light = object(LIGHT_POINT, light_point(vector(50, 50, 50), vector(1, 1, 1), 0.5), vector(0, 0, 0));
	map->light = light;
	ka = 0.2; // abmient brightness
	map->ambient = vmult(vector(1, 1, 1), ka);
	return (map);
}
