/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** init_client
*/

#include "ftp.h"
#include "program.h"
#include "program_error.h"

void server_init_client(int fd, struct sockaddr_in *server,
client_t *client, char *home_path)
{
    struct sockaddr_in socket;
    socklen_t len = sizeof(socket);

    client->fd = fd;
    client->status = S_BUSY;
    client->transfer.t_mode = T_NONE;
    if (getsockname(fd, (struct sockaddr *)&socket, &len) == -1) {
        close(fd);
        exit(84);
    }
    client->user = 0;
    client->port = ntohs(server->sin_port);
    client->in = strdup(inet_ntoa(socket.sin_addr));
    client->out = strdup(inet_ntoa(server->sin_addr));
    client->path = strdup(home_path);
    server_write_logs(fd, "220", "(vsFTPd 3.0.0)");
}