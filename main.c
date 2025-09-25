#include "parsing.h"


int validate_extension(char *file_name)
{
          int len;

          if (!file_name)
                    return (0);
          len = ft_strlen(file_name);
          if (len < 5)
                    return (0);
          if (ft_strncmp(file_name + len - 4, ".cub", 4) != 0)
                    return (0);
          return (1);
}

int is_directory(char *path)
{
          int fd;

          fd = open(path, O_DIRECTORY);
          if (fd >= 0)
          {
                    close(fd);
                    return (1);
          }
          return (0);
}

int file_exists_and_readable(char *file_name)
{
          int fd;

          fd = open(file_name, O_RDONLY);
          if (fd == -1)
          {
                    printf("Error: Cannot open file '%s': %s\n", file_name, strerror(errno));
                    return (0);
          }
          close(fd);
          return (1);
}

int valid_argument(int argc, char **argv)
{
          if (argc != 2)
          {
                    print_error("Invalid number of arguments");
                    return (0);
          }

          if (!argv[1])
          {
                    print_error("Invalid argument: NULL file path");
                    return (0);
          }

          if (is_directory(argv[1]))
          {
                    print_error("Argument is a directory, not a file");
                    return (0);
          }

          if (!file_exists_and_readable(argv[1]))
                    return (0);

          if (!validate_extension(argv[1]))
          {
                    print_error("Invalid file extension. Use .cub files only");
                    return (0);
          }

          return (1);
}

int main(int argc, char **argv)
{
	t_game	game;
	char	*file_content;
	char	**lines;
	int		line_count;

	if (!valid_argument(argc, argv))
		return (1);
	
	init_game_struct(&game, argv[1]);
	
	file_content = read_entire_file(argv[1]);
	if (!file_content)
	{
		print_error("Failed to read file");
		free_game_struct(&game);
		return (1);
	}
	
	line_count = count_lines(file_content);
	if (line_count == 0)
	{
		print_error("Empty file");
		free(file_content);
		free_game_struct(&game);
		return (1);
	}
	
	lines = split_lines(file_content, line_count);
	if (!lines)
	{
		print_error("Failed to split file content");
		free(file_content);
		free_game_struct(&game);
		return (1);
	}
	
	printf("Successfully read %d lines from %s\n", line_count, argv[1]);
	
	free(file_content);
	free_string_array(lines);
	free_game_struct(&game);
	
	return (0);
}