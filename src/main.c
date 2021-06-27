/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** main
*/

#include "ftp.h"
#include "program.h"
#include "parser.h"

int main(int ac, char **av)
{
    program_t *program = NULL;
    program_error_t error;
    program = init_prgm(av[0]);
    if (program == NULL || program->parser == NULL)
        return (PROGRAM_FAILURE);
    parse_arguments(ac, av, program->parser);
    if (program->parser->error.type != NO_ERROR) {
        display_parser_error(program->name, program->parser->error);
        return (PROGRAM_FAILURE);
    }
    if (program->parser->display_help == true) {
        display_help();
        return (PROGRAM_SUCESS);
    }
    error = program_start(program);
    if (error.type != NO_PGM_ERROR) {
        display_program_error(program->name, error);
        return (PROGRAM_FAILURE);
    }
    return (0);
}