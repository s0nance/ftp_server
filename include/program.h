/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
** File description:
** program
*/

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "ftp.h"
#include "parser.h"
#include "program_error.h"
#include "time.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <signal.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/un.h>
#include <dirent.h>

extern const unsigned int PROGRAM_FAILURE;
extern const unsigned int PROGRAM_SUCESS;

struct program_s {
    char *name;
    parser_t *parser;
};

typedef struct program_s program_t;

enum socket_status_s {
    S_BUSY = 0,
    S_READY,
    S_VOID,
    S_ERROR
};

typedef enum socket_status_s socket_status_t;

enum transfer_mode_e {
    T_PASSIVE,
    T_ACTIVE,
    T_NONE
};

typedef enum transfer_mode_e transfer_mode_t;

struct transfer_s {
    FILE *file;
    char buffer[1024];
    int retr;
    ssize_t retr_size;
    int fd;
    int client_fd;
    struct sockaddr_in t_socket;
    transfer_mode_t t_mode;
};

typedef struct transfer_s transfer_t;

struct client_s {
    int fd;
    int port;
    socket_status_t status;
    int user;
    int pass;
    int user_input;
    transfer_t transfer;
    char *pwd;
    char *path;
    char *in;
    char *out;
};

typedef struct client_s client_t;


struct server_s {
    int fd;
    socket_status_t status;
    int port;
    char *path;
    struct sockaddr_in socket;
    struct protoent *protoent;
};

typedef struct server_s server_t;

struct program_data_s {
    fd_set reference_fd_set;
    client_t clients[51];
    server_t server;
    int server_fd_tmp;
    int select;
    program_error_t error;
};

typedef struct program_data_s program_data_t;

typedef void (*func)(client_t *client, char *buffer);

struct cmd_data_s {
    const char * const str;
    func ptr;
    bool reload;
    short len;
};

typedef struct cmd_data_s cmd_data_t;

struct cmd_ptr_s {
    char *str;
    func ptr;
    bool reload;
};

typedef struct cmd_ptr_s cmd_ptr_t;


program_t *init_prgm(char *prgm);
void display_help(void);
void display_parser_error(char *name, parser_error_t error);
void display_program_error(char *name, program_error_t error);
program_error_t program_start(program_t *program);
program_data_t *init_data_struct(program_t *program);
program_error_t server_start(program_data_t *data);
void server_write_logs(int file_descriptor, char *reply_code,
char *message);
void server_init_client(int fd, struct sockaddr_in *server,
client_t *client, char *home_path);
void kill_client(client_t *client);
void killer(void *ptr);
program_data_t *static_data(void);
void close_signal(int);
void clear_buffer(char *buffer);
void server_commands(char *buffer, client_t *client);
void server_unk_cmd(client_t *client, char *buffer);
void server_quit(client_t *client, char *);
void server_user(client_t *client, char *);
void server_pass(client_t *client, char *);
void server_help(client_t *client, char *);
void server_dele(client_t *client, char *);
void server_noop(client_t *client, char *);
void server_pwd(client_t *client, char *);
void server_cdup(client_t *client, char *);
void server_cwd(client_t *client, char *);
void server_pasv(client_t *client, char *buffer);
void server_list(client_t *client, char *buffer);
void server_retr(client_t *client, char *buffer);

#endif /* !PROGRAM_H_ */
