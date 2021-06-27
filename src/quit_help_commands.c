/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** quit_commands
*/

#include "ftp.h"
#include "program.h"
#include "program_error.h"

void server_quit(client_t *client, char *buffer)
{
    for (int i=0; buffer && buffer[i] && i < 4096; buffer[i] = 0, i++);
    server_write_logs(client->fd, "221", "Goodbye.");
    kill_client(client);
}

void server_unk_cmd(client_t *client, char *buffer)
{
    clear_buffer(buffer);
    if (client->user == 0 && client->pass == 0) {
        server_write_logs(client->fd, "530","Please login with USER and PASS.");
    } else
        server_write_logs(client->fd, "500", "Unknown command.");
}

void server_help(client_t *client, char *buffer)
{
    char *str = "214-The following commands are recognized.";
    char *str2 = " CDUP CWD  DELE HELP LIST NOOP PASS PASV PORT PWD "
    " QUIT RETR STOR USER";
    clear_buffer(buffer);

    if (client->user == 0 || client->pass == 0)
        server_write_logs(client->fd, "530",
        "Please login with USER and PASS.");
    else {
        server_write_logs(client->fd, NULL, str);
        server_write_logs(client->fd, NULL, str2);
        server_write_logs(client->fd, "214", "Help OK.");
    }
}