#include "uShell.h"


void print_greeting()
{
	char *text = "\nHi bud, this is a \033[1muShell\033[0m.\nHere's a simple guide for commands it can execute:\n\t\033[1;3;4mmypwd\033[0m: prints the current working directory.\n\t\033[1;3;4mmyecho\033[0m: prints a string you type.\n\t\033[1;3;4mmycp\033[0m: copies a file from source path to target path.\n\t\033[1;3;4mmymv\033[0m: moves a file from source path to target path.\n\t\033[1;3;4mmycd\033[0m: changes the current working directory.\n\t\033[1;3;4mmyhelp\033[0m: displays some help.\n\t\033[1;3;4mmyexit\033[0m: closes the uShell session.\n\n";
	write(STDOUT, text, strlen(text));
}

char *PWD()
{
	char cwd[MAX_LINE];
	getcwd(cwd, sizeof(cwd));
	return strdup(cwd);
}

int change_dir(char *new_path)
{
	if (chdir(new_path) != 0)
	{
		perror("chdir");
		return -1;
	}
	else
	{
		char current_dir[MAX_LINE];
		if (getcwd(current_dir, MAX_LINE) == NULL)
		{
			perror("getcwd");
			return -1;
		}
        return 0;
    }
}

void display_guide()
{
	char *text = "\nHere are some instructions when dealing with some commands that have arguments\n\t\033[1mcp\033[0m: cp [OPTION] SOURCE_PATH DIRECTORY_PATH.\n\t\tfor the option flag you can use \"-a\" which allows you to append the source content to the end of the target file\n\t\033[1mmv\033[0m: mv [OPTION] SOURCE_PATH DIRECTORY_PATH.\n\t\tfor the option flag you can use \"-f\" which allows you to force overwriting the target file if exists\n\n";
	write(STDOUT, text, strlen(text));
}

void shell_exit()
{
	char *text = "Exiting..\n";
	write(STDOUT, text, strlen(text));
	exit(0);
}

char *get_file_name(char *path)
{
	char *last_slash = strrchr(path, '/');
	if (last_slash == NULL)
		{return path;}		
	last_slash++;
	char *file_name = malloc(strlen(last_slash) + 1);
	strcpy(file_name, last_slash);
	return file_name;
}

int cp(char *source_path, char *target_path)
{
	if (strcmp(source_path, target_path) == 0)
 	{
 		printf("Source and target paths are the same.\n");
		return -1;
        }
        FILE *source_file = fopen(source_path, "r");
	if (source_file == NULL)
	{
		printf("Error: cannot open source file %s\n", source_path);
		return -1;
	}
	FILE *target_file;
	if (access(target_path, F_OK) != -1)
	{
		printf("Target file %s already exists\n", target_path);
		return 1;
	}
	target_file = target_file = fopen(target_path, "w");
	char buffer[MAX_LINE];
	while (fgets(buffer, MAX_LINE, source_file) != NULL)
	{
		fwrite(buffer, strlen(buffer), 1, target_file); 
		break;
	}
	fclose(source_file);
	fclose(target_file);
	return 0;
}

int mv(char *source_path, char *target_path)
{
	if (strcmp(source_path, target_path) == 0)
	{
		printf("Source and target paths are the same.\n");
		return -1;
	}
        FILE *source_file = fopen(source_path, "r");
	if (source_file == NULL)
	{
		printf("Error: cannot open source file %s\n", source_path);
		return -1;
	}
	if (access(target_path, F_OK) != -1)
	{
		printf("Target file already exists.\n");
		return -1;
	}
	FILE *target_file;
	target_file = fopen(target_path, "w");
	char buffer[MAX_LINE];
	while (fgets(buffer, MAX_LINE, source_file) != NULL)
	{
		fwrite(buffer, strlen(buffer), 1, target_file); 
		break;
	}
	if (rename(source_path, target_path) != 0)
	{
		printf("Error: cannot rename file %s to %s\n", source_path, target_path);
        	fclose(source_file);
        	return -1;
	}
	printf("File moved successfully.\n");
	fclose(source_file);	
	return 0;
}
int envir()
{
	extern char ** environ;
	int i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return 0;
}

char* type(char* cmd)
{
	char* path_env = getenv("PATH");
	static const char* internal_commands[] = {"mycd", "mypwd", "myecho", "myexit", "myhelp", "myenv", "mycp", "mymv"};
	for (int i = 0; i < sizeof(internal_commands) / sizeof(internal_commands[0]); i++)
	{
		if (strcmp(cmd, internal_commands[i]) == 0)
		{
			return "internal";
		}
		break;
	}
	if (access(path_env, F_OK) != -1 && strcmp(path_env, "") != 0)
	{
	struct stat *sb;
	if (stat(path_env, &sb) == 0 && S_ISREG(sb->st_mode))
	{return "Unsupported: command not found in PATH\n";}
	}
	else
	{return "external";}

    return "";
}

