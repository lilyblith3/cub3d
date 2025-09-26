#include "parsing.h"

static char *get_color_part(char *trimmed)
{
    int i;

    i = 0;
    while (trimmed[i] && !ft_isspace(trimmed[i]))
        i++;
    while (trimmed[i] && ft_isspace(trimmed[i]))
        i++;
    return (trimmed + i);
}

static int assign_color(char *trimmed, char *color_part, t_game *game)
{
    if (ft_strncmp(trimmed, "F", 1) == 0)
    {
        if (!_values(color_part, game->floor_color))
        {
            printf("Error: Invalid floor color format\n");
            return (0);
        }
    }
    else if (ft_strncmp(trimmed, "C", 1) == 0)
    {
        if (!parse_color_values(color_part, game->ceiling_color))
        {
            printf("Error: Invalid ceiling color format\n");
            return (0);
        }
    }
    return (1);
}

int parse_color_line(char *line, t_game *game)
{
    char *trimmed;
    char *color_part;
    int result;

    trimmed = trim_whitespace(line);
    if (!trimmed)
        return (0);
    color_part = get_color_part(trimmed);
    result = assign_color(trimmed, color_part, game);
    free(trimmed);
    return (result);
}

static int process_line(char *line, t_game *game, int *elements_found)
{
    if (ft_strlen(line) == 0)
        return (1);
    if (is_texture_line(line))
    {
        if (!parse_texture_line(line, game))
            return (0);
        (*elements_found)++;
        return (1);
    }
    if (is_color_line(line))
    {
        if (!parse_color_line(line, game))
            return (0);
        (*elements_found)++;
        return (1);
    }
    if (*elements_found >= 6)
        return (1);
    printf("Error: Invalid line format: %s\n", line);
    return (0);
}

int parse_elements(char **lines, t_game *game)
{
    int i;
    int elements_found;

    i = 0;
    elements_found = 0;
    while (lines[i])
    {
        if (!process_line(lines[i], game, &elements_found))
            return (0);
        if (elements_found >= 6 && ft_strlen(lines[i]) > 0)
            break;
        i++;
    }
    if (elements_found != 6)
    {
        printf("Error: Missing elements (found %d/6)\n", elements_found);
        return (0);
    }
    return (i);
}