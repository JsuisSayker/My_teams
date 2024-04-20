/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** convert_string_to_time_t
*/

#include "client.h"
#include <time.h>

time_t convert_string_to_time_t(const char *time_string, const char *format)
{
    struct tm time_struct = {0};
    time_t time = 0;

    if (strptime(time_string, format, &time_struct) == NULL) {
        return ERROR;
    }
    time = mktime(&time_struct);
    if (time == ERROR) {
        return ERROR;
    }
    return time;
}
