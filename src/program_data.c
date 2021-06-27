/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** program_data
*/

#include "program.h"

static void init_data_server(program_data_t *data)
{
    data->server.fd = socket(AF_INET, SOCK_STREAM,
    data->server.protoent->p_proto);
    if (data->server.fd == -1) {
        close(data->server.fd);
        exit(84);
    }
    data->server.socket.sin_port = htons(data->server.port);
    data->server.socket.sin_family = AF_INET;
    data->server.socket.sin_addr.s_addr = htonl(INADDR_ANY);
}

program_data_t *init_data_struct(program_t *program)
{
    program_data_t *data = static_data();
    data->error = new_program_error(NO_ERROR, NULL, NULL);

    if (getprotobyname("TCP"))
        data->server.protoent = getprotobyname("TCP");
    else {
        data->error = new_program_error(INVALID_PROTOTYPE,
        "Error: couldn't get the TCP protocol", "init_data_struct");
        return (data);
    }
    data->server.port = program->parser->port;
    data->server.path = program->parser->path;
    init_data_server(data);

    return (data);
}