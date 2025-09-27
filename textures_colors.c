#include "parsing.h"

int is_texture_line(char *line)
{
    char *trimmed;

    trimmed = trim_whitespace(line);
    if (!trimmed)
        return (0);
    if (ft_strncmp(trimmed, "NO ", 3) == 0 || ft_strncmp(trimmed, "SO ", 3) == 0 || ft_strncmp(trimmed, "WE ", 3) == 0 || ft_strncmp(trimmed, "EA ", 3) == 0)
    {
        free(trimmed);
        return (1);
    }
    free(trimmed);
    return (0);
}

int is_color_line(char *line)
{
    char *trimmed;

    trimmed = trim_whitespace(line);
    if (!trimmed)
        return (0);
    if (ft_strncmp(trimmed, "F ", 2) == 0 || ft_strncmp(trimmed, "C ", 2) == 0)
    {
        free(trimmed);
        return (1);
    }
    free(trimmed);
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
    int i = 0;
    char *start;
    char *result;
    int len;

    while (trimmed[i] && !ft_isspace(trimmed[i]))
        i++;
    while (trimmed[i] && ft_isspace(trimmed[i]))
        i++;

    start = trimmed + i;
    len = ft_strlen(start);
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
    i = len - 1;
    while (i >= 0 && ft_isspace(result[i]))
    {
        result[i] = '\0';
        i--;
    }
    return (result);
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

// fix things
static int	ft_isdigit_str(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	count_commas(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

static char	*extract_number(char *str, int *pos)
{
	char	*result;
	int		start;
	int		len;
	int		i;

	while (str[*pos] && ft_isspace(str[*pos]))
		(*pos)++;
	start = *pos;
	while (str[*pos] && str[*pos] >= '0' && str[*pos] <= '9')
		(*pos)++;
	len = *pos - start;
	if (len == 0)
		return (NULL);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = str[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static int	validate_rgb_component(char *component)
{
	int	value;

	if (!ft_isdigit_str(component))
		return (-1);
	value = ft_atoi(component);
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

static int	parse_rgb_components(char *color_str, int *rgb)
{
	int		pos;
	int		i;
	char	*component;
	int		value;

	pos = 0;
	i = 0;
	while (i < 3)
	{
		component = extract_number(color_str, &pos);
		if (!component)
			return (0);
		value = validate_rgb_component(component);
		free(component);
		if (value == -1)
			return (0);
		rgb[i] = value;
		while (color_str[pos] && ft_isspace(color_str[pos]))
			pos++;
		if (i < 2)
		{
			if (color_str[pos] != ',')
				return (0);
			pos++;
		}
		i++;
	}
	while (color_str[pos] && ft_isspace(color_str[pos]))
		pos++;
	return (color_str[pos] == '\0' ? 1 : 0);
}

int	parse_colors_values(char *color_str, int *rgb)
{
	char	*trimmed;
	int		result;

	if (!color_str)
		return (0);
	trimmed = trim_whitespace(color_str);
	if (!trimmed)
		return (0);
	if (count_commas(trimmed) != 2)
	{
		free(trimmed);
		return (0);
	}
	result = parse_rgb_components(trimmed, rgb);
	free(trimmed);
	return (result);
}