#include "parsing.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}


char	*trim_whitespace(char *str)
{
	char	*start;
	char	*end;
	char	*result;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	start = str;
	while (ft_isspace(*start))
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	end = str + ft_strlen(str) - 1;
	while (end > start && ft_isspace(*end))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = start[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*read_entire_file(char *filename)
{
	int		fd;
	char	buffer[BUFFER_SIZE];
	char	*content;
	char	*temp;
	int		bytes_read;
	int		total_size;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	content = malloc(1);
	if (!content)
		return (NULL);
	content[0] = '\0';
	total_size = 0;
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		temp = malloc(total_size + bytes_read + 1);
		if (!temp)
		{
			free(content);
			close(fd);
			return (NULL);
		}
		if (total_size > 0)
		{
			int i = 0;
			while (i < total_size)
			{
				temp[i] = content[i];
				i++;
			}
		}
		int j = 0;
		while (j < bytes_read)
		{
			temp[total_size + j] = buffer[j];
			j++;
		}
		temp[total_size + bytes_read] = '\0';
		free(content);
		content = temp;
		total_size += bytes_read;
	}
	close(fd);
	if (bytes_read == -1)
	{
		free(content);
		return (NULL);
	}
	return (content);
}

int	count_lines(char *content)
{
	int	count;
	int	i;

	if (!content)
		return (0);
	count = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\n')
			count++;
		i++;
	}
	if (i > 0 && content[i - 1] != '\n')
		count++;
	return (count);
}

char	**split_lines(char *content, int line_count)
{
	char	**lines;
	int		i;
	int		j;
	int		start;
	int		line_idx;

	lines = malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		return (NULL);
	i = 0;
	line_idx = 0;
	while (content[i] && line_idx < line_count)
	{
		start = i;
		while (content[i] && content[i] != '\n')
			i++;
		lines[line_idx] = malloc(i - start + 1);
		if (!lines[line_idx])
		{
			while (line_idx > 0)
				free(lines[--line_idx]);
			free(lines);
			return (NULL);
		}
		j = 0;
		while (start + j < i)
		{
			lines[line_idx][j] = content[start + j];
			j++;
		}
		lines[line_idx][j] = '\0';
		if (content[i] == '\n')
			i++;
		line_idx++;
	}
	lines[line_idx] = NULL;
	return (lines);
}

void	init_game_struct(t_game *game, char *filename)
{
	game->file_name = ft_strdup(filename);
	game->north_texture = NULL;
	game->south_texture = NULL;
	game->west_texture = NULL;
	game->east_texture = NULL;
	game->floor_color[0] = -1;
	game->floor_color[1] = -1;
	game->floor_color[2] = -1;
	game->ceiling_color[0] = -1;
	game->ceiling_color[1] = -1;
	game->ceiling_color[2] = -1;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->player_x = -1;
	game->player_y = -1;
	game->player_dir = '\0';
	game->textures_parsed = 0;
	game->colors_parsed = 0;
}

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_game_struct(t_game *game)
{
	if (game->file_name)
		free(game->file_name);
	if (game->north_texture)
		free(game->north_texture);
	if (game->south_texture)
		free(game->south_texture);
	if (game->west_texture)
		free(game->west_texture);
	if (game->east_texture)
		free(game->east_texture);
	if (game->map)
		free_string_array(game->map);
}