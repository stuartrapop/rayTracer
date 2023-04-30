/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:30:57 by max               #+#    #+#             */
/*   Updated: 2023/04/30 13:01:21 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

t_rgb	get_specular(t_minirt minirt, t_intersect inter, \
	double angle, double specular)
{
	t_rgb	tmp_phong;
	t_vect	ldir;
	t_vect	vdir;
	t_vect	reflection;

	ldir = vector_normalize(point_subtract(inter.point, minirt.lights->origin));
	reflection.x = 2 * (vect_dot(inter.normal, ldir)) * inter.normal.x - ldir.x;
	reflection.y = 2 * (vect_dot(inter.normal, ldir)) * inter.normal.y - ldir.y;
	reflection.z = 2 * (vect_dot(inter.normal, ldir)) * inter.normal.z - ldir.z;
	reflection = vector_normalize(reflection);
	vdir = vector_normalize(point_subtract(inter.point, minirt.camera->origin));
	angle = vect_dot(reflection, vdir);
	angle = fmax(0.0, fmin(angle, 1.0));
	specular = pow(angle, PHONG_POW) * minirt.lights->intensity * PHONG_COEF;
	tmp_phong = add_intensity(minirt.lights->rgb, specular);
	return (sum_light(tmp_phong, inter.specular));
}

t_rgb	get_diffuse(t_minirt minirt, t_intersect inter, double adjustment)
{
	t_rgb	tmp;
	t_ray	lray;
	double	angle;
	double	factor;

	lray.origin = minirt.lights->origin;
	lray.direct = point_subtract(inter.point, lray.origin);
	if (closest_object(minirt, lray) != inter.index)
		return (inter.diffuse);
	angle = vect_angle(inter.normal, lray.direct);
	if (angle > 90)
		factor = fabs(cos(deg_to_rad(angle)));
	else
		return (inter.diffuse);
	adjustment = (factor * minirt.lights->intensity);
	adjustment = fmin(1.0, adjustment);
	tmp = add_light(inter.object_color, minirt.lights->rgb, adjustment);
	return (sum_light(tmp, inter.diffuse));
}

int	apply_light(t_minirt minirt, t_intersect inter)
{
	inter.specular = add_intensity(inter.object_color, 0);
	inter.diffuse = add_intensity(inter.object_color, 0);
	while (minirt.lights)
	{
		inter.diffuse = get_diffuse(minirt, inter, 0);
		inter.specular = get_specular(minirt, inter, 0, 0);
		minirt.lights = minirt.lights->next;
	}
	inter.rgb = sum_light3(inter.ambiant, inter.diffuse, inter.specular);
	return (rgb_to_int(inter.rgb));
}