
#include "../include/cub3d.h"

void	my_mlx_pixel_put2(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_line_re(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;

	dx = x1 - x0;
	dy = y1 - y0;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	x = x0;
	y = y0;
	while (steps--)
	{
		my_mlx_pixel_put2(data, round(x), round(y), color);
		x += x_inc;
		y += y_inc;
	}
}

int	calculate_width(char **map)
{
	int max_width = 0;
	int current_width;
	int i = 0;

	while (map[i])
	{
		current_width = 0;
		while (map[i][current_width])
			current_width++;
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width); // Return width in map units (tiles)
}

int calculate_height(char **map)
{
	int height;

	height = 0;
	while (map[height])
		height++;
	return (height); // Return height in map units (tiles)
}

float normalizeAngle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

int has_wall_at(t_data *data, float x, float y)
{
	int mapGridIndexX = floor(x / TILE_SIZE);
	int mapGridIndexY = floor(y / TILE_SIZE);

	if (mapGridIndexY < 0 || mapGridIndexY >= calculate_height(data->map))
		return ( 1);

	if (mapGridIndexX < 0 || mapGridIndexX >= (int)ft_strlen(data->map[mapGridIndexY]))
		return ( 1) ;

	return (data->map[mapGridIndexY][mapGridIndexX] == '1');
}

float	distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

int	castRay(t_data *data, int columId, float rayAngle)
{
	/*=====================Ray Direction======================================*/
	data->rays[columId].isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
	data->rays[columId].isRayFacingUp = !data->rays[columId].isRayFacingDown;
	data->rays[columId].isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
	data->rays[columId].isRayFacingLeft = !data->rays[columId].isRayFacingRight;

	/*=====================Horizontal Intersection============================*/
	float	horzWallHitX = 0.0;
	float	horzWallHitY = 0.0;
	float	horzHitDistance = FLT_MAX;
	int		foundHorzWallHit = 0;

	float	yintercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
	if (data->rays[columId].isRayFacingDown)
		yintercept += TILE_SIZE;

	float xintercept = data->player.x + (yintercept - data->player.y) / tan(rayAngle);

	float ystep = TILE_SIZE;
	ystep *= data->rays[columId].isRayFacingUp ? -1 : 1;

	float xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (data->rays[columId].isRayFacingLeft && xstep > 0) ? -1 : 1;
	xstep *= (data->rays[columId].isRayFacingRight && xstep < 0) ? -1 : 1;

	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	// printf("nextHorzTouchX: %f | nextHorzTouchY: %f\n", nextHorzTouchX, nextHorzTouchY);

	if (data->rays[columId].isRayFacingUp)
		nextHorzTouchY -=0.002;

	while (nextHorzTouchX >= 0 && nextHorzTouchX <= calculate_width(data->map) * TILE_SIZE
			&& nextHorzTouchY >= 0 && nextHorzTouchY <= calculate_height(data->map) * TILE_SIZE)
	{
		if (has_wall_at(data, nextHorzTouchX, nextHorzTouchY))
		{
			foundHorzWallHit = 1;
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzHitDistance = distanceBetweenPoints(data->player.x, data->player.y, horzWallHitX, horzWallHitY);
			break ;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}

	/*=====================Vertical Intersection============================*/
	float	verWallHitX = 0.0;
	float	verWallHitY = 0.0;
	float	verHitDistance = FLT_MAX;
	int		foundVerWallHit = 0;

	xintercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
	if (data->rays[columId].isRayFacingRight)
		xintercept += TILE_SIZE;

	yintercept = data->player.y + (xintercept - data->player.x) * tan(rayAngle);

	xstep = TILE_SIZE;
	xstep *= data->rays[columId].isRayFacingLeft ? -1 : 1;

	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= (data->rays[columId].isRayFacingUp && ystep > 0) ? -1 : 1;
	ystep *= (data->rays[columId].isRayFacingDown && ystep < 0) ? -1 : 1;

	float nextVerTouchX = xintercept;
	float nextVerTouchY = yintercept;

	if (data->rays[columId].isRayFacingLeft)
		nextVerTouchX-=0.002;

	while (nextVerTouchX >= 0 && nextVerTouchX <= calculate_width(data->map) * TILE_SIZE
			&& nextVerTouchY >= 0 && nextVerTouchY <= calculate_height(data->map) * TILE_SIZE)
	{
		if (has_wall_at(data, nextVerTouchX, nextVerTouchY))
		{
			foundVerWallHit = 1;
			verWallHitX = nextVerTouchX;
			verWallHitY = nextVerTouchY;
			verHitDistance = distanceBetweenPoints(data->player.x, data->player.y, verWallHitX, verWallHitY);
			break ;
		}
		else
		{
			nextVerTouchX += xstep;
			nextVerTouchY += ystep;
		}
	}

	/*=====================Final Ray Properties============================*/
	data->rays[columId].rayAngle = rayAngle;

	if (foundHorzWallHit && horzHitDistance < verHitDistance)
	{
		data->rays[columId].wallHitX = horzWallHitX;
		data->rays[columId].wallHitY = horzWallHitY;
		data->rays[columId].wasHitVertical = 0;
		data->rays[columId].distance = horzHitDistance;
	}
	else if (foundVerWallHit)
	{
		data->rays[columId].wallHitX = verWallHitX;
		data->rays[columId].wallHitY = verWallHitY;
		data->rays[columId].wasHitVertical = 1;
		data->rays[columId].distance = verHitDistance;
	}
	else
	{
		data->rays[columId].wallHitX = 0;
		data->rays[columId].wallHitY = 0;
		data->rays[columId].wasHitVertical = 0;
		data->rays[columId].distance = FLT_MAX;
		return (0);
	}
	return (1);
}

void	castAllRays(t_data *data)
{
	int		i;
	float	rayAngle;

	i = 0;
	rayAngle = data->player.rotationangle - (FOV_ANGLE / 2);

	while (i < NUM_RAYS)
	{
		rayAngle = normalizeAngle(rayAngle);
		castRay(data, i, rayAngle);
		rayAngle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}

/* ============================================================================================================================= */

// #include "../include/cub3d.h"

// //
// // Utility functions
// //

// float distanceBetweenPoints(float x1, float y1, float x2, float y2)
// {
// 	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
// }

// int calculate_width(char **map)
// {
// 	int max_width = 0;
// 	int current_width;
// 	int i = 0;

// 	while (map[i])
// 	{
// 		current_width = 0;
// 		while (map[i][current_width])
// 			current_width++;
// 		if (current_width > max_width)
// 			max_width = current_width;
// 		i++;
// 	}
// 	return (max_width);
// }

// int calculate_height(char **map)
// {
// 	int height;

// 	height = 0;
// 	while (map[height])
// 		height++;
// 	return (height);
// }

// float normalizeAngle(float angle)
// {
// 	angle = fmod(angle, 2 * M_PI);
// 	if (angle < 0)
// 		angle += (2 * M_PI);
// 	return (angle);
// }

// int has_wall_at(t_data *data, float x, float y)
// {
// 	int mapGridIndexX = floor(x / TILE_SIZE);
// 	int mapGridIndexY = floor(y / TILE_SIZE);

// 	if (mapGridIndexY < 0 || mapGridIndexY >= calculate_height(data->map))
// 		return (1);

// 	if (mapGridIndexX < 0 || mapGridIndexX >= (int)ft_strlen(data->map[mapGridIndexY]))
// 		return (1);

// 	return (data->map[mapGridIndexY][mapGridIndexX] == '1');
// }

// //
// // Raycasting Helper Functions
// //

// void	set_ray_direction(t_data *data, int columId, float rayAngle)
// {
// 	data->rays[columId].isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
// 	data->rays[columId].isRayFacingUp = !data->rays[columId].isRayFacingDown;
// 	data->rays[columId].isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
// 	data->rays[columId].isRayFacingLeft = !data->rays[columId].isRayFacingRight;
// }

// void	find_horz_hit(t_data *data, int columId, float rayAngle, float *horz_hit_dist, float *wall_x, float *wall_y)
// {
// 	float	yintercept, xintercept;
// 	float	ystep, xstep;
// 	float	nextHorzTouchX, nextHorzTouchY;

// 	yintercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
// 	if (data->rays[columId].isRayFacingDown)
// 		yintercept += TILE_SIZE;
// 	xintercept = data->player.x + (yintercept - data->player.y) / tan(rayAngle);

// 	ystep = TILE_SIZE;
// 	ystep *= data->rays[columId].isRayFacingUp ? -1 : 1;

// 	xstep = TILE_SIZE / tan(rayAngle);
// 	xstep *= (data->rays[columId].isRayFacingLeft && xstep > 0) ? -1 : 1;
// 	xstep *= (data->rays[columId].isRayFacingRight && xstep < 0) ? -1 : 1;

// 	nextHorzTouchX = xintercept;
// 	nextHorzTouchY = yintercept;

// 	if (data->rays[columId].isRayFacingUp)
// 		nextHorzTouchY -= 0.002;

// 	while (nextHorzTouchX >= 0 && nextHorzTouchX <= calculate_width(data->map) * TILE_SIZE && nextHorzTouchY >= 0 && nextHorzTouchY <= calculate_height(data->map) * TILE_SIZE)
// 	{
// 		if (has_wall_at(data, nextHorzTouchX, nextHorzTouchY))
// 		{
// 			*wall_x = nextHorzTouchX;
// 			*wall_y = nextHorzTouchY;
// 			*horz_hit_dist = distanceBetweenPoints(data->player.x, data->player.y, *wall_x, *wall_y);
// 			return;
// 		}
// 		else
// 		{
// 			nextHorzTouchX += xstep;
// 			nextHorzTouchY += ystep;
// 		}
// 	}
// }

// void find_ver_hit(t_data *data, int columId, float rayAngle, float *ver_hit_dist, float *wall_x, float *wall_y)
// {
// 	float xintercept, yintercept;
// 	float xstep, ystep;
// 	float nextVerTouchX, nextVerTouchY;

// 	xintercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
// 	if (data->rays[columId].isRayFacingRight)
// 		xintercept += TILE_SIZE;
// 	yintercept = data->player.y + (xintercept - data->player.x) * tan(rayAngle);

// 	xstep = TILE_SIZE;
// 	xstep *= data->rays[columId].isRayFacingLeft ? -1 : 1;

// 	ystep = TILE_SIZE * tan(rayAngle);
// 	ystep *= (data->rays[columId].isRayFacingUp && ystep > 0) ? -1 : 1;
// 	ystep *= (data->rays[columId].isRayFacingDown && ystep < 0) ? -1 : 1;

// 	nextVerTouchX = xintercept;
// 	nextVerTouchY = yintercept;

// 	if (data->rays[columId].isRayFacingLeft)
// 		nextVerTouchX -= 0.002;

// 	while (nextVerTouchX >= 0 && nextVerTouchX <= calculate_width(data->map) * TILE_SIZE && nextVerTouchY >= 0 && nextVerTouchY <= calculate_height(data->map) * TILE_SIZE)
// 	{
// 		if (has_wall_at(data, nextVerTouchX, nextVerTouchY))
// 		{
// 			*wall_x = nextVerTouchX;
// 			*wall_y = nextVerTouchY;
// 			*ver_hit_dist = distanceBetweenPoints(data->player.x, data->player.y, *wall_x, *wall_y);
// 			return;
// 		}
// 		else
// 		{
// 			nextVerTouchX += xstep;
// 			nextVerTouchY += ystep;
// 		}
// 	}
// }

// //
// // Main Raycasting Functions
// //

// int castRay(t_data *data, int columId, float rayAngle)
// {
// 	float horz_hit_dist = FLT_MAX;
// 	float ver_hit_dist = FLT_MAX;
// 	float horz_wall_x, horz_wall_y;
// 	float ver_wall_x, ver_wall_y;

// 	set_ray_direction(data, columId, rayAngle);

// 	find_horz_hit(data, columId, rayAngle, &horz_hit_dist, &horz_wall_x, &horz_wall_y);
// 	find_ver_hit(data, columId, rayAngle, &ver_hit_dist, &ver_wall_x, &ver_wall_y);

// 	data->rays[columId].rayAngle = rayAngle;
// 	if (horz_hit_dist < ver_hit_dist)
// 	{
// 		data->rays[columId].distance = horz_hit_dist;
// 		data->rays[columId].wasHitVertical = 0;
// 		data->rays[columId].wallHitX = horz_wall_x;
// 		data->rays[columId].wallHitY = horz_wall_y;
// 	}
// 	else
// 	{
// 		data->rays[columId].distance = ver_hit_dist;
// 		data->rays[columId].wasHitVertical = 1;
// 		data->rays[columId].wallHitX = ver_wall_x;
// 		data->rays[columId].wallHitY = ver_wall_y;
// 	}

// 	if (data->rays[columId].distance == FLT_MAX)
// 		return (0);
// 	return (1);
// }

// void castAllRays(t_data *data)
// {
// 	int i;
// 	float rayAngle;

// 	i = 0;
// 	rayAngle = data->player.rotationangle - (FOV_ANGLE / 2);

// 	while (i < NUM_RAYS)
// 	{
// 		rayAngle = normalizeAngle(rayAngle);
// 		castRay(data, i, rayAngle);
// 		rayAngle += FOV_ANGLE / NUM_RAYS;
// 		i++;
// 	}
// }

/* ============================================================================================================================= */

/* =================================it's work just some change=================================================================================== */

// #include "../include/cub3d.h"

// /*
// ** Utility functions
// */

// float distanceBetweenPoints(float x1, float y1, float x2, float y2)
// {
//     return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
// }

// int calculate_width(char **map)
// {
//     int max_width;
//     int current_width;
//     int i;

//     max_width = 0;
//     i = 0;
//     while (map[i])
//     {
//         current_width = 0;
//         while (map[i][current_width])
//             current_width++;
//         if (current_width > max_width)
//             max_width = current_width;
//         i++;
//     }
//     return (max_width);
// }

// int calculate_height(char **map)
// {
//     int height;

//     height = 0;
//     while (map[height])
//         height++;
//     return (height);
// }

// float normalizeAngle(float angle)
// {
//     float new_angle;

//     new_angle = fmod(angle, 2 * M_PI);
//     if (new_angle < 0)
//         new_angle += (2 * M_PI);
//     return (new_angle);
// }

// int has_wall_at(t_data *data, float x, float y)
// {
//     int map_grid_x;
//     int map_grid_y;

//     map_grid_x = floor(x / TILE_SIZE);
//     map_grid_y = floor(y / TILE_SIZE);
//     if (map_grid_y < 0 || map_grid_y >= calculate_height(data->map))
//         return (1);
//     if (map_grid_x < 0 || map_grid_x >= (int)ft_strlen(data->map[map_grid_y]))
//         return (1);
//     return (data->map[map_grid_y][map_grid_x] == '1');
// }

// /*
// ** Raycasting Helper Functions
// */

// typedef struct s_ray_params
// {
//     float yintercept;
//     float xintercept;
//     float ystep;
//     float xstep;
// }   t_ray_params;

// void    set_ray_direction(t_ray *ray, float rayAngle)
// {
//     ray->isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
//     ray->isRayFacingUp = !ray->isRayFacingDown;
//     ray->isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
//     ray->isRayFacingLeft = !ray->isRayFacingRight;
// }

// t_ray_params    set_horz_params(t_data *data, t_ray *ray, float rayAngle)
// {
//     float yintercept;
//     float xintercept;
//     float ystep;
//     float xstep;

//     yintercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
//     if (ray->isRayFacingDown)
//         yintercept += TILE_SIZE;
//     xintercept = data->player.x + (yintercept - data->player.y) / tan(rayAngle);
//     ystep = TILE_SIZE;
//     ystep *= ray->isRayFacingUp ? -1 : 1;
//     xstep = TILE_SIZE / tan(rayAngle);
//     if (ray->isRayFacingLeft && xstep > 0)
//         xstep *= -1;
//     if (ray->isRayFacingRight && xstep < 0)
//         xstep *= -1;
//     return ((t_ray_params){yintercept, xintercept, ystep, xstep});
// }

// t_ray_params    set_ver_params(t_data *data, t_ray *ray, float rayAngle)
// {
//     float xintercept;
//     float yintercept;
//     float xstep;
//     float ystep;

//     xintercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
//     if (ray->isRayFacingRight)
//         xintercept += TILE_SIZE;
//     yintercept = data->player.y + (xintercept - data->player.x) * tan(rayAngle);
//     xstep = TILE_SIZE;
//     xstep *= ray->isRayFacingLeft ? -1 : 1;
//     ystep = TILE_SIZE * tan(rayAngle);
//     if (ray->isRayFacingUp && ystep > 0)
//         ystep *= -1;
//     if (ray->isRayFacingDown && ystep < 0)
//         ystep *= -1;
//     return ((t_ray_params){yintercept, xintercept, ystep, xstep});
// }

// void    find_horz_hit(t_data *data, t_ray *ray, t_ray_params params, float *hit_dist, float *wall_x, float *wall_y)
// {
//     float next_x;
//     float next_y;

//     next_x = params.xintercept;
//     next_y = params.yintercept;
//     if (ray->isRayFacingUp)
//         next_y -= 0.002;
//     while (next_x >= 0 && next_x <= calculate_width(data->map) * TILE_SIZE && next_y >= 0 && next_y <= calculate_height(data->map) * TILE_SIZE)
//     {
//         if (has_wall_at(data, next_x, next_y))
//         {
//             *wall_x = next_x;
//             *wall_y = next_y;
//             *hit_dist = distanceBetweenPoints(data->player.x, data->player.y, next_x, next_y);
//             return ;
//         }
//         next_x += params.xstep;
//         next_y += params.ystep;
//     }
// }

// void    find_ver_hit(t_data *data, t_ray *ray, t_ray_params params, float *hit_dist, float *wall_x, float *wall_y)
// {
//     float next_x;
//     float next_y;

//     next_x = params.xintercept;
//     next_y = params.yintercept;
//     if (ray->isRayFacingLeft)
//         next_x -= 0.002;
//     while (next_x >= 0 && next_x <= calculate_width(data->map) * TILE_SIZE && next_y >= 0 && next_y <= calculate_height(data->map) * TILE_SIZE)
//     {
//         if (has_wall_at(data, next_x, next_y))
//         {
//             *wall_x = next_x;
//             *wall_y = next_y;
//             *hit_dist = distanceBetweenPoints(data->player.x, data->player.y, next_x, next_y);
//             return ;
//         }
//         next_x += params.xstep;
//         next_y += params.ystep;
//     }
// }

// void    set_final_hit(t_ray *ray, float horz_dist, float ver_dist, float horz_x, float horz_y, float ver_x, float ver_y)
// {
//     if (horz_dist < ver_dist)
//     {
//         ray->distance = horz_dist;
//         ray->wasHitVertical = 0;
//         ray->wallHitX = horz_x;
//         ray->wallHitY = horz_y;
//     }
//     else
//     {
//         ray->distance = ver_dist;
//         ray->wasHitVertical = 1;
//         ray->wallHitX = ver_x;
//         ray->wallHitY = ver_y;
//     }
// }

// /*
// ** Main Raycasting Functions
// */

// int castRay(t_data *data, int columId, float rayAngle)
// {
//     t_ray_params horz_params;
//     t_ray_params ver_params;
//     float        horz_dist;
//     float        ver_dist;
//     float        horz_wall_x;
//     float        horz_wall_y;
//     float        ver_wall_x;
//     float        ver_wall_y;

//     horz_dist = FLT_MAX;
//     ver_dist = FLT_MAX;
//     horz_wall_x = 0;
//     horz_wall_y = 0;
//     ver_wall_x = 0;
//     ver_wall_y = 0;
//     set_ray_direction(&data->rays[columId], rayAngle);
//     horz_params = set_horz_params(data, &data->rays[columId], rayAngle);
//     ver_params = set_ver_params(data, &data->rays[columId], rayAngle);
//     find_horz_hit(data, &data->rays[columId], horz_params, &horz_dist, &horz_wall_x, &horz_wall_y);
//     find_ver_hit(data, &data->rays[columId], ver_params, &ver_dist, &ver_wall_x, &ver_wall_y);
//     data->rays[columId].rayAngle = rayAngle;
//     set_final_hit(&data->rays[columId], horz_dist, ver_dist, horz_wall_x, horz_wall_y, ver_wall_x, ver_wall_y);
//     if (data->rays[columId].distance == FLT_MAX)
//         return (0);
//     return (1);
// }

// void    castAllRays(t_data *data)
// {
//     int i;
//     float rayAngle;

//     i = 0;
//     rayAngle = data->player.rotationangle - (FOV_ANGLE / 2);
//     while (i < NUM_RAYS)
//     {
//         rayAngle = normalizeAngle(rayAngle);
//         castRay(data, i, rayAngle);
//         rayAngle += FOV_ANGLE / NUM_RAYS;
//         i++;
//     }
// }

/* ============================================it's work just some change=================================================================== */



/*                  the final recasting file           */
// #include "../include/cub3d.h"

// /*
// ** Utility functions
// */

// float distanceBetweenPoints(float x1, float y1, float x2, float y2)
// {
// 	float dx;
// 	float dy;

// 	dx = x2 - x1;
// 	dy = y2 - y1;
// 	return (sqrt((dx * dx) + (dy * dy)));
// }

// int calculate_width(char **map)
// {
// 	int max_w;
// 	int cur_w;
// 	int i;

// 	max_w = 0;
// 	i = 0;
// 	while (map[i])
// 	{
// 		cur_w = 0;
// 		while (map[i][cur_w])
// 			cur_w++;
// 		if (cur_w > max_w)
// 			max_w = cur_w;
// 		i++;
// 	}
// 	return (max_w);
// }

// int calculate_height(char **map)
// {
// 	int h;

// 	h = 0;
// 	while (map[h])
// 		h++;
// 	return (h);
// }

// float normalizeAngle(float angle)
// {
// 	float res;

// 	res = fmod(angle, 2 * M_PI);
// 	if (res < 0)
// 		res += (2 * M_PI);
// 	return (res);
// }

// int has_wall_at(t_data *data, float x, float y)
// {
// 	int gx;
// 	int gy;
// 	int h;

// 	gx = floor(x / TILE_SIZE);
// 	gy = floor(y / TILE_SIZE);
// 	h = calculate_height(data->map);
// 	if (gy < 0 || gy >= h)
// 		return (1);
// 	if (gx < 0 || gx >= (int)ft_strlen(data->map[gy]))
// 		return (1);
// 	return (data->map[gy][gx] == '1');
// }

// /*
// ** Raycasting Helpers
// */

// typedef struct s_ray_params
// {
// 	float yintercept;
// 	float xintercept;
// 	float ystep;
// 	float xstep;
// } t_ray_params;

// typedef struct s_hit
// {
// 	float dist;
// 	float x;
// 	float y;
// } t_hit;

// void	set_ray_direction(t_ray *ray, float angle)
// {
// 	ray->isRayFacingDown = angle > 0 && angle < M_PI;
// 	ray->isRayFacingUp = !ray->isRayFacingDown;
// 	ray->isRayFacingRight = angle < 0.5 * M_PI || angle > 1.5 * M_PI;
// 	ray->isRayFacingLeft = !ray->isRayFacingRight;
// }

// static void init_hit(t_hit *hit)
// {
// 	hit->dist = FLT_MAX;
// 	hit->x = 0;
// 	hit->y = 0;
// }

// t_ray_params	set_horz_params(t_data *data, t_ray *ray, float angle)
// {
// 	t_ray_params	p;

// 	p.yintercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
// 	if (ray->isRayFacingDown)
// 		p.yintercept += TILE_SIZE;
// 	p.xintercept = data->player.x + (p.yintercept - data->player.y) / tan(angle);
// 	p.ystep = TILE_SIZE;
// 	if (ray->isRayFacingUp)
// 		p.ystep *= -1;
// 	p.xstep = TILE_SIZE / tan(angle);
// 	if (ray->isRayFacingLeft && p.xstep > 0)
// 		p.xstep *= -1;
// 	if (ray->isRayFacingRight && p.xstep < 0)
// 		p.xstep *= -1;
// 	return (p);
// }

// t_ray_params	set_ver_params(t_data *data, t_ray *ray, float angle)
// {
// 	t_ray_params	p;

// 	p.xintercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
// 	if (ray->isRayFacingRight)
// 		p.xintercept += TILE_SIZE;
// 	p.yintercept = data->player.y + (p.xintercept - data->player.x) * tan(angle);
// 	p.xstep = TILE_SIZE;
// 	if (ray->isRayFacingLeft)
// 		p.xstep *= -1;
// 	p.ystep = TILE_SIZE * tan(angle);
// 	if (ray->isRayFacingUp && p.ystep > 0)
// 		p.ystep *= -1;
// 	if (ray->isRayFacingDown && p.ystep < 0)
// 		p.ystep *= -1;
// 	return (p);
// }

// static void get_horz_hit(t_data *data, t_ray *ray,
// 						 t_ray_params p, t_hit *hit)
// {
// 	float nx;
// 	float ny;

// 	nx = p.xintercept;
// 	ny = p.yintercept;
// 	if (ray->isRayFacingUp)
// 		ny -= 0.002;
// 	while (nx >= 0 && nx <= calculate_width(data->map) * TILE_SIZE
// 			&& ny >= 0 && ny <= calculate_height(data->map) * TILE_SIZE)
// 	{
// 		if (has_wall_at(data, nx, ny))
// 		{
// 			hit->x = nx;
// 			hit->y = ny;
// 			hit->dist = distanceBetweenPoints(data->player.x,
// 											  data->player.y, nx, ny);
// 			return;
// 		}
// 		nx += p.xstep;
// 		ny += p.ystep;
// 	}
// }

// static void get_ver_hit(t_data *data, t_ray *ray,
// 						t_ray_params p, t_hit *hit)
// {
// 	float nx;
// 	float ny;

// 	nx = p.xintercept;
// 	ny = p.yintercept;
// 	if (ray->isRayFacingLeft)
// 		nx -= 0.002;
// 	while (nx >= 0 && nx <= calculate_width(data->map) * TILE_SIZE && ny >= 0 && ny <= calculate_height(data->map) * TILE_SIZE)
// 	{
// 		if (has_wall_at(data, nx, ny))
// 		{
// 			hit->x = nx;
// 			hit->y = ny;
// 			hit->dist = distanceBetweenPoints(data->player.x,
// 											  data->player.y, nx, ny);
// 			return;
// 		}
// 		nx += p.xstep;
// 		ny += p.ystep;
// 	}
// }

// static void choose_hit(t_ray *ray, t_hit horz, t_hit ver)
// {
// 	if (horz.dist < ver.dist)
// 	{
// 		ray->distance = horz.dist;
// 		ray->wasHitVertical = 0;
// 		ray->wallHitX = horz.x;
// 		ray->wallHitY = horz.y;
// 	}
// 	else
// 	{
// 		ray->distance = ver.dist;
// 		ray->wasHitVertical = 1;
// 		ray->wallHitX = ver.x;
// 		ray->wallHitY = ver.y;
// 	}
// }

// /*
// ** Main Raycasting
// */

// int	castRay(t_data *data, int col, float angle)
// {
// 	t_hit			horz;
// 	t_hit			ver;
// 	t_ray_params	h;
// 	t_ray_params	v;

// 	set_ray_direction(&data->rays[col], angle);
// 	init_hit(&horz);
// 	init_hit(&ver);
// 	h = set_horz_params(data, &data->rays[col], angle);
// 	v = set_ver_params(data, &data->rays[col], angle);
// 	get_horz_hit(data, &data->rays[col], h, &horz);
// 	get_ver_hit(data, &data->rays[col], v, &ver);
// 	data->rays[col].rayAngle = angle;
// 	choose_hit(&data->rays[col], horz, ver);
// 	if (data->rays[col].distance == FLT_MAX)
// 		return (0);
// 	return (1);
// }

// void	castAllRays(t_data *data)
// {
// 	int		i;
// 	float	angle;

// 	i = 0;
// 	angle = data->player.rotationangle - (FOV_ANGLE / 2);
// 	while (i < NUM_RAYS)
// 	{
// 		angle = normalizeAngle(angle);
// 		castRay(data, i, angle);
// 		angle += FOV_ANGLE / NUM_RAYS;
// 		i++;
// 	}
// }
/*                  the final recasting file           */


/*

- what mean by screen_x and screen_y
- what the purpose of multipe in negative (-1) :
				horizontal:
		xstep *= (data->rays[columId].isRayFacingLeft && xstep > 0) ? -1 : 1;
		xstep *= (data->rays[columId].isRayFacingRight && xstep < 0) ? -1 : 1;
				vertical:
		ystep *= (data->rays[columId].isRayFacingUp && ystep > 0) ? -1 : 1;
		ystep *= (data->rays[columId].isRayFacingDown && ystep < 0) ? -1 : 1;
*/