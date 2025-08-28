#include "../include/cub3d.h"



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
//         while (y <= wallTopPixel)
//         {
//             my_mlx_pixel_put(data, i, y, GREEN); // Ceiling color (example: a light blue)
//             y++;
//         }

//         // Draw the wall
//         while (y <= wallBottomPixel)
//         {
//             // Apply a simple color based on wall orientation (for now)
//             if (data->rays[i].wasHitVertical)
//             {
//                 color = RED; // Darker color for vertical walls
//             }
//             else
//             {
//                 color = BLUE; // Lighter color for horizontal walls
//             }
//             my_mlx_pixel_put(data, i, y, color);
//             y++;
//         }
        
//         // Draw the floor
//         while (y < HEIGHT)
//         {
//             my_mlx_pixel_put(data, i, y, BLACK); // Floor color (example: a dark grey)
//             y++;
//         }

//         i++;
//     }
// }



// int	load_textures(t_data *data, t_vmap *v_map)
// {
// 	(void)data;
// 	printf("v_map->north : '%s'\n", v_map->north);
// 	printf("v_map->north : '%s'\n", v_map->south);
// 	printf("v_map->north : '%s'\n", v_map->west);
// 	printf("v_map->north : '%s'\n", v_map->east);


// 	v_map->images[0].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, v_map->north, &v_map->images[0].width,
// 								&data->v_map.images[0].height);

// 	v_map->images[0].addr = mlx_get_data_addr(v_map->images[0].img_ptr, &v_map->images[0].bpp,
// 								&v_map->images[0].line_len, &v_map->images[0].endian);

// 	v_map->images[1].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, v_map->south, &v_map->images[1].width,
// 								&v_map->images[1].height);
// 	v_map->images[1].addr = mlx_get_data_addr(v_map->images[1].img_ptr, &v_map->images[1].bpp,
// 								&v_map->images[1].line_len, &v_map->images[1].endian);

// 	v_map->images[2].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, v_map->west, &v_map->images[2].width,
// 								&v_map->images[2].height);
// 	v_map->images[2].addr = mlx_get_data_addr(v_map->images[2].img_ptr, &v_map->images[2].bpp,
// 								&v_map->images[2].line_len, &v_map->images[2].endian);

// 	v_map->images[3].img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, v_map->east, &v_map->images[3].width,
// 								&v_map->images[3].height);
// 	v_map->images[3].addr = mlx_get_data_addr(v_map->images[3].img_ptr, &v_map->images[3].bpp,
// 								&v_map->images[3].line_len, &v_map->images[3].endian);

// 	return (0);
// }





// #include "../include/cub3d.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>

// int load_textures(t_data *data, t_vmap *v_map)
// {

// 	(void)data;

// 	printf("-----> %s\n", v_map->north);
// 	printf("-----> %s\n", v_map->south);
// 	printf("-----> %s\n", v_map->west);
// 	printf("-----> %s\n", v_map->east);

//     // // Load each texture and check immediately
//     v_map->north_img.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,"textures/east_texture.xpm",
//                                     &v_map->north_img.width, &v_map->north_img.height);
// 	if (NULL == v_map->north_img.img_ptr)
// 		printf("here1");
// 	else
// 		printf("%s\n", v_map->north_img.img_ptr);
//     v_map->south_img.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, "textures/east_texture.xpm",
//                                     &v_map->south_img.width, &v_map->south_img.height);

// 	if (NULL == v_map->south_img.img_ptr)
// 		printf("here_2");
// 	else
// 		printf("%s\n", v_map->south_img.img_ptr );

//     v_map->west_img.img_ptr  = mlx_xpm_file_to_image(data->mlx_ptr, "textures/east_texture.xpm",
//                                     &v_map->west_img.width, &v_map->west_img.height);
// 	if (NULL == v_map->west_img.img_ptr)
// 		printf("here_3");
// 	else
// 		printf("%s\n", v_map->west_img.img_ptr );

//     v_map->east_img.img_ptr  = mlx_xpm_file_to_image(data->mlx_ptr, "textures/east_texture.xpm",
//                                     &v_map->east_img.width, &v_map->east_img.height);

