/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** program_error
*/

#ifndef PROGRAM_ERROR_H_
#define PROGRAM_ERROR_H_

enum program_error_type {
    NO_PGM_ERROR,
    INVALID_DIR,
    INVALID_FILE,
    INVALID_FD,
    INVALID_PROTOTYPE,
    INVALID_BIND,
    INVALID_PATH,
    INVALID_FD_LISTEN,
    INVALID_SET_FD,
    FORK_ERROR,
    MEMORY_ERROR,
    ERROR_PARSING_CMD,
};

typedef enum program_error_type program_error_type_t;

struct program_error_s {
    program_error_type_t type;
    char *message;
    char *where;
};

typedef struct program_error_s program_error_t;

program_error_t new_program_error(program_error_type_t type,
char *message, char *where);

#endif /* !PROGRAM_ERROR_H_ */
