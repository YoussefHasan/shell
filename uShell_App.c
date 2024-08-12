#include "uShell.h"

int main(int argc, char** argv)
{
	print_greeting();
	char command_line[MAX_LINE];
	ssize_t read_size = 0;
	
	while (1)
	{
		char *current_pwd = PWD();
		char *shell_msg = malloc(1024);
		strcpy(shell_msg, "3m el kawkab@");
		strcat(shell_msg, current_pwd);
		strcat(shell_msg, "  laghiny $ ");
		write(STDOUT, shell_msg, strlen(shell_msg));
		read_size = read(STDIN, command_line, MAX_LINE);
		char *token = strtok(command_line, " \n");
		while (token != NULL)
		{
			if (strcmp(token, "mypwd") == 0)
			{
				printf("%s\n", current_pwd);
				break;
			}
			else if (strcmp(token, "myenv") == 0)
			{
				envir();
				break;
			}
			else if  (strcmp(token, "mycd") == 0)
			{
				char *new_path = strtok(NULL, " \n");
				change_dir(new_path);
				break;
			}
			else if (strcmp((char*) "myecho", (char*) token) == 0)
			{
        			while ((token = strtok(NULL, " \n")) != NULL)
				{
					write(STDOUT, token, strlen(token));
					write(STDOUT, " ", 1);
				}
				printf("\n");
			}
			else if  (strcmp(token, "mytype") == 0)
			{
				char *cmd = strtok(NULL, " \n");
				printf("Type of command: %s\n", type(cmd));
				break;
			}
			else if (strcmp(token, "mycp") == 0)
			{
				char *source_path = strtok(NULL, " \n");
				char *target_path = strtok(NULL, " \n");
				cp(source_path, target_path);
				break;
			}
			else if (strcmp(token, "mymv") == 0)
			{
				char *source_path = strtok(NULL, " \n");
				char *target_path = strtok(NULL, " \n");
				mv(source_path, target_path);
				break;
			}
			else if  (strcmp(token, "myhelp") == 0)
			{
				display_guide();
				break;
			}
			else if  (strcmp(token, "myexit") == 0)
			{
				printf("Are you sure you want to exit? (confirm by entering y)\n");
				char confirm;
				scanf("%c", &confirm);
				if (confirm == 'y')
					{shell_exit();}
				else
				{
					printf("unrecognized option\n");
					break;
				}
			}
			else if (strchr(token, '|') != NULL)
			{	// Extract commands
				char *cmd1 = strtok(token, "|");
				char *cmd2 = strtok(NULL, "\n");
				// Call pipe_commands with the extracted commands
				pipe_commands(cmd1, cmd2);
				break;
			}
			else if (strcmp(token, "myredirect") == 0)
			{
				char *cmd = strtok(NULL, " \n");
				char *infile = NULL;
				char *outfile = NULL;
				char *errfile = NULL;
				// Parse the redirection operators
				while ((token = strtok(NULL, " \n")) != NULL)
				{
					if (strcmp(token, "<") == 0)
						{infile = strtok(NULL, " \n");}
					else if (strcmp(token, ">") == 0)
						{outfile = strtok(NULL, " \n");}
					else if (strcmp(token, "2>") == 0)
						{errfile = strtok(NULL, " \n");}
				}
				// Call the redirection function
				redirect_io(cmd, infile, outfile, errfile);
				break;
			}
			else if (strcmp(token, "free") == 0)
			{
				free_command();
				break;
			}
			else if  (strcmp(token, "uptime") == 0)
			{
				uptime_command();
				break;
			}
			else
			{
				char* cmd = NULL;
				if (cmd == NULL)
				{
					cmd = (char*)malloc(strlen(token) + 1);
					strcat(cmd, " ");
					strcat(cmd, token);
				}
				else
				{
					char* temp = (char*)malloc((strlen(temp) + strlen(cmd) + 2) * sizeof(char));
					strcat(temp, cmd);
					free(cmd);
					cmd = temp;
				}
				token = strtok(NULL, "");
				execute_external_command(cmd);
			}
			
		}
		free(shell_msg);
	}
	return 0;
}