// 		if (NULL == v_map->east_img.img_ptr)
// 			printf("here_4");
// 		else
// 			printf("%s\n",v_map->east_img.img_ptr );
//     // if (!v_map->north_img.img_ptr || !v_map->south_img.img_ptr ||
//     //     !v_map->west_img.img_ptr  || !v_map->east_img.img_ptr)
//     // {
//     //     fprintf(stderr, "Error: Failed to load one or more textures\n");
//     //     return (1337);
//     // }

//     // // Get image data addresses and check
//     v_map->north_img.addr = mlx_get_data_addr(v_map->north_img.img_ptr,
//                         &v_map->north_img.bpp, &v_map->north_img.line_len, &v_map->north_img.endian);

// 	if (NULL == v_map->north_img.addr)
// 		printf("here_5");
// 	else
// 		printf("%s\n",  v_map->north_img.addr);

//     v_map->south_img.addr = mlx_get_data_addr(v_map->south_img.img_ptr,
//                         &v_map->south_img.bpp, &v_map->south_img.line_len, &v_map->south_img.endian);

// 	if (NULL == v_map->south_img.addr)
// 		printf("here_6");
// 	else
// 		printf("%s\n",  v_map->south_img.addr);

//     v_map->west_img.addr  = mlx_get_data_addr(v_map->west_img.img_ptr,
//                         &v_map->west_img.bpp, &v_map->west_img.line_len, &v_map->west_img.endian);
// 	if (NULL ==  v_map->west_img.addr)
// 		printf("here_7");
// 	else
// 		printf("%s\n", v_map->west_img.addr);
//     v_map->east_img.addr  = mlx_get_data_addr(v_map->east_img.img_ptr,
//                         &v_map->east_img.bpp, &v_map->east_img.line_len, &v_map->east_img.endian);
// 	if (NULL ==  v_map->east_img.addr)
// 		printf("here_8");
// 	else
// 		printf("%s\n", v_map->east_img.addr);
//     // if (!v_map->north_img.addr || !v_map->south_img.addr ||
//     //     !v_map->west_img.addr  || !v_map->east_img.addr)
//     // {
//     //     fprintf(stderr, "Error: Failed to get image data address for textures\n");
//     //     return (1337);
//     // }
// 	data->v_map = v_map;
//     return (0);
// }


// void project_wall(t_data *data)
// {
//     int i, y;

//     for (i = 0; i < NUM_RAYS; i++)
//     {
//         // Perpendicular distance for fisheye fix
//         float perpDistance = data->rays[i].distance
//             * cos(data->rays[i].rayAngle - data->player.rotationangle);

//         // Projected wall height
//         int wallStripHeight = (int)((TILE_SIZE / perpDistance)
//             * ((WIDTH / 2) / tan(FOV_ANGLE / 2)));

//         int wallTopPixel = (HEIGHT / 2) - (wallStripHeight / 2);
//         if (wallTopPixel < 0) wallTopPixel = 0;

//         int wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);
//         if (wallBottomPixel > HEIGHT) wallBottomPixel = HEIGHT;

//         // Draw ceiling
//         for (y = 0; y < wallTopPixel; y++)
//             my_mlx_pixel_put(data, i, y, CEILING_COLOR);

//         // Select texture based on ray hit
//         t_img *texture;
// 		texture = &data->v_map->north_img;
// 		printf("jjhg : %p\n", texture);
//         // if (data->rays[i].wasHitVertical)
//         //     texture = (data->rays[i].isRayFacingLeft)
//         //                 ? &data->v_map.west_img : &data->v_map.east_img;
//         // else
//         //     texture = (data->rays[i].isRayFacingUp)
//         //                 ? &data->v_map.north_img : &data->v_map.south_img;

//         int wall_height = wallBottomPixel - wallTopPixel;
//         for (y = wallTopPixel; y < wallBottomPixel; y++)
//         {
//             int dist_from_top = y - wallTopPixel;
//             int tex_y = dist_from_top * texture->height / wall_height;

//             int tex_x;
//             if (data->rays[i].wasHitVertical)
//                 tex_x = (int)fmod(data->rays[i].wallHitY, TILE_SIZE) * texture->width / TILE_SIZE;
//             else
//                 tex_x = (int)fmod(data->rays[i].wallHitX, TILE_SIZE) * texture->width / TILE_SIZE;

