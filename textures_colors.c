#include "parsing.h"

int	is_texture_line(char *line)
{
          char *trimmed;

          trimmed = trim_whitespace(line);
          if (!trimmed)
                    return (0);
          if (ft_strncmp(trimmed, "NO ", 3) == 0
                    || ft_strncmp(trimmed, "SO ", 3) == 0
                    || ft_strncmp(trimmed, "WE ", 3) == 0
                    || ft_strncmp(trimmed, "EA ", 3) == 0
          )
          {
                    free (trimmed);
                    return (1);
          }
          free (trimmed);
          return (0);
}

int is_color_line(char *line)
{
          char *trimmed;

          trimmed = trim_whitespace(line);
          if (!trimmed)
                    return (0);
          if (ft_strncmp(trimmed, "F ", 2) == 0
                    || ft_strncmp(trimmed, "C ", 2) == 0)
          {
                    free (trimmed);
                    return (1);
          }
          free (trimmed);
          return (0);
}

int validate_texture_file(char *path)
{
          int fd;

          if (!path)
                    return (0);
          fd = open(path, O_RDONLY);
          if (fd == -1)
                    return (0);
          close(fd);
          return (1);
}

static char *get_texture_path(char *trimmed)
{
          int i;

          i = 0;
          while (trimmed[i] && ft_isspace(trimmed[i]))
                    i++;
          while (trimmed[i] && !ft_isspace(trimmed[i]))
                    i++;
          return (trimmed + i);
}

static void assign_texture(t_game *game, char *trimmed, char *path)
{
	if (ft_strncmp(trimmed, "NO", 2) == 0)
		game->north_texture = path;
	else if (ft_strncmp(trimmed, "SO", 2) == 0)
		game->south_texture = path;
	else if (ft_strncmp(trimmed, "WE", 2) == 0)
		game->west_texture = path;
	else if (ft_strncmp(trimmed, "EA", 2) == 0)
		game->east_texture = path;
}

int parse_texture_line(char *line, t_game *game)
{
	char *trimmed, *path;

	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (0);

	path = get_texture_path(trimmed);
	if (!path)
	{
		free(trimmed);
		return (0);
	}
	if (!validate_texture_file(path))
	{
		printf("Error: Texture file not found: %s\n", path);
		free(path);
		free(trimmed);
		return (0);
	}
	assign_texture(game, trimmed, path);
	free(trimmed);
	return (1);
}


int parse_colors_values(char *color_str, int *rgb)
{
          int i;
          int value;
          int color_count;

          i = 0;
          color_count = 0;
          while (color_str[i] && color_count < 3)
          {
                    while (color_str[i] && !('0' <= color_str[i] && color_str[i] <= '9'))
                              i++;
                    if (!color_str[i])
                              break;
                    value = ft_atoi(color_str + 1);
                    if (value < 0 || value > 255)
                              return (0);
                    rgb[color_count++] = value;
                    color_count++;
                    while (color_str[i] && ('0' <= color_str[i] && color_str[i] <= '9'))
			i++;
          }
          return (color_count == 3);
}
