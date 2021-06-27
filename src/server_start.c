/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** server_start
*/

#include "ftp.h"
#include "program.h"
#include "program_error.h"
#include <errno.h>

static void server_add_client(client_t clients[51], fd_set *ref);

static int server_accept_client(program_data_t *data)
{
    int client = 0;
    socklen_t len = sizeof(data->server.socket);

    if (!FD_ISSET(data->server.fd, &data->reference_fd_set))
        return 0;
    client = accept(data->server.fd,
    (struct sockaddr *)&data->server.socket, &len);
    if (client == -1) {
        close(data->server.fd);
        exit(84);
    }
    return (client);
}

static void server_client_is_free(client_t clients[51], fd_set *ref_fd_set,
int *fd_temp)
{
    for (size_t index = 0; index < 51; index++) {
        bool swi = false;
        if (clients[index].fd <= *fd_temp)
            continue;
        if (clients[index].status == S_READY ||
        clients[index].status == S_ERROR) {
            swi = true;
            FD_CLR(clients[index].fd, ref_fd_set);
            clients[index].status = S_BUSY;
        }
        if (clients[index].status == S_BUSY) {
            swi = true;
            FD_SET(clients[index].fd, ref_fd_set);
            clients[index].status = S_READY;
        }
        if (clients[index].status == S_VOID || !swi)
            break;
        if (clients[index].fd > *fd_temp)
            *fd_temp = clients[index].fd;
    }
}

static int server_find_client(program_data_t *data)
{
    FD_ZERO(&data->reference_fd_set);
    FD_SET(data->server.fd, &data->reference_fd_set);
    data->server_fd_tmp = data->server.fd;
    data->server.status = S_READY;
    server_client_is_free(data->clients, &data->reference_fd_set,
    &data->server_fd_tmp);
    data->select = select(data->server_fd_tmp + 1,
    &data->reference_fd_set, NULL, NULL, NULL);
    if (data->select < 0) {
        close(data->server.fd);
        exit(84);
    }
    return server_accept_client(data);
}

program_error_t server_start(program_data_t *data)
{
    program_error_t error = new_program_error(NO_PGM_ERROR, NULL, NULL);
    int client = 0;

    for (int index = 0; true; index = index < 51 - 1 ? index + 1 : 0) {
        client = server_find_client(data);
        if (client)
            server_init_client(client, &data->server.socket,
            &data->clients[index], data->server.path);
        server_add_client(data->clients, &data->reference_fd_set);
    }
    return (error);
}

static void server_add_client(client_t clients[51], fd_set *ref)
{
    char buffer[4096];
    char *command = NULL;

    for (int i = 0; i < 51; i++) {
        if (FD_ISSET(clients[i].fd, ref)) {
            memset(buffer, 0, 4096);
            if (read(clients[i].fd, buffer, 4096) < 0) {
                server_quit(&clients[i], buffer);
                continue;
            }
            command = strtok(buffer, "\r\n");
            if (command)
                server_commands(buffer, &clients[i]);
        }
    }
}