//             // Clamp to valid range
//             if (tex_x < 0) tex_x = 0;
//             if (tex_x >= texture->width) tex_x = texture->width - 1;
//             if (tex_y < 0) tex_y = 0;
//             if (tex_y >= texture->height) tex_y = texture->height - 1;

//             char *tex_pixel = texture->addr + (tex_y * texture->line_len + tex_x * (texture->bpp / 8));
// 			printf("%s : test", tex_pixel);
//             // int color = *(unsigned int *)tex_pixel;
//             my_mlx_pixel_put(data, i, y, 0);
//         }

//         // Draw floor
//         for (; y < HEIGHT; y++)
//             my_mlx_pixel_put(data, i, y, FLOOR_COLOR);
//     }
// }



















// void	project_wall(t_data *data)
// {
// 	int		i;
// 	int		y;
// 	float	perpDistance;
// 	int		wallStripHeight;
// 	int		wallTopPixel;
// 	int		wallBottomPixel;

// 	i = 0;
// 	while (i < NUM_RAYS)
// 	{
// 		// Fix fish-eye by using perpendicular distance
// 		perpDistance = data->rays[i].distance
// 			* cos(data->rays[i].rayAngle - data->player.rotationangle);

// 		// Projected wall height
// 		wallStripHeight = (int)((TILE_SIZE / perpDistance)
// 				* ((WIDTH / 2) / tan(FOV_ANGLE / 2)));

// 		wallTopPixel = (HEIGHT / 2) - (wallStripHeight / 2);
// 		if (wallTopPixel < 0)
// 			wallTopPixel = 0;
// 		wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);
// 		if (wallBottomPixel > HEIGHT)
// 			wallBottomPixel = HEIGHT;

// 		// Draw ceiling
// 		y = 0;
// 		while (y < wallTopPixel)
// 			my_mlx_pixel_put(data, i, y++, CEILING_COLOR);

// 		// --- Draw the wall with textures ---
// 		t_img *texture;
// 		if (data->rays[i].wasHitVertical)
// 			texture = (data->rays[i].isRayFacingLeft)
// 				? &data->v_map.west_img : &data->v_map.east_img;
// 		else
// 			texture = (data->rays[i].isRayFacingUp)
// 				? &data->v_map.north_img : &data->v_map.south_img;

// 		int wall_height = wallBottomPixel - wallTopPixel;
// 		y = wallTopPixel;
// 		while (y < wallBottomPixel)
// 		{
// 			int dist_from_top = y - wallTopPixel;
// 			int tex_y = dist_from_top * texture->height / wall_height;

// 			int tex_x;
// 			if (data->rays[i].wasHitVertical)
// 				tex_x = (int)fmod(data->rays[i].wallHitY, TILE_SIZE)
// 					* texture->width / TILE_SIZE;
// 			else
// 				tex_x = (int)fmod(data->rays[i].wallHitX, TILE_SIZE)
// 					* texture->width / TILE_SIZE;

// 			printf("texture->addr : %s\n", texture->addr);

// 			char *tex_pixel = texture->addr
// 				+ (tex_y * texture->line_len + tex_x * (texture->bpp / 8));
// 			int color = *(unsigned int *)tex_pixel;
// 			my_mlx_pixel_put(data, i, y, color);
// 			y++;
// 		}

// 		// Draw floor
// 		while (y < HEIGHT)
// 			my_mlx_pixel_put(data, i, y++, FLOOR_COLOR);

// 		i++;
// 	}
// }



/*=========================================================================*/


/*=====================================*/

// void project_wall(t_data *data)
// {
//     int i;
//     float correctedDistance;
//     int wallStripHeight, distantProjectioPlane, wallTopPixel, wallBottomPixel;
//     int y;
//     t_img *texture;
//     int tex_x, tex_y;

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
//             wallTopPixel = 0;
//         wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);
//         if (wallBottomPixel > HEIGHT)
//             wallBottomPixel = HEIGHT;

