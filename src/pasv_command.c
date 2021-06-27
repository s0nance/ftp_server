/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** pasv_command
*/

#include "ftp.h"
#include "program.h"
#include "program_error.h"
#include <stdio.h>

static int create_passive_socket(client_t *client)
{
    socklen_t len_socket = sizeof(client->transfer.t_socket);

    client->transfer.fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->transfer.fd == -1)
        return (-1);
    client->transfer.t_socket.sin_family = AF_INET;
    client->transfer.t_socket.sin_addr.s_addr = INADDR_ANY;
    client->transfer.t_socket.sin_port = htons(0);
    if (bind(client->transfer.fd, (struct sockaddr *)&client->transfer.t_socket,
    sizeof(client->transfer.t_socket)) == -1)
        return (-1);
    getsockname(client->transfer.fd,
    (struct sockaddr *)&client->transfer.t_socket, &len_socket);
    listen(client->transfer.fd, 10);
    return(0);
}

static void set_pasv_server(client_t *client)
{
    char res[512];
    program_data_t *data = static_data();
    struct in_addr ip;
    socklen_t len_ip = sizeof(ip);

    ip.s_addr = INADDR_ANY;
    getsockname(data->server.fd, (struct sockaddr *)&ip, &len_ip);
    sprintf(res, "Entering passive mode (0,0,0,0,%d,%d).",
    ntohs(client->transfer.t_socket.sin_port) / 256,
    ntohs(client->transfer.t_socket.sin_port) % 256);
    client->transfer.t_mode = T_PASSIVE;
    server_write_logs(client->fd, "227", res);
}

void server_pasv(client_t *client, char *buffer)
{
    int socket_generated = 0;

    clear_buffer(buffer);
    if (client->user == 0 && client->pass == 0) {
        server_write_logs(client->fd, "530","Please login with USER and PASS.");
    } else {
        socket_generated = create_passive_socket(client);
        if (socket_generated == 0) {
            set_pasv_server(client);
        } else {
            server_write_logs(client->fd, "500",
            "Unable to enter passive mode.");
        }
    }
}