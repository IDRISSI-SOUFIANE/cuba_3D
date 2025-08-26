#include "../include/cub3d.h"
#include <float.h>

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
	return (max_width * TILE_SIZE); // Return width in pixels
}


int calculate_height(char **map)
{
	int height;

	height = 0;
	while (map[height])
		height++;
	return (height * TILE_SIZE);
}


int has_wall_at(t_data *data, float x, float y)
{
	int mapGridIndexX = floor(x / TILE_SIZE);
	int mapGridIndexY = floor(y / TILE_SIZE);

	if (mapGridIndexY < 0 || mapGridIndexY >= calculate_height(data->map))
		return (1);

	if (mapGridIndexX < 0 || mapGridIndexX >= (int)ft_strlen(data->map[mapGridIndexY]))
		return ( 1) ;

	return (data->map[mapGridIndexY][mapGridIndexX] == '1');
}

void	my_mlx_pixel_put2(t_data *data, int x, int y, int color)
{
	char	*dst;

	// Check if coordinates are within the window bounds 
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	// Calculate the memory address of the pixel
	dst = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
	// Write the color to the pixel address
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

// This is the new function you asked for, specifically for drawing the rays.
// It is private to recasting.c
void	draw_ray(t_data *data, int x0, int y0, int x1, int y1)
{
	// A raycast line is drawn in yellow
	draw_line_re(data, x0, y0, x1, y1, 0xFFFF00FF);
}

// Normalize an angle to be within [0, 2*PI)
float normalizeAngle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI) + angle;
	return (angle);
}

// Find horizontal intersection distance
float find_horizontal_intersection(t_data *data, int columId, float rayAngle)
{
	float horzWallHitX, horzWallHitY;
	float nextHorzX, nextHorzY;
	float x_step, y_step;

	data->rays[columId].isRayFacingDown = (rayAngle > 0 && rayAngle < M_PI);
	data->rays[columId].isRayFacingUp = !data->rays[columId].isRayFacingDown;
	data->rays[columId].isRayFacingRight = (rayAngle < 0.5 * M_PI) || (rayAngle > 1.5 * M_PI);
	data->rays[columId].isRayFacingLeft = !data->rays[columId].isRayFacingRight;

	// Find the y-coordinate of the closest horizontal grid intersection
	horzWallHitY = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
	if (data->rays[columId].isRayFacingDown)
		horzWallHitY += TILE_SIZE;
	else
		horzWallHitY -= 1;

	// Find the x-coordinate of the closest horizontal grid intersection
	horzWallHitX = data->player.x + (horzWallHitY -  data->player.y) / tan(rayAngle);

	// Calculate the increment xstep and ystep
	y_step = TILE_SIZE;
	if (data->rays[columId].isRayFacingUp)
		y_step *= -1;

	x_step = y_step / tan(rayAngle);
	// if (data->rays[columId].isRayFacingLeft && x_step > 0)
	//     x_step *= -1;
	// if (data->rays[columId].isRayFacingRight && x_step < 0)
	//     x_step *= -1;

	nextHorzX = horzWallHitX;
	nextHorzY = horzWallHitY;

	// Correct for the ray starting on a horizontal grid line
	if (data->rays[columId].isRayFacingUp)
		nextHorzY--;
		
	// Increment x and y steps to find the wall
	// FIXED: Use hardcoded WIDTH and HEIGHT for boundary checks
	while (nextHorzX >= 0 && nextHorzX < calculate_width(data->map) && nextHorzY >= 0 && nextHorzY < calculate_height(data->map))
	{
		if (has_wall_at(data, nextHorzX, nextHorzY))
		{
			data->rays[columId].wallHitX = nextHorzX;
			data->rays[columId].wallHitY = nextHorzY;
			return (sqrt((data->player.x - data->rays[columId].wallHitX) * (data->player.x - data->rays[columId].wallHitX) +
					(data->player.y - data->rays[columId].wallHitY) * (data->player.y - data->rays[columId].wallHitY)));
		}
		else
		{
			nextHorzX += x_step;
			nextHorzY += y_step;
		}
	}
	return (FLT_MAX);
}