//         // 5. Select texture based on hit direction
//         if (data->rays[i].wasHitVertical)
//         {
//             if (data->rays[i].isRayFacingLeft)
//                 texture = &data->v_map.images[2]; // West
//             else
//                 texture = &data->v_map.images[3]; // East
//             // For vertical walls, use wallHitY for texture X coordinate
//             tex_x = (int)data->rays[i].wallHitY % TILE_SIZE;
//         }
//         else
//         {
//             if (data->rays[i].isRayFacingUp)
//                 texture = &data->v_map.images[0]; // North
//             else
//                 texture = &data->v_map.images[1]; // South
//             // For horizontal walls, use wallHitX for texture X coordinate
//             tex_x = (int)data->rays[i].wallHitX % TILE_SIZE;
//         }
//         // Scale tex_x to the texture width
//         tex_x = tex_x * texture->width / TILE_SIZE;

//         // Draw ceiling
//         y = 0;
//         while (y < wallTopPixel)
//         {
//             my_mlx_pixel_put(data, i, y, CEILING_COLOR);
//             y++;
//         }

//         // Draw wall with texture
//         while (y <= wallBottomPixel)
//         {
//             int d = y - wallTopPixel;
//             tex_y = d * texture->height / wallStripHeight;
//             if (tex_y < 0) tex_y = 0;
//             if (tex_y >= texture->height) tex_y = texture->height - 1;
//             unsigned int color = get_pixel_color(texture, tex_x, tex_y);
//             my_mlx_pixel_put(data, i, y, color);
//             y++;
//         }

//         // Draw floor
//         while (y < HEIGHT)
//         {
//             my_mlx_pixel_put(data, i, y, FLOOR_COLOR);
//             y++;
//         }

//         i++;
//     }
// }


/*=========================================================================================================================*/



// int	load_textures(t_data *data)
// {
// 	printf(" [ v_map->north ] : '%s'\n", data->v_map.north);
// 	printf(" [ v_map->south ] : '%s'\n", data->v_map.south);
// 	printf(" [ v_map->west ]  : '%s'\n", data->v_map.west);
// 	printf(" [ v_map->east ]  : '%s'\n", data->v_map.east);

// 	data->v_map.east_img.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->v_map.east, &data->v_map.east_img.width, &data->v_map.east_img.height);
// 	data->v_map.west_img.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->v_map.west, &data->v_map.west_img.width, &data->v_map.west_img.height);

// 	data->v_map.north_img.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->v_map.north, &data->v_map.north_img.width, &data->v_map.north_img.height);
// 	data->v_map.south_img.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->v_map.south, &data->v_map.south_img.width, &data->v_map.south_img.height);

// 		if (!data->v_map.north_img.img_ptr || !data->v_map.south_img.img_ptr ||
// 		!data->v_map.west_img.img_ptr || !data->v_map.east_img.img_ptr )
// 			 (printf("here_1"), exit(1337));

// 	data->v_map.east_img.addr = mlx_get_data_addr(data->v_map.east_img.img_ptr, &data->v_map.east_img.bpp, &data->v_map.east_img.line_len, &data->v_map.east_img.endian);
// 	data->v_map.west_img.addr = mlx_get_data_addr(data->v_map.west_img.img_ptr, &data->v_map.west_img.bpp, &data->v_map.west_img.line_len, &data->v_map.west_img.endian);
// 	data->v_map.north_img.addr = mlx_get_data_addr(data->v_map.north_img.img_ptr, &data->v_map.north_img.bpp, &data->v_map.north_img.line_len, &data->v_map.north_img.endian);
// 	data->v_map.south_img.addr = mlx_get_data_addr(data->v_map.south_img.img_ptr, &data->v_map.south_img.bpp, &data->v_map.south_img.line_len, &data->v_map.south_img.endian);

// 		if (!data->v_map.north_img.addr || !data->v_map.south_img.addr ||
// 		!data->v_map.west_img.addr || !data->v_map.east_img.addr)
// 			 (printf("here_2"), exit(1337));

// 	return (0);
// }

// void    project_wall(t_data *data)
// {
// 	// printf("[%d]\n", data->v_map.n_ceil);
// 	// printf("[%d]\n", data->v_map.n_floor);

// 	printf(" project_wall : [ v_map->north ] : '%s'\n", data->v_map.north);
// 	printf(" project_wall : [ v_map->south ] : '%s'\n", data->v_map.south);
// 	printf(" project_wall : [ v_map->west ]  : '%s'\n", data->v_map.west);
// 	printf(" project_wall : [ v_map->east ]  : '%s'\n", data->v_map.east);



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
//             wallTopPixel = 0;
//         wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);
//         if (wallBottomPixel > HEIGHT)
//             wallBottomPixel = HEIGHT;

