/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** program_start
*/

#include "ftp.h"
#include "program.h"

static program_error_t program_init_socket(program_data_t *data)
{
    program_error_t error = new_program_error(NO_PGM_ERROR, NULL, NULL);
    int setter = 1;
    if (setsockopt(data->server.fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
    &setter, sizeof(setter)) == -1 || bind(data->server.fd,
    (const struct sockaddr *)&data->server.socket,
    sizeof(data->server.socket)) == -1 || listen(data->server.fd, 51) == -1) {
        close(data->server.fd);
        return (new_program_error(INVALID_FD_LISTEN,
        "Error: cannot init socket", "program_init_socket"));
    }

    return (error);
}

program_error_t program_start(program_t *program)
{
    program_data_t *data = NULL;
    program_error_t error = new_program_error(NO_PGM_ERROR, NULL, NULL);
    DIR *directory = NULL;

    data = init_data_struct(program);
    directory = opendir(data->server.path);
    chdir(data->server.path);
    getcwd(data->server.path, 256);

    if (directory == NULL)
        return new_program_error(INVALID_DIR, "Invalid path.", "program_start");

    if (error.type == NO_PGM_ERROR)
        error = program_init_socket(data);
    if (error.type == NO_PGM_ERROR)
        error = server_start(data);
    return (error);
}