This project consists of designing a C program to serve as a shell interface
that accepts user commands and then executes each command in a separate
process. This project can be completed on any Linux, UNIX, or Mac OS X system.
A shell interface gives the user a prompt, after which the next command
is entered.

##TEMPLATE

#include <stdio.h>
#include <unistd.h>
#define MAX LINE 80 /* The maximum length command */
int main(void)
{
char *args[MAX LINE/2 + 1]; /* command line arguments */
int should run = 1; /* flag to determine when to exit program */
while (should run) {
printf("osh>");
fflush(stdout);
/**
* After reading user input, the steps are:
* (1) fork a child process using fork()
* (2) the child process will invoke execvp()
* (3) if command included &, parent will invoke wait()
*/
}
return 0;
}


# Part I— Creating a Child Process
The first task is to modify the main() function in Figure 3.36 so that a child
process is forked and executes the command specified by the user. This will
require parsing what the user has entered into separate tokens and storing the
tokens in an array of character strings (args in Figure 3.36). For example, if the
user enters the command ps -ael at the osh> prompt, the values stored in the
args array are:
args[0] = "ps"
args[1] = "-ael"
args[2] = NULL

This args array will be passed to the execvp() function, which has the
following prototype:
execvp(char *command, char *params[]);


#Part II—Creating a History Feature
The next task is to modify the shell interface program so that it provides
a history feature that allows the user to access the most recently entered
commands. The user will be able to access up to 10 commands by using the
feature. The commands will be consecutively numbered starting at 1, and
the numbering will continue past 10. For example, if the user has entered 35
commands, the 10 most recent commands will be numbered 26 to 35.
The user will be able to list the command history by entering the command
history
at the osh> prompt. As an example, assume that the history consists of the
commands (from most to least recent):
ps, ls -l, top, cal, who, date
The command history will output:
6 ps
5 ls -l
4 top
3 cal
2 who
1 date


# HOW TO RUN

Just compile dshell.c with gcc and execute the output.