//         // 5. Draw the vertical wall strip
//         y = 0;

//         // Draw the ceiling
//         while (y <= wallTopPixel)
//         {
//             my_mlx_pixel_put(data, i, y, CEILING_COLOR);
//             y++;
//         }

//         // Draw the wall
//         while (y <= wallBottomPixel)
//         {
//             // Directional color selection
//             if (data->rays[i].wasHitVertical)
//             {
//                 // Hit a vertical wall (E/W)
//                 if (data->rays[i].isRayFacingLeft)
//                     color = WEST_COLOR;  // West wall
//                 else
//                     color = EAST_COLOR;  // East wall
//             }
//             else
//             {
//                 // Hit a horizontal wall (N/S)
//                 if (data->rays[i].isRayFacingUp)
//                     color = NORTH_COLOR; // North wall
//                 else
//                     color = SOUTH_COLOR; // South wall
//             }
//             my_mlx_pixel_put(data, i, y, color);
//             y++;
//         }
        
//         // Draw the floor
//         while (y < HEIGHT)
//         {
//             my_mlx_pixel_put(data, i, y, FLOOR_COLOR);
//             y++;
//         }

//         i++;
//     }
// }





// projection.c
// Replaces previous projection logic with textured wall rendering per-ray.
// Assumes get_pixel_color(), my_mlx_pixel_put(), TILE_SIZE, WIDTH, HEIGHT, FOV_ANGLE,
// and data->v_map.{*_img} fields are correct (img_ptr, addr, bpp, line_len, endian, width, height).

#include "../include/cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int	load_textures(t_data *data)
{
	// Load XPM images into the t_img structs (width/height will be set by mlx)
	data->v_map.east_img.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->v_map.east, &data->v_map.east_img.width, &data->v_map.east_img.height);
	data->v_map.west_img.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->v_map.west, &data->v_map.west_img.width, &data->v_map.west_img.height);
	data->v_map.north_img.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->v_map.north, &data->v_map.north_img.width, &data->v_map.north_img.height);
	data->v_map.south_img.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->v_map.south, &data->v_map.south_img.width, &data->v_map.south_img.height);

	if (!data->v_map.north_img.img_ptr || !data->v_map.south_img.img_ptr ||
		!data->v_map.west_img.img_ptr || !data->v_map.east_img.img_ptr)
	{
		ft_putstr_fd("load_textures: failed to open texture file(s)\n", STDERR_FILENO);
		return (1);
	}

	// Get data addresses for each texture
	data->v_map.east_img.addr = mlx_get_data_addr(data->v_map.east_img.img_ptr, &data->v_map.east_img.bpp, &data->v_map.east_img.line_len, &data->v_map.east_img.endian);
	data->v_map.west_img.addr = mlx_get_data_addr(data->v_map.west_img.img_ptr, &data->v_map.west_img.bpp, &data->v_map.west_img.line_len, &data->v_map.west_img.endian);
	data->v_map.north_img.addr = mlx_get_data_addr(data->v_map.north_img.img_ptr, &data->v_map.north_img.bpp, &data->v_map.north_img.line_len, &data->v_map.north_img.endian);
	data->v_map.south_img.addr = mlx_get_data_addr(data->v_map.south_img.img_ptr, &data->v_map.south_img.bpp, &data->v_map.south_img.line_len, &data->v_map.south_img.endian);

	if (!data->v_map.north_img.addr || !data->v_map.south_img.addr ||
		!data->v_map.west_img.addr || !data->v_map.east_img.addr)
	{
		ft_putstr_fd("load_textures: failed to get texture data address\n", STDERR_FILENO);
		return (1);
	}

	return (0);
}

/*
 * project_wall:
 *   For every ray:
 *     - compute corrected distance (remove fisheye)
 *     - compute wall strip height on screen
 *     - choose the correct texture (N/S/E/W)
 *     - compute texture X coordinate (which column of the texture)
 *     - for each pixel of the vertical strip, compute texture Y and sample color
 *     - draw ceiling, textured wall column, and floor
 */
