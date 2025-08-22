/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:43:07 by sidrissi          #+#    #+#             */
/*   Updated: 2025/08/21 16:45:29 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


// void	project_wall(t_data *data)
// {
// 	int	i;
// 	int	wallStripHeight;
// 	int	distantProjectioPlane;

// 	i = 0;
// 	while (i < NUM_RAYS)
// 	{
// 		distantProjectioPlane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
// 		wallStripHeight = (TILE_SIZE / data->rays->distance) * distantProjectioPlane ; 
// 		i++;
// 	}
// }



// #include "../include/cub3d.h"

// void    project_wall(t_data *data)
// {
//     int i;
//     float correctedDistance;
//     int wallStripHeight;
//     int distantProjectioPlane;
//     int wallTopPixel;
//     int wallBottomPixel;
//     int y;
//     int color;

//     i = 0;
//     while (i < NUM_RAYS)
//     {
//         // 1. Correct the ray distance to avoid fisheye effect
//         correctedDistance = data->rays[i].distance * cos(data->rays[i].rayAngle - data->player.rotationangle);
        
//         // 2. Calculate the distance to the projection plane
//         distantProjectioPlane = (WIDTH / 2) / tan(FOV_ANGLE / 2);

//         // 3. Calculate the height of the wall strip on the screen
//         wallStripHeight = (int)((TILE_SIZE / correctedDistance) * distantProjectioPlane);
        
//         // 4. Calculate the top and bottom pixel of the wall
//         wallTopPixel = (HEIGHT / 2) - (wallStripHeight / 2);
//         if (wallTopPixel < 0)
//         {
//             wallTopPixel = 0;
//         }

//         wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);
//         if (wallBottomPixel > HEIGHT)
//         {
//             wallBottomPixel = HEIGHT;
//         }

//         // 5. Draw the vertical wall strip
//         y = 0;
//         // Draw the ceiling
//         while (y < wallTopPixel)
//         {
//             my_mlx_pixel_put(data, i, y, WHITE); // Ceiling color
//             y++;
//         }

//         // Draw the wall
//         while (y < wallBottomPixel)
//         {
//             // Apply a simple color based on wall orientation (for now)
//             if (data->rays[i].wasHitVertical)
//             {
//                 color = 0x888888; // Darker color for vertical walls
//             }
//             else
//             {
//                 color = 0xaaaaaa; // Lighter color for horizontal walls
//             }
//             my_mlx_pixel_put(data, i, y, color);
//             y++;
//         }
        
//         // Draw the floor
//         while (y < HEIGHT)
//         {
//             my_mlx_pixel_put(data, i, y, BLACK); // Floor color
//             y++;
//         }

//         i++;
//     }
// }





void    project_wall(t_data *data)
{
    int i;
    float correctedDistance;
    int wallStripHeight;
    int distantProjectioPlane;
    int wallTopPixel;
    int wallBottomPixel;
    int y;
    int color;

    i = 0;
    while (i < NUM_RAYS)
    {
        // 1. Correct the ray distance to avoid fisheye effect
        correctedDistance = data->rays[i].distance * cos(data->rays[i].rayAngle - data->player.rotationangle);
        
        // 2. Calculate the distance to the projection plane
        distantProjectioPlane = (WIDTH / 2) / tan(FOV_ANGLE / 2);

        // 3. Calculate the height of the wall strip on the screen
        wallStripHeight = (int)((TILE_SIZE / correctedDistance) * distantProjectioPlane);
        
        // 4. Calculate the top and bottom pixel of the wall
        wallTopPixel = (HEIGHT / 2) - (wallStripHeight / 2);
        if (wallTopPixel < 0)
        {
            wallTopPixel = 0;
        }

        wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);
        if (wallBottomPixel > HEIGHT)
        {
            wallBottomPixel = HEIGHT;
        }

        // 5. Draw the vertical wall strip
        y = 0;
        // Draw the ceiling
        while (y < wallTopPixel)
        {
            my_mlx_pixel_put(data, i, y, 0x00A0A0FF); // Ceiling color (example: a light blue)
            y++;
        }

        // Draw the wall
        while (y < wallBottomPixel)
        {
            // Apply a simple color based on wall orientation (for now)
            if (data->rays[i].wasHitVertical)
            {
                color = 0x888888; // Darker color for vertical walls
            }
            else
            {
                color = 0xaaaaaa; // Lighter color for horizontal walls
            }
            my_mlx_pixel_put(data, i, y, color);
            y++;
        }
        
        // Draw the floor
        while (y < HEIGHT)
        {
            my_mlx_pixel_put(data, i, y, 0x00808080); // Floor color (example: a dark grey)
            y++;
        }

        i++;
    }
}