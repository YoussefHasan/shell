#ifndef USHELL_H
#define USHELL_H

#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>
#include <fcntl.h>




#define STDIN		0
#define STDOUT		1
#define STDERR		2

#define MAX_LINE       1024

void print_greeting();
char *PWD();
int change_dir(char *new_path);
void shell_exit();
void display_guide();
char* type(char* cmd);
int envir();
void execute_external_command(char* cmd);
void free_command();
int uptime_command();
void redirect_io(char *cmd, char *infile, char *outfile, char *errfile);
void pipe_commands(char *cmd1, char *cmd2);
char *get_file_name(char *path);
int cp(char *source_path, char *target_path);
int mv(char *source_path, char *target_path);


#endif