void project_wall(t_data *data)
{
	int i;

	i = 0;
	while (i < NUM_RAYS)
	{
		// --- 1) correct distance to avoid fisheye
		float rayAngle = data->rays[i].rayAngle;
		float rawDistance = data->rays[i].distance;

		// guard against infinite or zero distance
		if (rawDistance <= 0.0001f || rawDistance == FLT_MAX)
		{
			// draw ceiling + floor for this column and skip texture sample
			int y = 0;
			while (y < HEIGHT / 2)
				my_mlx_pixel_put(data, i, y++, CEILING_COLOR);
			while (y < HEIGHT)
				my_mlx_pixel_put(data, i, y++, FLOOR_COLOR);
			i++;
			continue;
		}

		float correctedDistance = rawDistance * cosf(rayAngle - data->player.rotationangle);

		// --- 2) distance to projection plane
		float distProjPlane = (WIDTH / 2.0f) / tanf(FOV_ANGLE / 2.0f);

		// --- 3) wall strip height
		int wallStripHeight = (int)((TILE_SIZE / correctedDistance) * distProjPlane);
		if (wallStripHeight <= 0)
			wallStripHeight = 1;

		// --- 4) top and bottom of wall on screen
		int wallTopPixel = (HEIGHT / 2) - (wallStripHeight / 2);
		if (wallTopPixel < 0)
			wallTopPixel = 0;
		int wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);
		if (wallBottomPixel >= HEIGHT)
			wallBottomPixel = HEIGHT - 1;

		// --- 5) choose the correct texture based on hit orientation and facing
		t_img *tex = NULL;
		if (data->rays[i].wasHitVertical)
		{
			// Vertical wall => East or West texture
			if (data->rays[i].isRayFacingLeft)
				tex = &data->v_map.west_img; // hit west-facing wall
			else
				tex = &data->v_map.east_img; // hit east-facing wall
		}
		else
		{
			// Horizontal wall => North or South texture
			if (data->rays[i].isRayFacingUp)
				tex = &data->v_map.north_img; // hit north-facing wall
			else
				tex = &data->v_map.south_img; // hit south-facing wall
		}

		// Fallback if texture not loaded
		if (!tex || !tex->addr || tex->width == 0 || tex->height == 0)
		{
			// draw plain colored column (keep previous behavior)
			int y = 0;
			while (y <= wallTopPixel)
				my_mlx_pixel_put(data, i, y++, CEILING_COLOR);
			while (y <= wallBottomPixel)
			{
				int color;
				if (data->rays[i].wasHitVertical)
					color = data->rays[i].isRayFacingLeft ? WEST_COLOR : EAST_COLOR;
				else
					color = data->rays[i].isRayFacingUp ? NORTH_COLOR : SOUTH_COLOR;
				my_mlx_pixel_put(data, i, y++, color);
			}
			while (y < HEIGHT)
				my_mlx_pixel_put(data, i, y++, FLOOR_COLOR);
			i++;
			continue;
		}

		// --- 6) compute texture X coordinate:
		// If vertical hit -> use fractional part of wallHitY, else use fractional part of wallHitX.
		// Map that fractional offset to texture width.
		int texX;
		if (data->rays[i].wasHitVertical)
		{
			float hitY = data->rays[i].wallHitY;
			float offset = fmodf(hitY, TILE_SIZE);               // 0 .. TILE_SIZE-1
			if (offset < 0)
				offset += TILE_SIZE;
			// Map offset to texture width
			texX = (int)((offset / (float)TILE_SIZE) * tex->width);
		}
		else
		{
			float hitX = data->rays[i].wallHitX;
			float offset = fmodf(hitX, TILE_SIZE);               // 0 .. TILE_SIZE-1
			if (offset < 0)
				offset += TILE_SIZE;
			texX = (int)((offset / (float)TILE_SIZE) * tex->width);
		}
		if (texX < 0)
			texX = 0;
		if (texX >= tex->width)
			texX = tex->width - 1;

		// --- 7) draw ceiling
		int y = 0;
		while (y < wallTopPixel)
		{
			my_mlx_pixel_put(data, i, y, data->v_map.n_ceil);
			y++;
		}

		// --- 8) draw textured wall column
		// Calculate how much to step in texture for each screen pixel
		float textureStep = (float)tex->height / (float)wallStripHeight;
		// Starting texture y: if wallTopPixel < 0 we need to start at an offset. But we clamped wallTopPixel >= 0 above,
		// so textureYStart = 0 for wallTopPixel == computed top.
		float textureY = 0.0f;
		// If the wallTopPixel was clamped (when wallStripHeight > HEIGHT) we need to compute the starting textureY:
		if (wallStripHeight > HEIGHT)
		{
			// top of wall would be negative initially; compute how many pixels were skipped at the top
			int off = (wallStripHeight - HEIGHT) / 2;
			textureY = off * textureStep;
		}

		// For each pixel between wallTopPixel and wallBottomPixel, sample texture and draw
		while (y <= wallBottomPixel)
		{
			int texY = (int)textureY;
			if (texY < 0)
				texY = 0;
			if (texY >= tex->height)
				texY = tex->height - 1;

			unsigned int color = get_pixel_color(tex, texX, texY);

			// Optional: simple shading for horizontal vs vertical hits
			if (!data->rays[i].wasHitVertical)
			{
				// slightly darken horizontal hits to give depth (bit-twiddling)
				unsigned int r = (color >> 16) & 0xFF;
				unsigned int g = (color >> 8) & 0xFF;
				unsigned int b = (color) & 0xFF;
				// multiply by 0.8 (approx)
				r = (r * 8) / 10;
				g = (g * 8) / 10;
				b = (b * 8) / 10;
				color = (r << 16) | (g << 8) | b;
			}

			my_mlx_pixel_put(data, i, y, color);
			textureY += textureStep;
			y++;
		}

		// --- 9) draw floor
		while (y < HEIGHT)
		{
			my_mlx_pixel_put(data, i, y, data->v_map.n_floor);
			y++;
		}

		i++;
	}
}


