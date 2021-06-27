/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** list_command
*/

#include "ftp.h"
#include "program.h"
#include "program_error.h"
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>

static void list_command(client_t *client, char *buffer)
{
    if (buffer == NULL)
        buffer = strdup("./");
    char c[1024] = {};
    strcat(c, "ls -la ");
    strcat(c, buffer);
    fprintf(stderr, "%s\n", c);
    client->transfer.file = popen(c, "r");
    server_write_logs(client->fd, "150", "Here comes the directory listing. !");
    while(!feof(client->transfer.file) && (fread(client->transfer.buffer, 1, 1, client->transfer.file)) > 0) {
        if (client->transfer.buffer[0] == '\n'
        && client->transfer.buffer != false)
            write(client->transfer.client_fd, "\r\n", 2);
        else if (client->transfer.buffer[0] != '\n'
        && client->transfer.buffer != false)
            write(client->transfer.client_fd, &client->transfer.buffer, 1);
        memset(client->transfer.buffer, 0, 1024);
    }
    server_write_logs(client->fd, "226", "Directory send OK.");
    pclose(client->transfer.file);
    client->transfer.t_mode = T_NONE;
    return;
}

void server_list(client_t *client, char *buffer)
{
    struct in_addr ip;
    socklen_t len_ip = sizeof(ip);

    if ((client->transfer.t_mode != T_PASSIVE &&
    client->transfer.t_mode != T_ACTIVE)
    && client->user == 1 && client->pass == 1)
        server_write_logs(client->fd, "425", "Use PORT or PASV first.");
    else if (client->user == 0 && client->pass == 0) {
        server_write_logs(client->fd, "530", "Please login with USER and PASS");
    } else if ((client->transfer.client_fd = accept(client->transfer.fd,
    (struct sockaddr *)&client->transfer.t_socket, &len_ip)) == -1) {
        server_write_logs(client->transfer.client_fd, "550", "Socket error");
    } else
        list_command(client, buffer);
    close(client->transfer.client_fd);
    return;
}