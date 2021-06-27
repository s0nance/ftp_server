/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** login_commands
*/

#include "ftp.h"
#include "program.h"
#include "program_error.h"
#include <string.h>

void server_user(client_t *client, char *buffer)
{
    char *user = NULL;

    if (!buffer || strlen(buffer) == 0)
        server_write_logs(client->fd, "530", "Permission denied.");
    else if (client->user == 1 && client->pass == 1)
        server_write_logs(client->fd, "530", "Can't change from guest user.");
    else {
        server_write_logs(client->fd, "331", "Please specify the password.");
        user = strdup(buffer);
        if (strcasecmp(user, "anonymous") == 0)
            client->user = 1;
        else
            client->user = 0;
        client->user_input = 1;
    }
}

void server_pass(client_t *client, char *buffer)
{
    clear_buffer(buffer);
    if (client->user_input == 1 && !client->user)
        server_write_logs(client->fd, "530", "Login incorrect.");
    else if (!client->user && !client->user_input)
        server_write_logs(client->fd, "503", "Login with USER first.");
    else if (client->user == 1 && client->pass == 1)
        server_write_logs(client->fd, "230", "Already logged in.");
    else if (client->user == 1 && client->pass == 0) {
        client->pass = 1;
        server_write_logs(client->fd, "230", "Login successful.");
    }
}