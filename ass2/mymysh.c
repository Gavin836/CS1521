// mysh.c ... a small shell
// Started by John Shepherd, September 2018
// Completed by <<Gavin>>, September/October 2018

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <glob.h>
#include <assert.h>
#include <fcntl.h>
#include "history.h"

#define TRUE 1
#define FALSE 2

// This is defined in string.h
// BUT ONLY if you use -std=gnu99
//extern char *strdup(char *);

// Function forward references
int execute(char **args, char **path, char **envp);
int is_shell (char *command);
int execute_s (char** command);

void trim(char *);
int strContains(char *, char *);
char **tokenise(char *, char *);
char **fileNameExpand(char **);
void freeTokens(char **);
char *findExecutable(char *, char **);
int isExecutable(char *);
void prompt(void);



// Global Constants

#define MAXLINE 200

// Global Data

/* none ... unless you want some */


// Main program
// Set up enviroment and then run main loop
// - read command, execute command, repeat

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;    // pid of child process
    int stat = 0;     // return status of child
    char **path; // array of directory names
    int cmdNo = 0;    // command number
    int i;         // generic index

    // set up command PATH from environment variable
    for (i = 0; envp[i] != NULL; i++) {
        if (strncmp(envp[i], "PATH=", 5) == 0) break;
    }
    if (envp[i] == NULL)
        path = tokenise("/bin:/usr/bin",":");
    else
        // &envp[i][5] skips over "PATH=" prefix
        path = tokenise(&envp[i][5],":");
#ifdef DBUG
    for (i = 0; path[i] != NULL;i++)
        printf("path[%d] = %s\n",i,path[i]);
#endif

    // initialise command history
    // - use content of ~/.mymysh_history file if it exists

    //cmdNo = initCommandHistory();

    // main loop: print prompt, read line, execute command

    char line[MAXLINE];
    prompt();
    int success;

    while (fgets(line, MAXLINE, stdin) != NULL) {
        trim(line); // remove leading/trailing space

        // TODO
        // Code to implement mainloop goes here
        // Uses
        // - addToCommandHistory()
        // - showCommandHistory()
        // - and many other functions
        // TODO

		char **command; 
        command = tokenise(line, " ");

        if (strcmp(command[0], "exit") == 0){
        	break;
        
        } else if (command != NULL) { 		
	        pid = fork();

	       	//Child process executes command,
	        if ( pid == 0 ) {
	        	
	        	if (is_shell(command[0]) == TRUE) {
	        		execute_s(command);	
	        	
	        	} else {
	        		success = execute(command, path, envp);
	        	}
	        	
	        	if (success != FALSE) {
	        		printf("TODO add to history\n");
	        		cmdNo++;
	        		addToCommandHistory(line, cmdNo);
	        	} 

	        	return stat;
	        
	        // Parent process resets.
	        } else {
	        	wait(NULL);
	        	freeTokens(command);
	        	
	        }	
	    }

        prompt();
    }
    //saveCommandHistory();
    //cleanCommandHistory();
    printf("\n");
    return(EXIT_SUCCESS);
}
int execute_s(char **command) {
	char path[MAXLINE];
	getcwd(path, MAXLINE);
	//int ret;

	if ((strcmp(command[0], "h") == 0) || 
	    (strcmp(command[0], "history") == 0)) {
		
		printf("HISTORY");
	
	} else if (strcmp(command[0], "pwd") == 0){		
		printf("%s\n", path);

	} else if (strcmp(command[0], "cd") == 0){
		
		if (strcmp(command[1], "..") == 0) {
			char **sep_path = tokenise(path,"/");
			int i = 0;
			char * s = path;
			int len = 0;

			while (s[i] != '\0') {
				
				if (s[i] == '/'){
					len++;
				}
				i++;
			}
			
			memset(path, 0, MAXLINE);
			printf("path: %s", path);
			for (i = 0; i < len - 1; i++) {
				strcat(path, "/");
				strcat(path, sep_path[i]);
			}

		} else {
			strcat(path, "/");
			strcat(path, command[1]);	
		}

		strcat(path, "/");
		printf ("changing to %s\n", path);
		chdir(path);

		/*if (ret) {
			printf("Directory not found");
			return FALSE;
		}
		*/
	} else {
		printf("broken execute_s\n");
	}

	return TRUE;
}

