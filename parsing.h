#ifndef PARSING_H
#define PARSING_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include  <errno.h>
# include <string.h>

# define BUFFER_SIZE 1024

typedef struct s_game
{
	char	*file_name;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_dir;
	int		textures_parsed;
	int		colors_parsed;
}	t_game;


char	*read_entire_file(char *filename);
int	count_lines(char *content);
char	**split_lines(char *content, int line_count);
void	init_game_struct(t_game *game, char *filename);
void      free_string_array(char **array);
void      free_game_struct(t_game *game);
int       ft_strlen(const char *str);


int ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_atoi(const char *str);
int ft_isspace(char c);
char *trim_whitespace(char *str);

int is_texture_line(char *line);
int is_color_line(char *line);
int validate_texture_file(char *path);

void print_error(char *msg);
int ft_isspace(char c);
int ft_strlen(const char *str);


int parse_elements(char **lines, t_game *game);
int parse_color_line(char *line, t_game *game);


#endif
