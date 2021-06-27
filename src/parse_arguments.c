/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** parse_arguments
*/

#include "parser.h"
#include "parser_error.h"
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

static char* error_messages[4] = {INVALID_ARG, INVALID_ARG_NB,
NO_ARG_PROVIDED, INVALID_PORT};

static char *argument_error_message(int case_nb)
{
    char *message = calloc(1, sizeof(char) *
    strlen(error_messages[case_nb - 1]) + 2);
    if (message == NULL)
            return (NULL);

    message = strcat(message, error_messages[case_nb - 1]);

    return (message);
}

static int get_port(char *str)
{
    char *ptr;
    errno = 0;
    long port = strtol(str, &ptr, 10);
    int result = 0;

    if (errno != 0 || *ptr != '\0' || port > INT_MAX || port < INT_MIN)
        return (0);
    else {
        if (port > 65535 || port < 0)
            return (-1);
        result = port;
        return (result);
    }
}

static char *get_path(char *str)
{
    char *path = calloc(1, sizeof(char) * strlen(str) + 2);

    path = strcat(path, str);

    return (path);
}

static parser_error_type_t parse_port_path(char **av, parser_t *parser)
{
    parser_error_type_t type_error = NO_ERROR;
    int port = 0;
    char *path = NULL;

    port = get_port(av[1]);
    path = get_path(av[2]);

    if (port == 0 || path == NULL) {
        parser->error.message = argument_error_message(1);
        type_error = INVALID_ARGS;
    } else {
        if (port == (-1)) {
            parser->error.message = argument_error_message(4);
            return (type_error = INVALID_ARGS);
        }
        parser->port = port;
        parser->path = path;
    }
    return (type_error);
}

void parse_arguments(int ac, char **av, parser_t *parser)
{
    parser_error_type_t type_error = NO_ERROR;

    if (ac == 1) {
        parser->error.message = argument_error_message(3);
        type_error = INVALID_ARGS;
    } else {
        if (ac == 2 && av[1][0] == '-') {
            type_error = parse_flag(av[1], parser);
        } else if (ac == 3) {
            type_error = parse_port_path(av, parser);
        } else {
            parser->error.message = argument_error_message(2);
            type_error = INVALID_ARGS;
        }
    }
    parser->error.type = type_error;
}