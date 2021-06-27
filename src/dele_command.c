/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** dele_command
*/

#include "ftp.h"
#include "program.h"
#include "program_error.h"

void server_dele(client_t *client, char *buffer)
{
    if (client->user == 0 && client->pass == 0) {
        server_write_logs(client->fd, "530",
        "Please login with USER and PASS.");
        return;
    }
    if (remove(buffer) < 0)
        server_write_logs(client->fd, "550", "Permission denied.");
    else
        server_write_logs(client->fd, "250",
        "Requested file action okay, completed.");
}