/*=========================================================================*/








// void project_wall(t_data *data)
// {
//     int i;
//     float correctedDistance;
//     int wallStripHeight, distantProjectioPlane, wallTopPixel, wallBottomPixel;
//     int y;
//     t_img *texture;
//     int tex_x, tex_y;

//     i = 0;
//     while (i < NUM_RAYS)
//     {
//         correctedDistance = data->rays[i].distance * cos(data->rays[i].rayAngle - data->player.rotationangle);
//         distantProjectioPlane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
//         wallStripHeight = (int)((TILE_SIZE / correctedDistance) * distantProjectioPlane);

//         wallTopPixel = (HEIGHT / 2) - (wallStripHeight / 2);
//         if (wallTopPixel < 0) wallTopPixel = 0;
//         wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);
//         if (wallBottomPixel > HEIGHT) wallBottomPixel = HEIGHT;

//         // 1. Select the correct texture and tex_x
//         if (data->rays[i].wasHitVertical)
//         {
//             if (data->rays[i].isRayFacingLeft)
//                 texture = &data->v_map.images[2]; // West
//             else
//                 texture = &data->v_map.images[3]; // East
//             tex_x = (int)fmod(data->rays[i].wallHitY, TILE_SIZE);
//         }
//         else
//         {
//             if (data->rays[i].isRayFacingUp)
//                 texture = &data->v_map.images[0]; // North
//             else
//                 texture = &data->v_map.images[1]; // South
//             tex_x = (int)fmod(data->rays[i].wallHitX, TILE_SIZE);
//         }
//         // Scale tex_x to texture width
//         tex_x = tex_x * texture->width / TILE_SIZE;

//         // 2. Draw ceiling
//         y = 0;
//         while (y < wallTopPixel)
//             my_mlx_pixel_put(data, i, y, CEILING_COLOR), y++;

//         // 3. Draw wall with texture
//         while (y <= wallBottomPixel)
//         {
//             int d = y - wallTopPixel;
//             tex_y = (wallStripHeight > 0) ? (d * texture->height / wallStripHeight) : 0;
//             if (tex_y < 0) tex_y = 0;
//             if (tex_y >= texture->height) tex_y = texture->height - 1;
//             unsigned int color = get_pixel_color(texture, tex_x, tex_y);
//             my_mlx_pixel_put(data, i, y, color);
//             y++;
//         }

//         // 4. Draw floor
//         while (y < HEIGHT)
//             my_mlx_pixel_put(data, i, y, FLOOR_COLOR), y++;

//         i++;
//     }
// }
