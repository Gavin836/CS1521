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
void cd_path(char **command, char *path);
void prod_cmdLine(char **command, char cmdLine[MAXLINE]);
void p_brace();



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
    int child_stat;     // return status of child
    char **path; // array of directory names
    int cmdNo;    // command number
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
    char cd_buff[MAXLINE];
    char cmdLine[MAXLINE];
    
    int ret;
    int skip = FALSE;
    
    char *redir_input;
    char *redir_command;
    char **temp;
    FILE *fp;
    while (fgets(line, MAXLINE, stdin) != NULL) {
       // Deal with empty strings.

        trim(line); // remove leading/trailing space
        char **command; 

        //Skip the loop if command is empty
        if (strcmp(line, "") == 0){
            skip = TRUE;

        } else {
            command = tokenise(line, " ");
        }

        //Deal with sequence commands
        if (command[0][0] == '!' && skip == FALSE) {
            int use_no;
            char *use_line;
            
            if (strcmp(command[0], "!!") == 0) {
                use_no = cmdNo;
                         
            } else {
                sscanf(command[0], "!%d", &use_no);
            }            
           
            use_line = getCommandFromHistory(use_no);          
            
            if (use_line == NULL) {
                skip = TRUE;
            
            } else {
                freeTokens(command);
                command = tokenise(use_line, " ");
            }
        }
        
        //convert **char into a string
        prod_cmdLine(command, cmdLine);
        
        // Wildcard expansions        
        command = fileNameExpand(command);
        
        // Determine which command to run.
        if (skip == FALSE) {
        
            if (strcmp(command[0], "exit") == 0){
            	break;
            
            } else if (strcmp(command[0], "cd") == 0) {
                cd_path(command, cd_buff);
                //printf("New buf is %s",cd_buff);
                ret = chdir(cd_buff);
                
                if (ret != FALSE) {
                    //printf("add %d with line %s\n", cmdNo, line);
                    addToCommandHistory(cmdLine, cmdNo);
                    cmdNo++;
                }
                 else {
                    printf("Directory not found");

                }
                
                
            } else if ((strcmp(command[0], "h") == 0) || 
                       (strcmp(command[0], "history") == 0)) {
                
                //Print a line of "---------"
                p_brace();        
                showCommandHistory(stdout);
                addToCommandHistory(cmdLine, cmdNo);
                
                cmdNo++;
                p_brace();
        
            } else if (strcmp(command[0], "pwd") == 0){     
                getcwd(cd_buff, MAXLINE*sizeof(char));
                printf("%s\n", cd_buff);

                addToCommandHistory(cmdLine, cmdNo);
                cmdNo++;
            
            } else if (command != NULL) { 		
                pid = fork();

               	//Child process executes command,
               	child_stat = TRUE;
                
                if ( pid == 0 ) {
                    //Redirect input
                    if (strContains(cmdLine, "<")) {
                        temp = tokenise(line,"<");
                        redir_command = strdup(temp[0]);
                        redir_input = strdup(temp[1]);
                        
                        // Open input command and write to it
                        //printf("redir %s < %s ", redir_command, redir_input);
                        
                        fp = popen(redir_command, "w");
                        assert(fp != NULL);
                        //if (fp == -1) {
                          //  printf("%s is not a valid command", redir_command);
                        //}

                        while(fputs(redir_input, fp) != EOF) {                
                        }
                        
                        pclose(fp);
                        free(redir_input);
                        free(redir_command);
                        freeTokens(temp);
                        
                    
                    //Redirect output
                    } else if (strContains(cmdLine, ">")) {
                    
                    
                    //Normal executions
                    } else {
                        execute(command, path, envp);
                        // Value set if execute fails
                        child_stat = FALSE;   	
                    }       	    
            	
            	// Parent process resets.
            	} else {
                	wait(NULL);
                	p_brace();
                	
                	if (child_stat == TRUE) {
                        addToCommandHistory(cmdLine, cmdNo);
                        cmdNo++; 	
                    } 
                    
                	freeTokens(command);	        	
                } 		        
            }
        }
        skip = FALSE;
	    prompt();
    }

    saveCommandHistory();
    cleanCommandHistory();
    printf("\n");
    
    return(EXIT_SUCCESS);
}

// Function constructs the absolute path of the required file
void cd_path(char **command, char cd_path[]){

    getcwd(cd_path, MAXLINE*sizeof(char));

    strcat(cd_path, "/");
    strcat(cd_path, command[1]);   
    strcat(cd_path, "/");

}

//Function contructs the full command as a string.
void prod_cmdLine(char **command, char cmdLine[MAXLINE]){
    int i = 0;
    //cmdLine = 0;
    memset(cmdLine, 0, MAXLINE * sizeof(char));
    
    for( i = 0; command[i] != NULL; i++){
        //printf("at %d: %s\n", i,command[i]);
        if (i != 0){
            strcat(cmdLine," ");
            strcat(cmdLine, command[i]);
        
        } else {
            strcat(cmdLine, command[i]);
        }
    }

}

int execute(char **args, char **path, char **envp)
{

    char *command = 0;
    command = findExecutable(args[0], path);

    if (command == NULL) {
        printf("Command not found\n");
  
    } else {
    	printf("Running %s ...\n", command);
        p_brace();
        execve(command, args, envp);
        
        perror("Exec failed\n");
    }

	return FALSE;       
}

// fileNameExpand: expand any wildcards in command-line args
// - returns a possibly larger set of tokens
char **fileNameExpand(char **tokens)
{
    int i = 0;
    int j = 0;
    int ret;    
    char str[MAXLINE] = {0};
    char **expanded;
    glob_t globbuf;
    
    
    //Expand the commands appropriately
    while (tokens[i] != NULL) {
        ret = glob( tokens[i], GLOB_NOCHECK|GLOB_TILDE, NULL,  &globbuf);
        
        //Append the extensions onto a buffer
        if (ret == 0) {
            while (j < globbuf.gl_pathc) {
                strcat(str, " ");
                strcat(str, globbuf.gl_pathv[j]);
                j++;
            }
                  
        } else {
            strcat(str, " ");
            strcat(str, tokens[i]);
        }
        
        j = 0;       
        i++;
    }
    //printf("STRING: %s\n", str);
    globfree(&globbuf);
    expanded = tokenise(str, " ");
    return expanded;
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

// prompt: print a shell prompt
// done as a function to allow switching to $PS1
void prompt(void)
{
    printf("mymysh$ ");
}

void p_brace (void)
{
    printf("------------------------------\n");
}


