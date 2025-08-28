

#include "../include/cub3d.h"

int p_player(char c)
{
	return ((c != 'N' && c != 'S' && c != 'W' && c != 'E'));
}

int ft_0_1_map(int c)
{
	if ((c >= '0' && c <= '1'))
		return (0);
	else
		return (1);
}

int check_map_line_2(char *line, int fd)
{
	char *_line_;

	while ((line = get_next_line(fd)) != NULL)
	{
		_line_ = ft_strtrim_end(line, " ");
		if (ft_strcmp(_line_, "\n"))
			return (free(line), free(_line_), line = NULL, _line_ = NULL, 1337);
		free(line);
		free(_line_);
	}
	return (0);
}

int check_map_line(char *line, int fd, int *flag)
{
	int i;

	i = 0;
	if (ft_strcmp(line, "\n"))
	{
		*flag = 1;
		while (line[i] == ' ')
			i++;
		while (line[i])
		{
			if (ft_0_1_map(line[i]) && line[i] != ' ' && line[i] != '\n' && p_player(line[i]))
				return (printf("check_map_line() : %s \n", line), 1337);
			i++;
		}
	}
	else if (*flag == 1)
	{
		if (check_map_line_2(line, fd))
			return (1337);
	}
	return (0);
}

static char *process_remaining_lines(char *temp, int fd, int *flag)
{
	char *line;
	char *_line_;
	char *res;

	res = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (check_map_line(line, fd, flag))
			return (free(line), free(temp), NULL);
		if (!ft_strcmp(line, "\n"))
		{
			free(line);
			break;
		}
		_line_ = ft_strtrim_end(line, " ");
		res = ft_strjoin(temp, _line_);
		(free(line), free(_line_));
		if (!res)
			return (free(temp), NULL);
		free(temp);
		temp = res;
	}
	return (temp);
}

int store_map(t_data *data, char *line, int fd, int *flag)
{
	char *_line_;
	char *temp;

	temp = NULL;
	while (line && !ft_strcmp(line, "\n"))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (NULL == line)
		return (1337);
	if (check_map_line(line, fd, flag))
		return (free(line), 1337);
	_line_ = ft_strtrim_end(line, " ");
	temp = ft_strjoin(temp, _line_);
	(free(_line_), free(line));
	if (!temp)
		return (1337);
	temp = process_remaining_lines(temp, fd, flag);
	if (!temp)
		return (1337);
	data->v_map._join_map_lines = temp;
	return (close(fd), 0);
}

int second_map(t_data *data)
{
	int fd;
	char *line;
	int count;
	int flag;

	flag = 0;
	fd = open("map/map.cub", O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("fd error\n", STDERR_FILENO), 1337);
	count = 0;
	while (((line = get_next_line(fd)) != NULL) && count < 6)
	{
		if (ft_strstr(line, data->v_map.ceil) || ft_strstr(line, data->v_map.floor)
			|| ft_strstr(line, data->v_map.north) || ft_strstr(line, data->v_map.south)
			|| ft_strstr(line, data->v_map.west) || ft_strstr(line, data->v_map.east))
			(count++, free(line));
		else
			free(line);
	}
	if (NULL == line)
		return (1337);
	// we reach to first line of map
	if (store_map(data, line, fd, &flag))
		return (1337);
	// free(line); //free line in store_map() function
	return (close(fd), 0);
}

int check_extention(char *map)
{
	char *ext;
	int i;
	int j;

	ext = ".cub";
	i = ft_strlen(map) - 1;
	j = ft_strlen(ext) - 1;
	while (j > -1)
	{
		if (map[i] != ext[j] && j > -1)
			return (1);
		else if (map[i] == ext[j])
			((i--), (j--));
	}
	return (0);
}

char *get_word(char *line, int count)
{
	char *str;
	int i;
	int j;

	i = 0;
	while (line[i] == ' ')
		i++;

	str = malloc(sizeof(char) * (count + 1));
	if (NULL == str)
		return (NULL);

	j = 0;
	while (j < count && line[i] && line[i] != '\n')
	{
		if (line[i] == '\t')
			return (free(str), NULL);
		str[j++] = line[i++];
	}
	str[j] = '\0';
	return (str);
}

int check_element(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (1337);
		i++;
	}
	return (0);
}

