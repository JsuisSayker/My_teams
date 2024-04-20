/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** get_time
*/

#include <string.h>
#include <time.h>
#include "macro.h"

int get_time(char (*dest)[TIME_LENGTH])
{
    time_t actual_time;
    struct tm *time_info;
    char time_form[TIME_LENGTH];

    if ((*dest) == NULL)
        return ERROR;
    time(&actual_time);
    time_info = localtime(&actual_time);
    strftime(time_form, sizeof(time_form), "%a %b %d %H:%M:%S %Y", time_info);
    if (strcpy((*dest), time_form) == NULL)
        return ERROR;
    return OK;
}
