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
    char ch;
    int line_no = 0; 

    //Open file. Create if necessary
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
        //Extract command number and line
        while(fgets(line, MAXSTR, fp)){
            sscanf(line,"  %d  %[^\n]\n", &cmdNo, cmdLine);
            assert(cmdNo >= 0 && strlen(line) != 0);
            //printf("cmdNo: %d, line: %s\n", cmdNo, cmdLine);
            
            CommandHistory.commands[i].seqNumber = i;
            CommandHistory.commands[i].commandLine = strdup(cmdLine);
            //printf("success == %d\n", CommandHistory.commands[i].seqNumber);        
            i++;
        }
    }

    CommandHistory.nEntries = i;
    fclose(fp);

    return CommandHistory.nEntries;
    
    return 0;
}

// addToCommandHistory()
// - add a command line to the history list
// - overwrite oldest entry if buffer is full

void addToCommandHistory(char *cmdLine, int seqNo)
{
 
    int curr_entries = CommandHistory.nEntries;

    // Add command into the command struct. Overwrite our records necessary
    if ( CommandHistory.commands[curr_entries].seqNumber < 20 ) {
        
        CommandHistory.commands[curr_entries].seqNumber = seqNo;
        CommandHistory.commands[curr_entries].commandLine =  strdup(cmdLine); 
        //printf("no: %d, line: %s", CommandHistory.commands[curr_entries].seqNumber, CommandHistory.commands[curr_entries].commandLine);

    //Overite based on oldest command
    }  else {
        int small_index = get_small();
        //printf("free %s new seq: %d\n", CommandHistory.commands[small_index].commandLine, seqNo);
        free(CommandHistory.commands[small_index].commandLine);
        
        CommandHistory.commands[small_index].seqNumber = seqNo;
        CommandHistory.commands[small_index].commandLine =  strdup(cmdLine);
    }
    
    if (CommandHistory.nEntries < MAXHIST){
        CommandHistory.nEntries++;
    }
    
}


// showCommandHistory()
// - display the list of 

void showCommandHistory(FILE *outf)
{
    int small_index = get_small();
    int no_entries = CommandHistory.nEntries;
    int i = 0;
    
    //printf("index %d, entries %d\n", small_index, no_entries);
    
    //Print out the oldest entries first. If needed, follow with new entries.
    i = small_index;
    while (i  < no_entries){
        fprintf(outf,"  %d  %s\n", CommandHistory.commands[i].seqNumber + 1,
                                  CommandHistory.commands[i].commandLine);
        i++;
    }

    i = 0;
    if (small_index  > 0){ 
        
        while (i < small_index){

             fprintf(outf,"  %d  %s\n", CommandHistory.commands[i].seqNumber + 1,
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
    int i = 0;
    
    //adjusted for index (CmdNo is 1 greater than SeqNo)
    cmdNo--;
    
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
    
    //Save memory to file. Free memory as it is saved
    while (small_index < CommandHistory.nEntries){

        fprintf(fp, "  %d  %s\n", CommandHistory.commands[small_index].seqNumber,     
                                  CommandHistory.commands[small_index].commandLine);

        free(CommandHistory.commands[small_index].commandLine);
        small_index++;
    }
     
    if (get_small() > 0){     
        while (i < small_index){            
        
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
    // Done throughout
}

//Find the index corresponding to the smallest command number
int get_small(){
    int i;
    int no_entries = CommandHistory.nEntries;
    int small_index = 0;
    
    for (i = 0; i < no_entries ; i++){
        //printf("Small~ no: %d / %d\n", CommandHistory.commands[i].seqNumber, CommandHistory.commands[small_index].seqNumber);
        if (CommandHistory.commands[i].seqNumber < 
            CommandHistory.commands[small_index].seqNumber){
            small_index = i;
            //printf("SET: %d", small_index);
            break;
        }
    }

    return small_index;
}
