/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** commands
*/

#include "ftp.h"
#include "program.h"
#include "program_error.h"
#include <string.h>
#include <stdio.h>

void server_write_logs(int file_descriptor, char *reply_code,
char *message) {
    if (reply_code)
        dprintf(file_descriptor, "%s ", reply_code);
    dprintf(file_descriptor, "%s\r\n", message);
}

static cmd_data_t commands[] = {
    {"QUIT", server_quit, 0, 4},
    {"USER", server_user, 0, 4},
    {"PASS", server_pass, 0, 4},
    {"HELP", server_help, 0, 4},
    {"DELE", server_dele, 0, 4},
    {"NOOP", server_noop, 0, 4},
    {"PWD", server_pwd, 0, 3},
    {"CDUP", server_cdup, 0, 4},
    {"CWD", server_cwd, 0, 3},
    {"pasv", server_pasv, 0, 4},
    {"list", server_list, 1, 4},
    {"retr", server_retr, 1, 4},
    {NULL, server_unk_cmd, 0, 0}
};


static void server_fork(client_t *client, func ptr, char *arg)
{
    int death = 0;
    pid_t pid = fork();

    if (pid < 0) {
        server_write_logs(client->fd, "451",
        "Requested action aborted: local error in processing.");
        kill(getpid(), SIGINT);
    } else if (pid > 0) {
        waitpid(pid, &death, 0);
    } else
        ptr(client, arg);
}

static cmd_ptr_t *server_find_commands(char *buffer)
{
    static cmd_ptr_t ptr = {NULL, server_unk_cmd, 0};
    char *command = NULL;

    ptr.str = NULL;
    ptr.ptr = server_unk_cmd;
    ptr.reload = 0;
    if (strlen(buffer) < 3)
        return &ptr;
    command = strtok(buffer, " ");
    if (!command)
        return &ptr;
    for (int index = 0; commands[index].str; index++) {
        if (!strncasecmp(commands[index].str, command, commands[index].len)) {
            ptr.ptr = commands[index].ptr;
            ptr.reload = commands[index].reload;
            break;
        }
    }
    ptr.str = strtok(NULL, "\r\n");
    return &ptr;
}

void server_commands(char *buffer, client_t *client)
{
    cmd_ptr_t *cmd = server_find_commands(buffer);

    if (cmd->reload)
        server_fork(client, cmd->ptr, cmd->str);
    else
        cmd->ptr(client, cmd->str);
}