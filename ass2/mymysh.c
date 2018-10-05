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

// This is defined in string.h
// BUT ONLY if you use -std=gnu99
//extern char *strdup(char *);

// Global Constants

#define MAXLINE 200
#define TRUE 0
#define FALSE 1

// Global Data

/* none ... unless you want some */


// Function forward references
int execute(char **args, char **path, char **envp);
int is_shell (char *command);
int execute_s (char** command);
void cd_path(char **command, char *path);
void prod_cmdLine(char **command, char cmdLine[MAXLINE]);


void trim(char *);
int strContains(char *, char *);
char **tokenise(char *, char *);
char **fileNameExpand(char **);
void freeTokens(char **);
char *findExecutable(char *, char **);
int isExecutable(char *);
void prompt(void);





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

    cmdNo = initCommandHistory();
    assert(cmdNo >= 0);
    // main loop: print prompt, read line, execute command

    prompt();
    char line[MAXLINE];
    int ret;
    char cd_buff[MAXLINE];
    char cmdLine[MAXLINE];

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
        prod_cmdLine(command, cmdLine);

        if (strcmp(command[0], "exit") == 0){
        	break;
        
        } else if (strcmp(command[0], "cd") == 0) {
            cd_path(command, cd_buff);
            //printf("New buf is %s",cd_buff);
            ret = chdir(cd_buff);

            if (ret == FALSE) {
                printf("Directory not found");
            }

        } else if ((strcmp(command[0], "h") == 0) || 
                   (strcmp(command[0], "history") == 0)) {

            showCommandHistory(stdout);
    
        } else if (strcmp(command[0], "pwd") == 0){     
            getcwd(cd_buff, MAXLINE*sizeof(char));
            printf("%s\n", cd_buff);

            addToCommandHistory(cmdLine, cmdNo);
            cmdNo++;

        } else if (command != NULL) { 		
	        pid = fork();

	       	//Child process executes command,
	        if ( pid == 0 ) {
        		
                ret = execute(command, path, envp);
	            
                if (ret != FALSE) {
                    printf("TODO add to history\n");
                    cmdNo++;
                    //addToCommandHistory(line, cmdNo);
            	
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

void cd_path(char **command, char cd_path[]){

    getcwd(cd_path, MAXLINE*sizeof(char));

    strcat(cd_path, "/");
    strcat(cd_path, command[1]);   
    strcat(cd_path, "/");

}

void prod_cmdLine(char **command, char cmdLine[MAXLINE]){
    int i = 0;

    for( i = 0; command[i] != NULL; i++){
        if (i != 0){
            strcat(cmdLine," ");
            strcat(cmdLine, command[i]);
        
        } else {
            strcat(cmdLine, command[i]);
        }
    }

}

int execute_s(char **command) {
	char path[MAXLINE] = {0};
	getcwd(path, sizeof(path));

	if ((strcmp(command[0], "h") == 0) || 
	    (strcmp(command[0], "history") == 0)) {
		
		printf("HISTORY");
	
	} else if (strcmp(command[0], "pwd") == 0){		
		printf("%s\n", path);

	} 

	return TRUE;
}

int execute(char **args, char **path, char **envp)
{

    char *command = 0;
    command = findExecutable(args[0], path);

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

	return status;
}
// prompt: print a shell prompt
// done as a function to allow switching to $PS1
void prompt(void)
{
    printf("mymysh$ ");
}