int execute(char **args, char **path, char **envp)
{

    char *command = 0;
    command = findExecutable(args[0], path);
    printf("Inside execute\n");
    if (command == NULL) {
        printf("Command not found\n");
  
    } else {
    	printf("Running %s ...\n", command);
        execve(command, args, envp);
        
        perror("Exec failed\n");
    }

	return FALSE;       
}

// fileNameExpand: expand any wildcards in command-line args
// - returns a possibly larger set of tokens
char **fileNameExpand(char **tokens)
{
    // TODO
    return 0;
}

// findExecutable: look for executable in PATH
char *findExecutable(char *cmd, char **path)
{
        char executable[MAXLINE];
        executable[0] = '\0';
        if (cmd[0] == '/' || cmd[0] == '.') {
            strcpy(executable, cmd);
            if (!isExecutable(executable))
                executable[0] = '\0';
        }
        else {
            int i;
            for (i = 0; path[i] != NULL; i++) {
                sprintf(executable, "%s/%s", path[i], cmd);
                if (isExecutable(executable)) break;
            }
            if (path[i] == NULL) executable[0] = '\0';
        }
        if (executable[0] == '\0')
            return NULL;
        else
            return strdup(executable);
}

// isExecutable: check whether this process can execute a file
int isExecutable(char *cmd)
{
    struct stat s;
    // must be accessible
    if (stat(cmd, &s) < 0)
        return 0;
    // must be a regular file
    //if (!(s.st_mode & S_IFREG))
    if (!S_ISREG(s.st_mode))
        return 0;
    // if it's owner executable by us, ok
    if (s.st_uid == getuid() && s.st_mode & S_IXUSR)
        return 1;
    // if it's group executable by us, ok
    if (s.st_gid == getgid() && s.st_mode & S_IXGRP)
        return 1;
    // if it's other executable by us, ok
    if (s.st_mode & S_IXOTH)
        return 1;
    return 0;
}

// tokenise: split a string around a set of separators
// create an array of separate strings
// final array element contains NULL
char **tokenise(char *str, char *sep)
{
    // temp copy of string, because strtok() mangles it
    char *tmp;
    // count tokens
    tmp = strdup(str);
    int n = 0;
    strtok(tmp, sep); n++;
    while (strtok(NULL, sep) != NULL) n++;
    free(tmp);
    // allocate array for argv strings
    char **strings = malloc((n+1)*sizeof(char *));
    assert(strings != NULL);
    // now tokenise and fill array
    tmp = strdup(str);
    char *next; int i = 0;
    next = strtok(tmp, sep);
    strings[i++] = strdup(next);
    while ((next = strtok(NULL,sep)) != NULL)
        strings[i++] = strdup(next);
    strings[i] = NULL;
    free(tmp);
    return strings;
}

// freeTokens: free memory associated with array of tokens
void freeTokens(char **toks)
{
    for (int i = 0; toks[i] != NULL; i++)
        free(toks[i]);
    free(toks);
}

// trim: remove leading/trailing spaces from a string
void trim(char *str)
{
    int first, last;
    first = 0;
    while (isspace(str[first])) first++;
    last  = strlen(str)-1;
    while (isspace(str[last])) last--;
    int i, j = 0;
    for (i = first; i <= last; i++) str[j++] = str[i];
    str[j] = '\0';
}

// strContains: does the first string contain any char from 2nd string?
int strContains(char *str, char *chars)
{
    for (char *s = str; *s != '\0'; s++) {
        for (char *c = chars; *c != '\0'; c++) {
            if (*s == *c) return 1;
        }
    }
    return 0;
}

int is_shell (char *command) {
	int status = FALSE;

	if (strcmp(command, "exit") == 0) {
		status = TRUE;
	
	} else if (strcmp(command, "h") == 0){
		status = TRUE;
	
	} else if (strcmp(command, "history") == 0){
		status = TRUE;
	
	} else if (strcmp(command, "pwd") == 0){
		status = TRUE;
	
	} else if (strcmp(command, "cd") == 0){
		status = TRUE;
	}

	printf("status is %d\n", status);

	return status;
}
// prompt: print a shell prompt
// done as a function to allow switching to $PS1
void prompt(void)
{
    printf("mymysh$ ");
}
