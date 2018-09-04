#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#define MAX_LINE		80 /* 80 chars per line, per command */
#define MAX_HISTORY     10

int id=0;
int counter=0;

struct{
    int id;
    char line[81];
} typedef historyItem;

historyItem historyQueue[MAX_HISTORY];

void shiftArray() {
    int i;
    for(i=0; i < MAX_HISTORY-1; i++) {
        historyQueue[i] = historyQueue[i+1];
    }
}

void appendHistory(char* line) {
    shiftArray();
    historyQueue[MAX_HISTORY-1].id++;
    strcpy(historyQueue[MAX_HISTORY-1].line, line);
    counter ++;
}

void showHistory() {
    historyItem aux;
    int i;
    for(i=0; i<MAX_HISTORY; i++){
        aux = historyQueue[i];
        printf("%d.-%s \n", aux.id, aux.line);
    }
}

historyItem getHistory(int index) {
    historyItem aux;
    aux = historyQueue[index];
    return aux;
}

int parse_index(char *line){
    if (line[0] == '!' && line[1] != '\0'){
        if(isdigit(line[1])){
            return atoi(& line[1]);
        }
    }
    return -1;
}

//spliting the args on args array.
int parse_command(char line[], char * args[]) {
    char * token = strtok(line, " \t");
    int count = 0;
    while (token != NULL && strlen(token) > 0) {
        args[count++] = token;
        token = strtok(NULL, " \t");
  }
    args[count] = NULL;
    return count;
}

int main(void)
{
    char copy_line[MAX_LINE+1];
	char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
    historyItem aux;
    char line[MAX_LINE+1];
    int background;
    int should_run = 1;
    int arg_count;
    int child;
    char * token;
		
    while (should_run) { 
        printf("osh> ");
        fflush(stdout);
        // get input and ask for another line if input == NULL
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        // delete jump of line
        if ((token = strchr(line, '\n')) != NULL) {
            *token = '\0';
        }
        // exit if requested.
        if (strcmp(line, "exit") == 0) {
            exit(errno);
        }
        arg_count = parse_command(line, args);
        //skip if empty
        if (arg_count == 0){
            continue;
        }
        if (strcmp(args[0], "!!") == 0) {
            int x;
            historyItem aux;
            if(counter == 0)
                printf("No commands in history. \n");
                continue;
            for(x=0; x < MAX_HISTORY;x++){
                aux = historyQueue[x];
                if(counter == aux.id) {
                    arg_count = parse_command(aux.line, args);
                    break;
                }
            }
        }
        if(args[0][0] == '!'){
            if(args[0][1] == '0'){
                printf("No such command in history.\n");
                continue;
            }
            int index = parse_index(args[0]);
                if(index<0){
                    printf("No such command in history.\n");
                    continue;
                }
                int x;
                for(x=0; x < MAX_HISTORY;x++) {
                    aux = historyQueue[x];
                    if(index == aux.id) {
                        arg_count = parse_command(aux.line, args);
                        break;
                    }
                }    
        }
        strcpy(copy_line, line);
        if (strcmp(line, "history") == 0) {
            showHistory();
            continue;
        }
        appendHistory(copy_line);
        //run on background if & at the end
        if (strcmp(args[arg_count - 1], "&") == 0) {
            background = 1;
            args[arg_count - 1] = NULL;
        }
        child = fork();
        
        // failed to create child
        if (child < 0) {
            printf("Could't create process.\n");
        }
       // The father waits for the child 
        if (child > 0) {
            if (!background) {
                waitpid(child, NULL, 0);
            }
        } else {
            // the child executes the cmd.
            if (execvp(args[0], args) < 0) {
                exit(errno);
            }
        }
    }
	return 0;
}
