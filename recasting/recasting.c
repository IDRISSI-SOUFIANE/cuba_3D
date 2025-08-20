/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:18:42 by sidrissi          #+#    #+#             */
/*   Updated: 2025/08/20 11:15:04 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	my_mlx_pixel_put2(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	// Check if coordinates are within the window bounds 
// 	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
// 		return ;
// 	// Calculate the memory address of the pixel
// 	dst = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
// 	// Write the color to the pixel address
// 	*(unsigned int *)dst = color;
// }


// void	draw_line_re(t_data *data, int x0, int y0, int x1, int y1, int color)
// {
// 	int	dx;
// 	int	dy;
// 	int	steps;
// 	float	x_inc;
// 	float	y_inc;
// 	float	x;
// 	float	y;

// 	dx = x1 - x0;
// 	dy = y1 - y0;
// 	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
// 	x_inc = dx / (float)steps;
// 	y_inc = dy / (float)steps;
// 	x = x0;
// 	y = y0;
// 	while (steps--)
// 	{
// 		my_mlx_pixel_put2(data, round(x), round(y), color);
// 		x += x_inc;
// 		y += y_inc;
// 	}
// }

// int	calculate_width(char **map)
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
// 	return (max_width * TILE_SIZE); // Return width in pixels
// }


// int calculate_height(char **map)
// {
// 	int height;

// 	height = 0;
// 	while (map[height])
// 		height++;
// 	return (height * TILE_SIZE);
// }

// float normalizeAngle(float angle)
// {
// 	angle = fmod(angle, 2 * M_PI);
// 	if (angle < 0)
// 		angle += (2 * M_PI) + angle;
// 	return (angle);
// }

// int has_wall_at(t_data *data, float x, float y)
// {
// 	int mapGridIndexX = floor(x / TILE_SIZE);
// 	int mapGridIndexY = floor(y / TILE_SIZE);

// 	if (mapGridIndexY < 0 || mapGridIndexY >= calculate_height(data->map))
// 		return (printf("--------------------> enter ----------> here1\n"), 1);

// 	if (mapGridIndexX < 0 || mapGridIndexX >= (int)ft_strlen(data->map[mapGridIndexY]))
// 		return (printf("--------------------> enter here\n"), 1) ;

// 	return (data->map[mapGridIndexY][mapGridIndexX] == '1');
// }


// float	distanceBetweenPoints(float x1, float y1, float x2, float y2)
// {
// 	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
// }

// int	castRay(t_data *data, int columId, float rayAngle)
// {
// 	(void)columId;
// 	/*=====================Horizontal============================================*/
// 	float	horzWallHitX = 0.0;
// 	float	horzWallHitY = 0.0;
// 	// float	distance =0.0;
// 	float	xintercept = 0.0;
// 	float	yintercept = 0.0;
// 	float	xstep = 0.0;
// 	float	ystep = 0.0;
// 	float	nextHorzTouchX = 0.0;
// 	float	nextHorzTouchY = 0.0;
// 	int		foundHorzWallHit = 0;
// 	float	horzHitDistance = 0.0;

// 	/*=========================================================================*/
// 	data->rays->isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
// 	data->rays->isRayFacingUp = !data->rays->isRayFacingDown;
// 	data->rays->isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
// 	data->rays->isRayFacingLeft = !data->rays->isRayFacingRight;
// 	/*=========================================================================*/

// 	yintercept = floor (data->player.y / TILE_SIZE) * TILE_SIZE;
// 	if (data->rays->isRayFacingDown)
// 		yintercept += TILE_SIZE;
// 	xintercept = data->player.x + (yintercept - data->player.y) / tan(rayAngle);

// 	ystep = TILE_SIZE;
// 	ystep *= data->rays->isRayFacingUp ? -1 : 1;
// 	xstep = TILE_SIZE / tan(rayAngle);
// 	xstep = (data->rays->isRayFacingLeft && xstep > 0) ? -1 : 1;
// 	xstep = (data->rays->isRayFacingRight && xstep < 0) ? -1 : 1;
	
// 	nextHorzTouchX = xintercept;
// 	nextHorzTouchY = yintercept;

// 	if (data->rays->isRayFacingUp)
// 		nextHorzTouchY--;
	
// 	while ((nextHorzTouchX >= 0 && nextHorzTouchX <= calculate_width(data->map))
// 			&& (nextHorzTouchY >= 0 && nextHorzTouchY <= calculate_height(data->map)))
// 	{
// 		if (has_wall_at(data, nextHorzTouchX, nextHorzTouchY))
// 		{
// 			foundHorzWallHit = 1;
// 			horzWallHitX = nextHorzTouchX;
// 			horzWallHitY = nextHorzTouchY;
// 			horzHitDistance = distanceBetweenPoints(data->player.x, data->player.y, horzWallHitX, horzWallHitY);
// 			break ;
// 		}
// 		else
// 		{
// 			nextHorzTouchX += xstep;
// 			nextHorzTouchY += ystep;
// 		}
// 	}
// 	/*=====================Horizontal============================================*/

// 	/*=====================vertical============================================*/
// 	float	verWallHitX = 0.0;
// 	float	verWallHitY = 0.0;
// 	// float	distance =0.0;
// 	// float	xintercept = 0.0;
// 	// float	yintercept = 0.0;
// 	// float	xstep = 0.0;
// 	// float	ystep = 0.0;
// 	float	nextVerTouchX = 0.0;
// 	float	nextVerTouchY = 0.0;
// 	int		foundVerWallHit = 0;
// 	float	verHitDistance = 0.0;

