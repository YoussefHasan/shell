# uShell: A Simple yet Powerful Command Line Interface

**Welcome**

to uShell, a command line interface designed to provide a user-friendly experience while executing various commands. With its wide range of features, uShell allows you to navigate through your system like never before.

**Basic Commands**

* `mypwd`: Displays the current working directory.
* `myecho`: Prints a string you type.
* `mycp`: Copies a file from source path to target path.
* `mymv`: Moves a file from source path to target path.
* `mycd`: Changes the current working directory.
* `myhelp`: Displays this help message.
* `uptime`: Displays the system uptime and idle time.
* `free`: Displays RAM and Swap area information.
* `myenv`: Prints all environment variables.

**External Commands**

* Execute any external command using internal process.
* Pipe between two processes for complex workflows. (Pipe is ont working properly for the moment but it will be updated shortly to be effeccient)

**Redirecting Input/Output/Error Streams**

* Use `myredirect` with `<`, `>`, or `2>` operators to redirect input/output/error streams.
* `<` for input redirection.
* `>` for output redirection.
* `2>` for eror redirection.

**Using uShell**

* Enter a command and press  Enter to execute it.
* Use the following syntax for commands that take arguments:
	+ `myecho YOUR_TEXT`.
	+ `mycp SOURCE_PATH DIRECTORY_PATH`.
	+ `mymv SOURCE_PATH DIRECTORY_PATH`.
	+ `mytype COMMAND`.
	+ `mycd DIRECTORY_PATH`.
	+ `myredirect: COMMAND_1 (<, >, 2>) COMMAND_2`.

**Exiting the Internal Session**

* Use `$exit` to close the internal session when executing external commands.

**Troubleshooting**

If you encounter any issues or errors, please don't hesitate to contact us. We're always here to help.

**Credits**

The uShell project was created be a simple yet powerful CLI for all users. Special thanks to my mentors at STMicroelectronics

**Getting Started**

1. build the files attached by this command: `gcc -static *.c -o uShell.exe`, then run the .exe.
2. Explore the various commands and features offered by uShell.
3. Don't hesitate to contact us if you have any questions or need assistance.

Thank you for choosing uShell ya 3m el kawkab!
