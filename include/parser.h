/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** parser
*/

#ifndef PARSER_H_
#define PARSER_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser_error.h"

#define INVALID_ARG "Invalid port number"
#define INVALID_ARG_NB "Invalid number of arguments"
#define NO_ARG_PROVIDED "No argument provided"
#define INVALID_PORT "Invalid port number"

struct parser_s {
    bool display_help;
    char *path;
    int port;
    parser_error_t error;
};

typedef struct parser_s parser_t;

parser_t *init_parser(void);
void parse_arguments(int ac, char **av, parser_t *parser);
void parse_filename(char *filename, parser_t *parser);
parser_error_type_t parse_flag(char *flag, parser_t *parser);

#endif /* !PARSER_H_ */
