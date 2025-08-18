/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:30:12 by sidrissi          #+#    #+#             */
/*   Updated: 2025/08/18 22:22:32 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// float normalizeAngle(float rayAngle)
// {
// 	if (rayAngle > 2 * M_PI)
// 		rayAngle -= 2 * M_PI;
// 	if (rayAngle < 0)
// 		rayAngle += 2 * M_PI;
// 	return (rayAngle);
// }

// // Check if a point is a wall
// int hasWallAt(t_data *data, float x, float y)
// {
// 	int mapGridIndexX;
// 	int mapGridIndexY;

// 	// Check if the coordinates are within the map bounds
// 	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
// 		return 1; // Out of bounds is a wall

// 	// Convert pixel coordinates to map grid coordinates
// 	mapGridIndexX = floor(x / TILE_SIZE);
// 	mapGridIndexY = floor(y / TILE_SIZE);

// 	// Check for wall
// 	if (data->map[mapGridIndexY][mapGridIndexX] == '1')
// 		return 1;
// 	return 0;
// }

// // Cast a single ray and find its distance to the nearest wall
// void	castRay(t_data *data, float rayAngle)
// {
// 	float	wallHitX;
// 	float	wallHitY;
// 	float	distance;
// 	// float	xstep;
// 	// float	ystep;
// 	// float	xintercept;
// 	// float	yintercept;

// 	// ... we will add more complex logic here later ...

// 	// Simplified, temporary logic to show how it would work
// 	// We would need a real ray-tracing algorithm here

// 	printf("data->player.x * TILE_SIZE : %f\n", data->player.x * TILE_SIZE);
// 	printf("data->player.y * TILE_SIZE : %f\n", data->player.y * TILE_SIZE);

	
// 	wallHitX = data->player.x * TILE_SIZE;
// 	wallHitY = data->player.y * TILE_SIZE;
// 	distance = 0; // Placeholder

// 	// This is where you would implement the ray intersection algorithm
// 	// For now, let's just make sure the basic structure works
// 	while (!hasWallAt(data, wallHitX, wallHitY)) /*&& distance < 900*/
// 	{
// 		wallHitX += cos(rayAngle);
// 		wallHitY += sin(rayAngle);
// 		distance++;
// 	}

// 	// For now, let's just draw the ray on the 2D map
// 	draw_line(data, data->player.screen_x, data->player.screen_y, rayAngle, distance);
// }

// void castAllRays(t_data *data)
// {
// 	int i;
// 	float rayAngle;

// 	i = 0;
// 	// Start first ray from the player's FOV
// 	rayAngle = data->player.rotationangle - (FOV_ANGLE / 2);

// 	printf("before: %f\n", rayAngle);
// 	while (i < NUM_RAYS)
// 	{
// 		// Normalize the angle to keep it between 0 and 2*PI
// 		rayAngle = normalizeAngle(rayAngle);
// 		// Cast the single ray
// 		castRay(data, rayAngle);

// 		// Increment the angle for the next ray
// 		rayAngle += FOV_ANGLE / NUM_RAYS;
// 		i++;
// 	}
// }

/* ==============================================================================================*/
/* ==============================================================================================*/
/* ==============================================================================================*/
/* ==============================================================================================*/
/* ==============================================================================================*/
/* ==============================================================================================*/
/* ==============================================================================================*/

float normalizeAngle(float rayAngle)
{
	if (rayAngle > 2 * M_PI)
		rayAngle -= 2 * M_PI;
	if (rayAngle < 0)
		rayAngle += 2 * M_PI;
	return (rayAngle);
}

// Check if a point is a wall
/*
int hasWallAt(t_data *data, float x, float y)
{
	int mapGridIndexX;
	int mapGridIndexY;

	// Check if the coordinates are within the map bounds
	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return 1; // Out of bounds is a wall

	// Convert pixel coordinates to map grid coordinates
	mapGridIndexX = floor(x / TILE_SIZE);
	mapGridIndexY = floor(y / TILE_SIZE);


	printf("mapGridIndexX : %d | mapGridIndexY : %d\n", mapGridIndexX, mapGridIndexY);

	// Check for wall
	if (data->map[mapGridIndexY][mapGridIndexX] == '1')
		return 1;
	return 0;
}
*/

int hasWallAt(t_data *data, float x, float y)
{
    int mapGridIndexX = floor(x / TILE_SIZE);
    int mapGridIndexY = floor(y / TILE_SIZE);

    // check bounds against the map array size (not just WIDTH/HEIGHT in pixels!)
    if (mapGridIndexY < 0 || mapGridIndexY >= HEIGHT)
        return 1;

    if (mapGridIndexX < 0 || mapGridIndexX >= (int)ft_strlen(data->map[mapGridIndexY]))
        return 1;

    return (data->map[mapGridIndexY][mapGridIndexX] == '1');
}




