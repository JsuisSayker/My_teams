/*
** EPITECH PROJECT, 2022
** my_putnbr
** File description:
** permet d'afficher des nombre
*/

#include "proto_lib.h"

int my_put_nbr(int nb)
{
    if (nb < 0) {
        if (my_putchar('-') == -1)
            return -1;
        nb = nb * -1;
    }
    if (nb > 9){
        if (my_put_nbr(nb / 10) == -1)
            return -1;
        if (my_putchar(nb % 10 + 48) == -1)
            return -1;
    } else {
        if (my_putchar(nb + 48) == -1)
            return -1;
    }
    return 0;
}
