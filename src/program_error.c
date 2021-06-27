/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** program_error
*/

#include "program_error.h"
#include <stdlib.h>
#include <string.h>

program_error_t new_program_error(program_error_type_t type,
char *message, char *where)
{
    program_error_t error;

    error.type = type;
    if (message != NULL) {
        error.message = strdup(message);
    } else {
        error.message = NULL;
    }

    if (where != NULL) {
        error.where = strdup(where);
    } else {
        error.where = NULL;
    }

    return (error);
}