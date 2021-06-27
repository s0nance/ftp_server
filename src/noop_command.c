/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** noop_command
*/

#include "ftp.h"
#include "program.h"
#include "program_error.h"

void server_noop(client_t *client, char *buffer)
{
    clear_buffer(buffer);
    if (client->user == 0 && client->pass == 0) {
        server_write_logs(client->fd, "530",
        "Please login with USER and PASS.");
        return;
    }
    server_write_logs(client->fd, "200", "NOOP ok.");
}