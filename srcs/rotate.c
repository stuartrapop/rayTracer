#include "minirt.h"

t_sphere	*change_origin_sphere(int keycode, t_sphere *sphere)
{
	if (keycode == 83)
		sphere->origin.z -= 5;
	if (keycode == 84)
		sphere->origin.z += 5;
	if (keycode == 86)
		sphere->origin.y -= 5;
	if (keycode == 87)
		sphere->origin.y += 5;
	if (keycode == 89)
		sphere->origin.x -= 5;
	if (keycode == 91)
		sphere->origin.x += 5;
	return (sphere);
}

t_vect 	change_direction_plane(int keycode, t_vect normal)
{
	if (keycode == 12)
		normal.z -= 0.2;
	if (keycode == 13)
		normal.z += 0.2;
	if (keycode == 0)
		normal.y -= 0.2;
	if (keycode == 1)
		normal.y += 0.2;
	if (keycode == 6)
		normal.x -= 0.2;
	if (keycode == 7)
		normal.x += 0.2;
	normal = vector_normalize(normal);
	return (normal);
}