// Find vertical intersection distance
float find_vertical_intersection(t_data *data, int columId, float rayAngle, float horizontal_distance)
{
	float v_hit_x, v_hit_y;
	float next_v_x, next_v_y;
	float x_step, y_step;

	data->rays[columId].isRayFacingRight = (rayAngle > 1.5 * M_PI || rayAngle < 0.5 * M_PI);
	data->rays[columId].isRayFacingLeft = !data->rays[columId].isRayFacingRight;
	data->rays[columId].isRayFacingDown = (rayAngle > 0 && rayAngle < M_PI);
	data->rays[columId].isRayFacingUp = !data->rays[columId].isRayFacingDown;

	v_hit_x = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
	if (data->rays[columId].isRayFacingRight)
		v_hit_x += TILE_SIZE;
	// else
	//     v_hit_x -= 1;

	v_hit_y = data->player.y + (v_hit_x - data->player.x) * tan(rayAngle);

	x_step = TILE_SIZE;
	if (data->rays[columId].isRayFacingLeft)
		x_step *= -1;
	
	y_step = x_step * tan(rayAngle);
	if (data->rays[columId].isRayFacingUp && y_step > 0)
		y_step *= -1;
	if (data->rays[columId].isRayFacingDown && y_step < 0)
		y_step *= -1;

	next_v_x = v_hit_x;
	next_v_y = v_hit_y;
	
	// Correct for the ray starting on a vertical grid line
	if (data->rays[columId].isRayFacingLeft)
		next_v_x--;
	float distance_vert = 0;
	float final_v_x = 0;
	float final_v_y = 0;
	// FIXED: Use hardcoded WIDTH and HEIGHT for boundary checks
	while (next_v_x >= 0 && next_v_x < calculate_width(data->map) && next_v_y >= 0 && next_v_y < calculate_height(data->map))
	{
		if (has_wall_at(data, next_v_x, next_v_y))
		{
			// data->rays[columId].wallHitX = next_v_x;
			// data->rays[columId].wallHitY = next_v_y;
			final_v_x = next_v_x;
			final_v_y = next_v_y;
			distance_vert = (sqrt((data->player.x - final_v_x) * (data->player.x - final_v_x) +
					(data->player.y - final_v_y) * (data->player.y - final_v_y)));
			break;
			// return (sqrt((data->player.x - data->rays[columId].wallHitX) * (data->player.x - data->rays[columId].wallHitX) +
			// 		(data->player.y - data->rays[columId].wallHitY) * (data->player.y - data->rays[columId].wallHitY)));
		}
		else
		{
			next_v_x += x_step;
			next_v_y += y_step;
		}
	}
	if (horizontal_distance > distance_vert){ // add to change the x y for ray we cast deppanding on distance!!
		data->rays[columId].wallHitX = final_v_x;
		data->rays[columId].wallHitY = final_v_y;
		return distance_vert;
	}
	return (FLT_MAX);
}

// Cast a single ray and find its distance to the nearest wall
void    castRay(t_data *data, int columId, float rayAngle)
{
	float horizontal_distance, vertical_distance;
	
	horizontal_distance = find_horizontal_intersection(data, columId, rayAngle);
	vertical_distance = find_vertical_intersection(data, columId, rayAngle, horizontal_distance);


	if (horizontal_distance < vertical_distance)
	{
		data->rays[columId].distance = horizontal_distance;
		data->rays[columId].wasHitVertical = 0;

		// Draw the ray on the 2D map using the new draw_ray function
		draw_ray(data, data->player.x, data->player.y, data->rays[columId].wallHitX, data->rays[columId].wallHitY);
	}
	else
	{
		data->rays[columId].distance = vertical_distance;
		data->rays[columId].wasHitVertical = 1;
		// Draw the ray on the 2D map using the new draw_ray function
		draw_ray(data, data->player.x, data->player.y, data->rays[columId].wallHitX, data->rays[columId].wallHitY);
	}
}


void castAllRays(t_data *data)
{
	int		i;
	float	rayAngle;

	i = 0;
	// Start first ray from the player's FOV
	rayAngle = data->player.rotationangle - (FOV_ANGLE / 2);

	while (i < NUM_RAYS)
	{
		rayAngle = normalizeAngle(rayAngle);
	
		// Cast the single ray
		castRay(data, i, rayAngle);

		// Increment the angle for the next ray
		rayAngle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}
