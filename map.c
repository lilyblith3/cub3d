#include "parsing.h"

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || 
			c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	count_map_lines(char **lines, int start_idx)
{
	int	count;
	int	i;

	count = 0;
	i = start_idx;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > 0)
			count++;
		i++;
	}
	return (count);
}

int	get_max_line_length(char **lines, int start_idx)
{
	int	max_len;
	int	current_len;
	int	i;

	max_len = 0;
	i = start_idx;
	while (lines[i])
	{
		current_len = ft_strlen(lines[i]);
		if (current_len > max_len)
			max_len = current_len;
		i++;
	}
	return (max_len);
}

char	*pad_line_with_spaces(char *line, int target_width)
{
	char	*padded;
	int		line_len;
	int		i;

	line_len = ft_strlen(line);
	padded = malloc(target_width + 1);
	if (!padded)
		return (NULL);
	i = 0;
	while (i < line_len)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < target_width)
	{
		padded[i] = ' ';
		i++;
	}
	padded[target_width] = '\0';
	return (padded);
}

int	parse_map_array(char **lines, int start_idx, t_game *game)
{
	int	map_height;
	int	i;
	int	line_idx;

	map_height = count_map_lines(lines, start_idx);
	if (map_height == 0)
		return (0);
	game->map_width = get_max_line_length(lines, start_idx);
	game->map_height = map_height;
	game->map = malloc(sizeof(char *) * (map_height + 1));
	if (!game->map)
		return (0);
	i = 0;
	line_idx = start_idx;
	while (i < map_height && lines[line_idx])
	{
		if (ft_strlen(lines[line_idx]) == 0)
		{
			line_idx++;
			continue;
		}
		game->map[i] = pad_line_with_spaces(lines[line_idx], game->map_width);
		if (!game->map[i])
			return (0);
		i++;
		line_idx++;
	}
	game->map[i] = NULL;
	return (1);
}

int	validate_map_characters(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (!is_valid_map_char(game->map[i][j]))
			{
				printf("Error: Invalid character '%c' at (%d,%d)\n", 
					game->map[i][j], i, j);
				return (0);
			}
			if (is_player_char(game->map[i][j]))
			{
				player_count++;
				game->player_x = j;
				game->player_y = i;
				game->player_dir = game->map[i][j];
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		printf("Error: Found %d players, expected exactly 1\n", player_count);
		return (0);
	}
	return (1);
}

int	is_wall_or_boundary(t_game *game, int y, int x)
{
	if (y < 0 || y >= game->map_height || 
		x < 0 || x >= game->map_width)
		return (1);
	return (game->map[y][x] == '1');
}

int	validate_map_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == '0' || is_player_char(game->map[i][j]))
			{
				if (!is_wall_or_boundary(game, i - 1, j) ||
					!is_wall_or_boundary(game, i + 1, j) ||
					!is_wall_or_boundary(game, i, j - 1) ||
					!is_wall_or_boundary(game, i, j + 1))
				{
					printf("Error: Map not closed at (%d,%d)\n", i, j);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_map(char **lines, int start_idx, t_game *game)
{
	if (!parse_map_array(lines, start_idx, game))
	{
		printf("Error: Failed to parse map array\n");
		return (0);
	}
	if (!validate_map_characters(game))
		return (0);
	if (!validate_map_walls(game))
		return (0);
	return (1);
}

void	print_final_result(t_game *game)
{
	int	i;

	printf("\n=== PARSING SUCCESSFUL ===\n");
	printf("File: %s\n", game->file_name);
	printf("North texture: %s\n", game->north_texture);
	printf("South texture: %s\n", game->south_texture);
	printf("West texture: %s\n", game->west_texture);
	printf("East texture: %s\n", game->east_texture);
	printf("Floor color: R:%d G:%d B:%d\n", 
		game->floor_color[0], game->floor_color[1], game->floor_color[2]);
	printf("Ceiling color: R:%d G:%d B:%d\n",
		game->ceiling_color[0], game->ceiling_color[1], game->ceiling_color[2]);
	printf("Map size: %dx%d\n", game->map_width, game->map_height);
	printf("Player position: (%d,%d) facing %c\n", 
		game->player_x, game->player_y, game->player_dir);
	printf("\nMap:\n");
	i = 0;
	while (i < game->map_height)
	{
		printf("%s\n", game->map[i]);
		i++;
	}
	printf("\n=== All validations passed! Ready for raycasting! ===\n");
}
















// #include "parsing.h"

// static char	*ft_strtrim_spaces(char *str)
// {
// 	char	*start;
// 	char	*end;
// 	int		len;
// 	int		i;

// 	if (!str)
// 		return (NULL);
// 	start = str;
// 	while (*start == ' ' || *start == '\t')
// 		start++;
// 	end = start + ft_strlen(start) - 1;
// 	while (end > start && (*end == ' ' || *end == '\t'))
// 		end--;
// 	len = end - start + 1;
// 	i = 0;
// 	while (i < len)
// 	{
// 		str[i] = start[i];
// 		i++;
// 	}
// 	str[len] = '\0';
// 	return (str);
// }

// static int	ft_isdigit_str(char *str)
// {
// 	int	i;

// 	if (!str || !str[0])
// 		return (0);
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] < '0' || str[i] > '9')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// static int	validate_rgb_value(char *str)
// {
// 	int	value;

