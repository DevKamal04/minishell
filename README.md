
# Project Title

A brief description of what this project does and who it's for


Minishell is a simple shell program inspired by Bash. It includes several important features, which are summarized below:

Main Features of Minishell

Prompt Display: Shows a prompt where you can type commands.

Command History: Use the up and down arrow keys to scroll through previously entered commands.

Running Commands:

System Commands: Run built-in system commands like ls, cat, grep, etc.

Local Commands: Run local executables with ./minishell.

Builtin Commands:

echo (with -n option)

cd (for changing directories)

pwd (print current directory)

export, unset, env (manage environment variables)

exit (exit with a status code)

Pipes: Use | to pass the output of one command as input to another.

Redirections:

>: Redirect output to a file.

>>: Append output to a file.

<: Redirect input from a file.

Environment Variables: Use variables like $USER and $? to get information from the environment.

Keyboard Signals:

ctrl-c: Interrupt the current command and show a new prompt.

ctrl-d: Exit the shell.

ctrl-\: Does nothing.

Minishell does not support:

Escape character \

Command separator ;

Logical operators && and ||

Wildcards like *

Key Concepts

Creating and Killing Child Processes in C:

Creating: Use fork() to create child processes.

Waiting: Use wait() or waitpid() to wait for child processes to finish.

Killing: Use signals like SIGTERM (which can be handled) and SIGKILL (which forcefully terminates the process) to terminate child processes​ (codequoi)​​ (Delft Stack)​.

Pipes: Allow commands to pass their output to the next command in the pipeline.

Signals: Used for inter-process communication. You can set up handlers for signals like SIGINT (interrupt) and SIGTERM (termination).

File Descriptors: Manage input and output using system calls like open(), read(), write(), and close().