int check_res(char **res)
{
	int i;

	if (ft_count_2d_array(res) != 3)
		return (1);
	i = 0;
	while (res[i] != NULL)
	{
		if (check_element(res[i]))
			return (1337);
		i++;
	}
	return (0);
}

int check_number(char *color, char *path, t_data *data)
{
	char **res;
	int r;
	int g;
	int b;

	res = NULL;
	res = ft_split(path, ", ");
	if (NULL == res)
		return (1337);
	if (check_res(res))
		return (free_2d_array(res), 1);
	r = ft_atoi(res[0]);
	g = ft_atoi(res[1]);
	b = ft_atoi(res[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (free_2d_array(res), 1337);
	if (!ft_strcmp(color, "F "))
		data->v_map.n_floor = (r << 16 | g << 8 | b << 0);
	else if (!ft_strcmp(color, "C "))
		data->v_map.n_ceil = (r << 16 | g << 8 | b << 0);
	;

	return (free_2d_array(res), 0);
}

int check_comma(char *path)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (path[i])
	{
		if (path[i] == ',')
			count++;
		if (path[i] == ',' && path[i + 1] == ',')
			return (1337);
		i++;
	}
	if (count != 2)
		return (1337);
	return (0);
}

int check_v_color(char *color, char *path, t_data *data)
{
	if (!ft_strcmp(color, "F ") || !ft_strcmp(color, "C "))
	{
		if (check_comma(path) || check_number(color, path, data))
			return (1337);
	}
	return (0);
}

int check_v_path(char *str, char *path)
{
	int fd;

	if (!ft_strcmp(str, "NO ") || !ft_strcmp(str, "SO ") || !ft_strcmp(str, "WE ") || !ft_strcmp(str, "EA "))
	{
		if (((fd = open(path, O_RDONLY)) < 0))
			return (ft_putstr_fd("!!path not valid\n", 2), 1337);
	}
	return (0);
}

int index_start(char *line)
{
	int i;

	i = 0;
	while (line[i] && (line[i] != ' '))
		i++;
	while (line[i] && (line[i] == ' '))
		i++;
	return (i);
}

int index_end(char *line)
{
	int start;

	start = index_start(line);
	while (line[start])
		start++;
	return (start);
}

static int assign_and_check_attribute(t_data *data, char *path, int *count)
{
	if (!ft_strcmp(data->v_map.str, "NO ") && !data->v_map.north)

		data->v_map.north = path;
	else if (!ft_strcmp(data->v_map.str, "SO ") && !data->v_map.south)
		data->v_map.south = path;	else if (!ft_strcmp(data->v_map.str, "WE ") && !data->v_map.west)
		data->v_map.west = path;
	else if (!ft_strcmp(data->v_map.str, "EA ") && !data->v_map.east)
		data->v_map.east = path;
	else if (!ft_strcmp(data->v_map.color, "F ") && !data->v_map.floor)
		data->v_map.floor = path;
	else if (!ft_strcmp(data->v_map.color, "C ") && !data->v_map.ceil)
		data->v_map.ceil = path;
	else
		return (0); // No attribute assigned
	(*count)++;
	return (1); // Attribute assigned successfully
}

static char *get_and_validate_path(char *line)
{
	char *path;

	path = ft_substr(line, index_start(line), index_end(line));
	if (NULL == path)
	{
		ft_putstr_fd("path is NULL\n", 2);
		return (NULL);
	}
	if (!ft_strcmp(path, "\0"))
	{
		ft_putstr_fd("path is not correct\n", 2);
		free(path);
		return (NULL);
	}
	return (path);
}

int check_dublicate(t_data *data, char *line, int *count)
{
	char *path;
	int assigned;

	if (!ft_strcmp(line, "\0"))
		return (*count);
	if (ft_strcmp(data->v_map.str, "NO ") && ft_strcmp(data->v_map.str, "SO ") &&
		ft_strcmp(data->v_map.str, "WE ") && ft_strcmp(data->v_map.str, "EA ") &&
		ft_strcmp(data->v_map.color, "F ") && ft_strcmp(data->v_map.color, "C "))
		return (1337);
	path = get_and_validate_path(line);
	if (!path)
		return (1337);
	assigned = assign_and_check_attribute(data, path, count);
	if (!assigned)
	{
		printf("assigned : %d\n", assigned);
		ft_putstr_fd("path not correct\n", 2);
		free(path);
		return (1337);
	}
	if (check_v_path(data->v_map.str, path) || check_v_color(data->v_map.color, path, data))
		return (1337);

	// Note: 'path' is now owned by `v_map`, so it should not be freed here.
	return (*count);
}

int check_direction(t_data *data, char *line, int *count)
{
	if (check_dublicate(data, line, count) == 1337)
		return (1337);
	return (*(count));
}

int	check_line(t_data *data, char *line, int *count)
{
	int check;
	char *new_line;

	new_line = ft_strtrim(line, " ");
	data->v_map.str = get_word(line, 3);
	data->v_map.color = get_word(line, 2);
	if ((NULL == data->v_map.str) || (NULL == data->v_map.color))
		return (1337);
	check = check_direction(data, new_line, count);
	free(new_line);
	if (check == 1337)
		return (free(data->v_map.str), free(data->v_map.color), 1337);
	return (free(data->v_map.str), free(data->v_map.color), *(count));
}

void free_v_map(t_vmap *v_map)
{
	if (v_map->north)
		free(v_map->north);
	if (v_map->south)
		free(v_map->south);
	if (v_map->west)
		free(v_map->west);
	if (v_map->east)
		free(v_map->east);
	if (v_map->floor)
		free(v_map->floor);
	if (v_map->ceil)
		free(v_map->ceil);
}

int check_first_part(int fd, int count, t_data *data)
{

	char	*line;
	int		n_count;
	char	*new_line;

	n_count = 0;
	fd = open("map/map.cub", O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("fd error\n", STDERR_FILENO), 1337);
	while (((line = get_next_line(fd)) != NULL) && n_count != 6)
	{
		if (ft_strcmp(line, "\n"))
		{
			new_line = ft_strtrim(line, "\n");
			n_count = check_line(data, new_line, &count);
			if (n_count == 1337)
				return (free(line), free(new_line), 1337);
			(free(line), free(new_line));
		}
		else
			free(line);
	}
	if (n_count != 6)
		return (free(line), 1337);
	return (close(fd), free(line), 0);
}

int fd_player(char p)
{
	return ((p == 'N' || p == 'S' || p == 'W' || p == 'E'));
}

int found_player(char **_2darray)
{
	int i;
	int j;
	int flag;

	flag = 0;
	i = 0;
	while (_2darray[i])
	{
		j = 0;
		while (_2darray[i][j])
		{
			if (fd_player(_2darray[i][j]))
				flag = 1;
			j++;
		}
		i++;
	}
	if (flag == 0)
		return (1337);
	return (0);
}

char **check_map(char *join_map_lines)
{
	// printf();
	char **_2darray;
	_2darray = ft_split(join_map_lines, "\n");
	if (!_2darray)
		return (/*free(join_map_lines), you free in main*/ NULL);
	if (found_player(_2darray))
		return (free_2d_array(_2darray), NULL);

	return (_2darray);
}


/*===========================================================================================================================================================*/







int ft_parsing(char *map, t_data *data)
{
	int fd;
	int count;


	fd = 0;
	count = 0;
	if (check_extention(map))
		return (1);
	if (check_first_part(fd, count, data) || second_map(data))
		return (free_v_map(&data->v_map), free(data->v_map._join_map_lines), 1); // remove it when finish



	/*==================================================================*/

		printf("(-----> ::: v_map->north)[%s]\n", data->v_map.north);

	/*==================================================================*/

	
	return (0);
}



void f()
{
	system("leaks Cub3d");
	// system("lsof -c Cub3d");
}

int main(int ac, char **av)
{
	atexit(f);
	(void)ac;
	char **maps;
	// t_vmap v_map;
	t_data data;

	ft_memset(&data, 0, sizeof(t_data));
	// atexit(f);

	if ((!av[1]) || ft_parsing(av[1], &data))
		return (ft_putstr_fd("map not valid!\n", STDERR_FILENO), 1);

	maps = check_map(data.v_map._join_map_lines);
	if (NULL == maps)
		return (printf("here\n"), free_v_map(&data.v_map), free(data.v_map._join_map_lines), 1337);

	// data.map = maps;
	if (ft_start(&data)) // ft_start(&data, maps)
		return (1);

	free_v_map(&data.v_map);
	free(data.v_map._join_map_lines);
	free_2d_array(maps);
	
	return (0);
}

/*===========================================================================================================================================================*/