// 	/*=========================================================================*/
// 	data->rays->isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
// 	data->rays->isRayFacingUp = !data->rays->isRayFacingDown;
// 	data->rays->isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
// 	data->rays->isRayFacingLeft = !data->rays->isRayFacingRight;
// 	/*=========================================================================*/

// 	xintercept = floor (data->player.x / TILE_SIZE) * TILE_SIZE;
// 	if (data->rays->isRayFacingRight)
// 		yintercept += TILE_SIZE;
// 	yintercept = data->player.y + (xintercept - data->player.x) * tan(rayAngle);

// 	xstep = TILE_SIZE;
// 	xstep *= data->rays->isRayFacingLeft ? -1 : 1;
	
// 	ystep = TILE_SIZE * tan(rayAngle);
// 	ystep = (data->rays->isRayFacingUp && xstep > 0) ? -1 : 1;
// 	xstep = (data->rays->isRayFacingDown && xstep < 0) ? -1 : 1;
	
// 	nextVerTouchX = xintercept;
// 	nextVerTouchY = yintercept;

// 	if (data->rays->isRayFacingLeft)
// 		nextVerTouchX--;
	
// 	while ((nextVerTouchX >= 0 && nextVerTouchX <= calculate_width(data->map))
// 			&& (nextVerTouchY >= 0 && nextVerTouchY <= calculate_height(data->map)))
// 	{
// 		if (has_wall_at(data, nextVerTouchX, nextVerTouchY))
// 		{
// 			foundVerWallHit = 1;
// 			verWallHitX = nextVerTouchX;
// 			verWallHitY = nextVerTouchY;
// 			verHitDistance = distanceBetweenPoints(data->player.x, data->player.y, verWallHitX, verWallHitY);
// 			break ;
// 		}
// 		else
// 		{
// 			nextVerTouchX += xstep;
// 			nextVerTouchY += ystep;
// 		}
// 	}
// 	/*=====================vertical============================================*/

// 	// chouse the smallest distance
// 	float	wallHitX;
// 	float	wallHitY;

// 	if (foundHorzWallHit && horzHitDistance < verHitDistance)
// 	{
// 		wallHitX = horzWallHitX;
// 		wallHitY = horzWallHitY;
// 		data->rays[columId].wasHitVertical = 0;
// 		data->rays[columId].distance = horzHitDistance;
// 	}
// 	else if (foundVerWallHit)
// 	{
// 		wallHitX = verWallHitX;
// 		wallHitY = verWallHitY;	
// 		data->rays[columId].wasHitVertical = 1;
// 		data->rays[columId].distance = verHitDistance;
// 	}
// 	else
// 		return (0);
	
// 	data->rays[columId].rayAngle = rayAngle;
// 	data->rays[columId].wallHitX = wallHitX;
// 	data->rays[columId].wallHitY = wallHitY;


// 	// printf("horzHitDistance : %f | verHitDistance : %f\n", horzHitDistance, verHitDistance);

// 	return (1);
// }

// void	castAllRays(t_data *data)
// {
// 	int		i;
// 	float	rayAngle;

// 	i = 0;
// 	// Start first ray from the player's FOV
// 	rayAngle = data->player.rotationangle - (FOV_ANGLE / 2);

// 	while (i < NUM_RAYS)
// 	{
// 		rayAngle = normalizeAngle(rayAngle);
	
// 		// Cast the single ray
// 		castRay(data, i, rayAngle);

// 		// Increment the angle for the next ray
// 		rayAngle += FOV_ANGLE / NUM_RAYS;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < NUM_RAYS)
// 	{
// 		draw_line_re(data, data->player.screen_x, data->player.screen_y, (data->rays[i].wallHitX  - data->player.x), (data->rays[i].wallHitY - data->player.y), 0xff0000);
// 		i++;
// 	}
// }







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

// int has_wall_at(t_data *data, float x, float y)
// {
// 	int mapGridIndexX = floor(x / TILE_SIZE);
// 	int mapGridIndexY = floor(y / TILE_SIZE);
	
// 	/* so he calculte the langest line of width and height */
// 	// printf("calculate_width(data->map) : %d\n", calculate_width(data->map));
// 	// printf("calculate_height(data->map) : %d\n", calculate_height(data->map));

// 	// sleep(1);

	
// 	if (mapGridIndexY < 0 || mapGridIndexY >= calculate_height(data->map))
// 		return (1);

// 	if (mapGridIndexX < 0 || mapGridIndexX >= calculate_width(data->map))
// 		return (1) ;

	
// 	// sleep(1);

// 	printf("mapGridIndexY : %d | mapGridIndexX: %d\n ", mapGridIndexY, mapGridIndexX);

// 	return (data->map[mapGridIndexY][mapGridIndexX] == '1');
// }



int has_wall_at(t_data *data, float x, float y)
{
	int mapGridIndexX = floor(x / TILE_SIZE);
	int mapGridIndexY = floor(y / TILE_SIZE);

	if (mapGridIndexY < 0 || mapGridIndexY >= calculate_height(data->map))
		return (printf("--------------------> enter ----------> here1\n"), 1);

	if (mapGridIndexX < 0 || mapGridIndexX >= (int)ft_strlen(data->map[mapGridIndexY]))
		return (printf("--------------------> enter here\n"), 1) ;

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
		nextHorzTouchY--;
	
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
		nextVerTouchX--;

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

	i = 0;
	while (i < NUM_RAYS)
	{
		draw_line_re(data,
			data->player.x,
			data->player.y,
			data->rays[i].wallHitX,
			data->rays[i].wallHitY,
			0xff0000);
		i++;
	}
}


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