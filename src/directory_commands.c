/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** directory_commands
*/

#include "ftp.h"
#include "program.h"
#include "program_error.h"

void server_pwd(client_t *client, char *buffer)
{
    char path[4096] = {};

    clear_buffer(buffer);
    if (client->user == 0 && client->pass == 0) {
        server_write_logs(client->fd, "530",
        "Please login with USER and PASS.");
    } else if (getcwd(path, sizeof(path)) != NULL) {
        server_write_logs(client->fd, "257", path);
    }
}

void server_cdup(client_t *client, char *buffer)
{
    clear_buffer(buffer);
    if (client->user == 0 && client->pass == 0) {
        server_write_logs(client->fd, "530",
        "Please login with USER and PASS.");
    } else {
        chdir("../");
        server_write_logs(client->fd, "250",
        "Directory successfully changed.");
    }
}

void server_cwd(client_t *client, char *buffer)
{
    struct stat sb;

    if (client->user == 0 && client->pass == 0) {
        server_write_logs(client->fd, "530",
        "Please login with USER and PASS.");
    } else {
        if (stat(buffer, &sb) == 0 && S_ISDIR(sb.st_mode)) {
            if (chdir(buffer) >= 0) {
                client->pwd = strdup(buffer);
                chdir(client->pwd);
                server_write_logs(client->fd, "250",
                "Directory successfully changed.");
            } else
                server_write_logs(client->fd, "550",
                "Failed to change directory.");
        } else
            server_write_logs(client->fd, "550",
                "Failed to change directory.");
    }
}