// Cast a single ray and find its distance to the nearest wall
void	castRay(t_data *data, float rayAngle)
{
	float	wallHitX;
	float	wallHitY;
	float	distance = 0.0;
	float	xstep;
	float	ystep;
	double	xintercept;
	double	yintercept;
	float	nextHorzTouchx;
	float	nextHorzTouchy;
	int		foundHorzWalHit = 0;

	// ... we will add more complex logic here later ...

	// Simplified, temporary logic to show how it would work
	// We would need a real ray-tracing algorithm here

	// Find the (x, y) coordinate of the closest horizontal grid intersenction (A9RAB NORTA HIROZONTAL AND VERTICAL)
	// A(xintercept, yintercept)
	// printf("data.player.y : %f\n", (data->player.y) *32);    ??????????  why y don't change just give me 0 or 32 should change?????????
	yintercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
	xintercept = data->player.x + (yintercept - data->player.y) / tan(rayAngle);
	 printf("yintercept: %f || xintercept: %f\n", yintercept,  xintercept);


	data->rays.isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
	data->rays.isRayFacingUp = !data->rays.isRayFacingDown;
	data->rays.isRayFacingRight = (rayAngle < 0.5 * M_PI) || (rayAngle > 1.5 * M_PI);
	data->rays.isRayFacingLeft = !data->rays.isRayFacingRight;

	if (data->rays.isRayFacingDown)
		yintercept += TILE_SIZE;


	// foor check ---> printf("yintercept: %f\n", yintercept);

	// calculate the increment xstep and ystep // xstep and ystep is the distance between from point to the next point 
	ystep = TILE_SIZE;
	if (data->rays.isRayFacingUp)
		ystep *= -1;
	xstep = TILE_SIZE / tan(rayAngle);
	if ((data->rays.isRayFacingLeft && xstep > 0) || (data->rays.isRayFacingRight && xstep < 0))
		xstep *= -1;

	nextHorzTouchx = xintercept;	
	nextHorzTouchy = yintercept;
	// printf("nextHorzTouchy : %f\n", nextHorzTouchy); //checking if is negative when `isRayFacingUp`
	// while (1);
	if (data->rays.isRayFacingUp)
		nextHorzTouchy--;
	// increment xstep and ystep until we find a wall
	while (nextHorzTouchx >= 0 && nextHorzTouchx <= WIDTH && nextHorzTouchy >= 0 && nextHorzTouchy < HEIGHT)
	{
		if (hasWallAt(data, nextHorzTouchx, nextHorzTouchy))
		{
			foundHorzWalHit = 1;
			wallHitX = nextHorzTouchx;
			wallHitY = nextHorzTouchy;
			draw_line(data, data->player.screen_x, data->player.screen_y, wallHitX, wallHitY);
			break ;
		}
		else
		{
			nextHorzTouchx += xstep;
			nextHorzTouchy += ystep;
		}
	}

	// For now, let's just draw the ray on the 2D map
	(void)distance;
	// draw_line(data, data->player.screen_x, data->player.screen_y, rayAngle, 10);

}

void castAllRays(t_data *data)
{
	int i;
	float rayAngle;

	i = 0;
	// Start first ray from the player's FOV
	rayAngle = data->player.rotationangle - (FOV_ANGLE / 2);

	while (i < 1)
	{
		// Normalize the angle to keep it between 0 and 2*PI
		rayAngle = normalizeAngle(rayAngle);
		// Cast the single ray
		castRay(data, rayAngle);

		// Increment the angle for the next ray
		rayAngle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}


/*

float normalizeAngle(float rayAngle)
{
	if (rayAngle > 2 * M_PI)
		rayAngle -= 2 * M_PI;
	if (rayAngle < 0)
		rayAngle += 2 * M_PI;
	return (rayAngle);
}

// Check if a point is a wall
int hasWallAt(t_data *data, float x, float y)
{
    if (x < 0 || x >= WIDTH|| y < 0 || y >=  HEIGHT)
        return 1;
    
    int mapX = (int)x;
    int mapY = (int)y;
    
    return data->map[mapY][mapX] == '1';
}
void castRay(t_data *data, float rayAngle)
{
    // Initialize ray facing directions
    data->rays.isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
    data->rays.isRayFacingUp = !data->rays.isRayFacingDown;
    data->rays.isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
    data->rays.isRayFacingLeft = !data->rays.isRayFacingRight;

    // ======================================
    // HORIZONTAL INTERSECTION CHECK
    // ======================================
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    int foundHorzWall = 0;

    // Find y-coordinate of closest horizontal grid intersection (in world units)
    float yintercept = floor(data->player.y) * TILE_SIZE;
    yintercept += data->rays.isRayFacingDown ? TILE_SIZE : 0;
    yintercept /= TILE_SIZE; // Convert to world units

    // Find x-coordinate of closest horizontal grid intersection (world units)
    float xintercept = data->player.x + (yintercept - data->player.y) / tan(rayAngle);

    // Calculate x and y steps (in world units)
    float ystep = 1.0f; // 1 tile in world units
    ystep *= data->rays.isRayFacingUp ? -1 : 1;

    float xstep = 1.0f / tan(rayAngle);
    xstep *= (data->rays.isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (data->rays.isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzX = xintercept;
    float nextHorzY = yintercept;

    while (nextHorzX >= 0 && nextHorzX < WIDTH && 
           nextHorzY >= 0 && nextHorzY < HEIGHT ) 
    {
        float checkX = nextHorzX;
        float checkY = nextHorzY + (data->rays.isRayFacingUp ? -0.0001f : 0);
        
        if (hasWallAt(data, checkX, checkY)) {
            horzWallHitX = nextHorzX;
            horzWallHitY = nextHorzY;
            foundHorzWall = 1;
            break;
        } else {
            nextHorzX += xstep;
            nextHorzY += ystep;
        }
    }

    // Convert world coordinates to pixel coordinates for rendering
    if (foundHorzWall) {
        draw_line(data,
                 data->player.x * TILE_SIZE,  // Convert player to pixels
                 data->player.y * TILE_SIZE,
                 horzWallHitX * TILE_SIZE,   // Convert hit to pixels
                 horzWallHitY * TILE_SIZE);
    }
}

void castAllRays(t_data *data)
{
	int i;
	float rayAngle;

	i = 0;
	// Start first ray from the player's FOV
	rayAngle = data->player.rotationangle - (FOV_ANGLE / 2);

	while (i < 1)
	{
		// Normalize the angle to keep it between 0 and 2*PI
		rayAngle = normalizeAngle(rayAngle);
		// Cast the single ray
		castRay(data, rayAngle);

		// Increment the angle for the next ray
		rayAngle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}


*/