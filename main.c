#include "parsing.h"

void print_error(char *msg)
{
          printf("Error: %s\n", msg);
          exit(EXIT_FAILURE);
}

int ft_strlen(const char *str)
{
          int len;

          len = 0;
          while (str[len])
                    len++;
          return (len);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
          size_t i;

          i = 0;
          while (i < n && (s1[i] || s2[i]))
          {
                    if (s1[i] != s2[i])
                              return ((unsigned char)s1[i] - (unsigned char)s2[i]);
                    i++;
          }
          return (0);
}

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
          t_game game;

          if (!validate_arguments(argc, argv))
                    return (1);
}