void execute_external_command(char* cmd)
{
	pid_t pid;
	char* args[1024];
	// Split the command into an array of strings
	char* command = strtok(cmd, " ");
	char* arguments = strtok(NULL, " ");
	char* new_args[] = {command, arguments, NULL};
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{	// Child process
		execvp("sh", new_args);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
		// Parent process
		{wait(NULL);}
}

void free_command()
{
	struct sysinfo info;
	sysinfo(&info);
	// Print RAM info
	printf("RAM:\n");
	printf("  Total: %lu bytes\n", info.totalram);
	printf("  Used: %lu bytes\n", info.totalram - info.freeram);
	printf("  Free: %lu bytes\n", info.freeram);
	// Print Swap area info
	printf("Swap:\n");
	printf("  Total: %lu bytes\n", info.totalswap);
	printf("  Used: %lu bytes\n", info.totalswap - info.freeswap);
	printf("  Free: %lu bytes\n", info.freeswap);
}

int uptime_command()
{
	int fd = open("/proc/uptime", O_RDONLY);	// Open the "/proc/uptime" file in read-only mode (O_RDONLY)
	if (fd == -1)
	{
		perror("open");				// If the file cannot be opened, print an error message using perror()
		return 0;
	}

	char buffer[1024];				// Allocate a buffer of size 1024 bytes to store the contents of the file
	read(fd, buffer, 1024);				// Read the contents of the file into the buffer
	close(fd);
	double uptime, idle_time;			// Declare two double variables to hold the uptime and idle time values
	sscanf(buffer, "%lf %lf", &uptime, &idle_time);	// Use sscanf() to parse the buffer and extract the uptime and idle time values

	int days = (int) uptime / 86400;		// Calculate the number of days from the uptime value
	int hours = (((int)uptime) % 86400) / 3600;	// Calculate the number of hours from the remaining uptime value (after subtracting days)
	int minutes = (((int)uptime) % 3600) / 60;	// Calculate the number of minutes from the remaining uptime value (after subtracting hours)
	int seconds = (int) uptime % 60;		// Calculate the number of seconds from the remaining uptime value (after subtracting minutes)

	sprintf(buffer, "Uptime: %d days, %d hours, %d minutes, %d seconds\n", days, hours, minutes, seconds);
	write(STDOUT, buffer, strlen(buffer));		// Write the formatted string to the standard output  (STDOUT)

	sprintf(buffer, "Idle time:  %d seconds\n",(int) idle_time);
	write(STDOUT, buffer, strlen(buffer));
}

void redirect_io(char *cmd, char *infile, char *outfile, char *errfile)
{
	int fd_in, fd_out, fd_err;
	// Open the input file
	if (infile)
	{
		fd_in = open(infile, O_RDONLY);
		if (fd_in < 0)
		{
			perror("open");
			return;
		}
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	// Open the output file
	if (outfile)
	{
		fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			perror("open");
			return;
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	// Open the error file
	if (errfile)
	{
		fd_err = open(errfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_err < 0)
		{
			perror("open");
			return;
		}
		dup2(fd_err, STDERR_FILENO);
		close(fd_err);
	}
	char *argv[] = {cmd, NULL};
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
		{execvp(cmd, argv);}	// child process
	else
		{wait(NULL);}	// parent process
}

void pipe_commands(char *cmd1, char *cmd2)
{
	int pipefd[2];
	pid_t pid;
	// Create a pipe
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	// Create a child process
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)	// Child process
	{
		close(pipefd[1]);	// Close the write end of the pipe
		dup2(pipefd[0], 0);	// Make the read end of the pipe the standard input
		close(pipefd[0]);	// Close the read end of the pipe
		redirect_io(cmd2, NULL, "output.txt", NULL);	// Redirect the output of the second command
		char *args[] = {"sh", "-c", cmd2, NULL};	// Define the arguments for the second command
		execvp("sh", args);	// Execute the second command in the pipeline using execvp
	}
	else	// Parent process
	{
		close(pipefd[0]);	// Close the read end of the pipe
		dup2(pipefd[1], 1);	// Make the write end of the pipe the standard output
		close(pipefd[1]);	// Close the write end of the pipe
		redirect_io(cmd1, "input.txt", NULL, NULL);	// Redirect the input of the first command
		char *args[] = {"sh", "-c", cmd1, NULL};	// Define the arguments for the first command
		execvp("sh", args);	// Execute the first command in the pipeline using execvp
	}
}





