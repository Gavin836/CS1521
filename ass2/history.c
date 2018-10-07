// COMP1521 18s2 mysh ... command history
// Implements an abstract data object

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "history.h"

// This is defined in string.h
// BUT ONLY if you use -std=gnu99
//extern char *strdup(const char *s);

// Command History
// array of command lines
// each is associated with a sequence number

#define MAXHIST 20
#define MAXSTR  200

#define HISTFILE ".mymysh_history"

typedef struct _history_entry {
    int    seqNumber;
    char *commandLine;
} HistoryEntry;

typedef struct _history_list {
    int nEntries;
    HistoryEntry commands[MAXHIST];
} HistoryList;

HistoryList CommandHistory;

// initCommandHistory()
// - initialise the data structure
// - read from .history if it exists

int initCommandHistory()
{

    // TODO
    char ch;
    int line_no; 

    FILE *fp;
    fp = fopen(HISTFILE, "r");
  
    if (fp == NULL){
        fp = fopen(HISTFILE, "a");
    }    

    //Count number of commands based on \n char  
    while((ch = fgetc(fp)) != EOF)
    {
      if (ch == '\n')
      {
         line_no++;
      }
    }
    
    char line[MAXSTR];
    int cmdNo = 0;
    char cmdLine[MAXSTR];
    
    int i = 0;
    // Load into memory the required strings from HISTFILE 
    fseek(fp, 0, SEEK_SET);
    
    if (line_no > 0){

        while(fgets(line, MAXSTR, fp)){
            sscanf(line,"  %3d  %[^\n]\n", &cmdNo, cmdLine);
            assert(cmdNo > 0 && strlen(line) != 0);
            printf("cmdNo: %d, line: %s\n", cmdNo, cmdLine);
            
            CommandHistory.commands[i].seqNumber = i;
            CommandHistory.commands[i].commandLine = strdup(cmdLine);
            //printf("success == %s\n", CommandHistory.commands[i].commandLine);        
            i++;
        }
    }
        CommandHistory.nEntries = i;

    fclose(fp);
    return CommandHistory.nEntries;
}

// addToCommandHistory()
// - add a command line to the history list
// - overwrite oldest entry if buffer is full

void addToCommandHistory(char *cmdLine, int seqNo)
{
 
    // TODO  
    int curr_entries = CommandHistory.nEntries;

    // Add command into the command struct. Overwrite our records necessary
    if ( curr_entries < 20 ) {
        
        CommandHistory.commands[curr_entries].seqNumber = seqNo;
        CommandHistory.commands[curr_entries].commandLine =  strdup(cmdLine); 
        //printf("no: %d, line: %s", CommandHistory.commands[curr_entries].seqNumber, CommandHistory.commands[curr_entries].commandLine);

    }  else {
        int small_index = get_small();
        free(CommandHistory.commands[small_index].commandLine);
        
        CommandHistory.commands[small_index].seqNumber = seqNo;
        CommandHistory.commands[small_index].commandLine =  strdup(cmdLine);
    }
    
    CommandHistory.nEntries++;
}


// showCommandHistory()
// - display the list of 

void showCommandHistory(FILE *outf)
{
    // TODO
    int small_index = get_small();
    int no_entries = CommandHistory.nEntries;
    int i = 0;
    
    //printf("no_entries: %d and small_index: %d", no_entries, small_index);
    
    while (small_index < no_entries){

        fprintf(outf,"  %d  %s\n",CommandHistory.commands[small_index].seqNumber + 1,
                                  CommandHistory.commands[small_index].commandLine);
        small_index++;
    }
     
    if (get_small() > 0){ 
        if (CommandHistory.nEntries > 20) {
            i = CommandHistory.nEntries - 20;
        }
        
        while (i < small_index){

             fprintf(outf,"  %d  %s\n",CommandHistory.commands[i].seqNumber + 1,
                                       CommandHistory.commands[i].commandLine);
            i++;
        }
    }
}

// getCommandFromHistory()
// - get the command line for specified command
// - returns NULL if no command with this number

char *getCommandFromHistory(int cmdNo)
{
    // TODO
    int i = 0;
    
    while (i < MAXHIST && CommandHistory.commands[i].seqNumber != cmdNo) {
        i++;
    }
    
    if (i == MAXHIST) {
        printf("Command number is not found\n");
        return 0;
    }
    
    //printf("use %d for cmdNo: %d", i, cmdNo);
    return CommandHistory.commands[i].commandLine;
}

// saveCommandHistory()
// - write history to $HOME/.mymysh_history

void saveCommandHistory()
{
    FILE *fp;
    fp = fopen(HISTFILE, "w+");
    
    int small_index = get_small();
    int i = 0;
    
    while (small_index < CommandHistory.nEntries){

        fprintf(fp, "  %d  %s\n", CommandHistory.commands[small_index].seqNumber + 1,     
                                CommandHistory.commands[small_index].commandLine);
        
        free(CommandHistory.commands[small_index].commandLine);
        small_index++;
    }
     
    if (get_small() > 0){     
        while (i < small_index){
             
            fprintf(fp, "  %d  %s", CommandHistory.commands[i].seqNumber + 1,     
                                    CommandHistory.commands[i].commandLine);
            
            free(CommandHistory.commands[i].commandLine);
            i++;
        }
    }
}

// cleanCommandHistory
// - release all data allocated to command history

void cleanCommandHistory()
{
    // TODO
}

int get_small(){
    int i;
    int no_entries = CommandHistory.nEntries;
    int small_index = 0;
    
    if (no_entries > 0){ 
        for (i = 0; i < no_entries; i++){
            
            if (CommandHistory.commands[i].seqNumber < 
                 CommandHistory.commands[small_index].seqNumber){

                small_index = i;
            }
        }
    }

    return small_index;
}
