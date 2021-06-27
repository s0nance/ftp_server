/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** parser
*/

#include "parser.h"

static void init_struct(parser_t *parser)
{
    parser->display_help = false;
    parser->error.message = NULL;
    parser->error.message = NO_ERROR;
    parser->path = NULL;
    parser->port = 0;
}

parser_t *init_parser(void)
{
    parser_t *parser = NULL;

    if ((parser = malloc(sizeof(parser_t))) == NULL) {
        return (NULL);
    }

    init_struct(parser);

    return (parser);
}