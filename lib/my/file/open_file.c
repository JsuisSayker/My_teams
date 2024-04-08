/*
** EPITECH PROJECT, 2023
** my
** File description:
** open_file
*/

#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char *open_file(char const *file)
{
    int fd;
    int bytes;
    struct stat st;
    char *str = NULL;

    if (file == NULL)
        return NULL;
    if (stat(file, &st) == -1)
        return NULL;
    str = malloc(sizeof(char) * (st.st_size + 1));
    fd = open(file, O_RDONLY);
    bytes = read(fd, str, st.st_size);
    if (bytes == -1)
        return NULL;
    str[st.st_size] = '\0';
    close(fd);
    return (str);
}