// 	if (!ft_isdigit_str(str))
// 		return (-1);
// 	value = ft_atoi(str);
// 	if (value < 0 || value > 255)
// 		return (-1);
// 	return (value);
// }

// static int	count_commas(char *str)
// {
// 	int	count;
// 	int	i;

// 	count = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == ',')
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// static char	**split_rgb_components(char *color_str)
// {
// 	char	**components;
// 	char	*trimmed;

// 	trimmed = ft_strtrim_spaces(color_str);
// 	if (!trimmed)
// 		return (NULL);
// 	if (count_commas(trimmed) != 2)
// 		return (NULL);
// 	components = ft_split(trimmed, ',');
// 	return (components);
// }

// static void	free_components(char **components)
// {
// 	int	i;

// 	if (!components)
// 		return ;
// 	i = 0;
// 	while (components[i])
// 	{
// 		free(components[i]);
// 		i++;
// 	}
// 	free(components);
// }

// static int	validate_components(char **components, int *rgb)
// {
// 	int	i;

// 	if (!components)
// 		return (0);
// 	i = 0;
// 	while (components[i] && i < 3)
// 		i++;
// 	if (i != 3 || components[3] != NULL)
// 		return (0);
// 	i = 0;
// 	while (i < 3)
// 	{
// 		ft_strtrim_spaces(components[i]);
// 		rgb[i] = validate_rgb_value(components[i]);
// 		if (rgb[i] == -1)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	parse_color(char *line, char identifier, int *r, int *g, int *b)
// {
// 	char	**components;
// 	char	*color_str;
// 	int		rgb[3];

// 	if (!line || line[0] != identifier || line[1] != ' ')
// 		return (0);
// 	color_str = line + 2;
// 	components = split_rgb_components(color_str);
// 	if (!validate_components(components, rgb))
// 	{
// 		free_components(components);
// 		return (-1);
// 	}
// 	*r = rgb[0];
// 	*g = rgb[1];
// 	*b = rgb[2];
// 	free_components(components);
// 	return (1);
// }

// int	handle_floor_color(t_data *data, char *line)
// {
// 	int	r;
// 	int	g;
// 	int	b;
// 	int	result;

// 	if (data->floor_color_set)
// 		return (error_msg("Duplicate floor color"));
// 	result = parse_color(line, 'F', &r, &g, &b);
// 	if (result == 0)
// 		return (0);
// 	if (result == -1)
// 		return (error_msg("Invalid floor color format"));
// 	data->floor_r = r;
// 	data->floor_g = g;
// 	data->floor_b = b;
// 	data->floor_color_set = 1;
// 	return (1);
// }

// int	handle_ceiling_color(t_data *data, char *line)
// {
// 	int	r;
// 	int	g;
// 	int	b;
// 	int	result;

// 	if (data->ceiling_color_set)
// 		return (error_msg("Duplicate ceiling color"));
// 	result = parse_color(line, 'C', &r, &g, &b);
// 	if (result == 0)
// 		return (0);
// 	if (result == -1)
// 		return (error_msg("Invalid ceiling color format"));
// 	data->ceiling_r = r;
// 	data->ceiling_g = g;
// 	data->ceiling_b = b;
// 	data->ceiling_color_set = 1;
// 	return (1);
// }