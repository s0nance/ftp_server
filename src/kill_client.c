/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** kill_client
*/

#include "ftp.h"
#include "program.h"
#include "program_error.h"

program_data_t *static_data(void)
{
    static program_data_t data = {};

    return &data;
}

void clear_buffer(char *buffer)
{
    if (buffer)
        memset(buffer, 0, strlen(buffer));
}

void killer(void *ptr)
{
    if (ptr) {
        free(ptr);
        ptr = NULL;
    }
}

void kill_client(client_t *client)
{
    program_data_t *data = static_data();

    if (!client || client > &data->clients[50] || client < &data->clients[0])
        return;
    client->status = S_BUSY;
    client->port = 0;
    killer(client->in);
    killer(client->out);
    killer(client->path);
    killer(client->pwd);
    FD_CLR(client->fd, &data->reference_fd_set);
    close(client->fd);
    memset(client, 0, sizeof(*client));
}
