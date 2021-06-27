/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** retr_command
*/

#include "ftp.h"
#include "program.h"
#include "program_error.h"
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>

static void retr_command(client_t *client)
{
    server_write_logs(client->fd, "150",
    "File status okay; about to open data connection.");
    client->transfer.buffer[0] = 0;
    while ((client->transfer.retr_size = read(client->transfer.retr,
    client->transfer.buffer, 1)) > 0) {
        if (client->transfer.buffer[0] == '\n')
            write(client->transfer.client_fd, "\r\n", 2);
        else
            write(client->transfer.client_fd, client->transfer.buffer,
            client->transfer.retr_size);
    }
    server_write_logs(client->fd, "226", "Requested file action successful.");
    close(client->transfer.retr);
    return;
}

void server_retr(client_t *client, char *buffer)
{
    struct in_addr ip;
    socklen_t len_ip = sizeof(ip);

    if ((client->transfer.t_mode != T_PASSIVE &&
    client->transfer.t_mode != T_ACTIVE)
    && client->user == 1 && client->pass == 1)
        server_write_logs(client->fd, "425", "Use PORT or PASV first.");
    else if (client->user == 0 && client->pass == 0) {
        server_write_logs(client->fd, "530","Please login with USER and PASS.");
    } else if ((client->transfer.client_fd = accept(client->transfer.fd,
    (struct sockaddr *)&client->transfer.t_socket, &len_ip)) == -1) {
        server_write_logs(client->transfer.client_fd, "550", "Socket error");
    } else if (access(buffer, R_OK | F_OK) == -1) {
        server_write_logs(client->fd, "550", "Error access.");
    } else if ((client->transfer.retr = open(buffer, O_RDONLY)) == -1) {
        server_write_logs(client->fd, "550", "Error opening file.");
    } else
        retr_command(client);
    client->transfer.t_mode = T_NONE;
    close(client->transfer.client_fd);
    return;
}
