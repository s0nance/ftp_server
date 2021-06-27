/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** parse_flag
*/

#include "parser.h"
#include "parser_error.h"
#include <string.h>

static char *flag_error_message(char *flag)
{
    char *message = calloc(1, sizeof(char) * strlen(flag) +
    strlen("Flag doesn't exist or not implemented '") + 2);

    if (message == NULL) {
        return (NULL);
    }

    message = strcat(message, "Flag doesn't exist or not implemented '");
    message = strcat(message, flag);
    message = strcat(message, "'");

    return (message);
}

parser_error_type_t parse_flag(char *flag, parser_t *parser)
{
    parser_error_type_t type_error = NO_ERROR;

    if (strlen(flag) == 1) {
        type_error = INVALID_SYNTAX;
    }
    if (strcmp(flag, "-help") == 0) {
        parser->display_help = true;
    } else {
        parser->error.message = flag_error_message(flag);
        type_error = INVALID_FLAG;
    }
    return (type_error);
}