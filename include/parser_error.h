/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** parser_error
*/

#ifndef PARSER_ERROR_H_
#define PARSER_ERROR_H_

enum parser_error_type {
    NO_ERROR,
    INVALID_ARGS,
    INVALID_SYNTAX,
    INVALID_FLAG
};

typedef enum parser_error_type parser_error_type_t;

struct parser_error_s {
    char *message;
    parser_error_type_t type;
};

typedef struct parser_error_s parser_error_t;

#endif /* !PARSER_ERROR_H_ */
