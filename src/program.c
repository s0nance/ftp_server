/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** program
*/

#include "program.h"
#include "parser_error.h"
#include <libgen.h>

const unsigned int PROGRAM_FAILURE = 84;
const unsigned int PROGRAM_SUCESS = 0;

void display_help(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("\tport is the port number on which the server socket listens\n");
    printf("\tpath is the path to the home directory for the Anonymous user\n");
}

void display_parser_error(char *name, parser_error_t error)
{
    fprintf(stderr, "%s: %s\n", name, error.message);
}

void display_program_error(char *name, program_error_t error)
{
    fprintf(stderr, "%s: %s\n", name, error.message);
}

program_t *init_prgm(char *prgm)
{
    program_t *program = NULL;

    if ((program = malloc(sizeof(program_t))) == NULL) {
        return (NULL);
    }

    program->name = basename(prgm);
    program->parser = init_parser();

    return (program);
}