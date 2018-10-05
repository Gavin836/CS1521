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
   int   seqNumber;
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
     if(ch == '\n')
     {
       line_no++;
     }
   }
   
   char line[MAXSTR];
   int cmdNo;
   
   int i = 0;
   int j = 0;

   // Load into memory the required increments from HISTFILE 
   fseek(fp, 0, SEEK_SET);
   if (line_no > 20) {
     
      while(fgets(line, MAXSTR, fp)){
         
         if (i >= line_no - MAXHIST){
            sscanf(line,"  %3d  %s\n", &cmdNo, line);
            
            CommandHistory.nEntries++;
            CommandHistory.commands[j].seqNumber = cmdNo;
            CommandHistory.commands[j].commandLine = line;
            j++;
         }
         
         i++;
      }

   } else if (line_no > 0){

      while(fgets(line, MAXSTR, fp)){
         sscanf(line,"  %3d  %s\n", &cmdNo, line);
         
         CommandHistory.nEntries++;
         CommandHistory.commands[i].seqNumber = cmdNo;
         CommandHistory.commands[i].commandLine = line;
         i++;
      }
   }

   fclose(fp);
   return CommandHistory.commands[CommandHistory.nEntries].seqNumber;
}

// addToCommandHistory()
// - add a command line to the history list
// - overwrite oldest entry if buffer is full

void addToCommandHistory(char *cmdLine, int seqNo)
{

   // TODO
	FILE *fp;
	fp = fopen("HISTFILE", "a");
/*
	lines = 0;
	
   while(!feof(fp))
	{
	  ch = fgetc(fp);
	  if(ch == '\n')
	  {
	    lines++;
	  }
	}
*/

   char history_str[MAXSTR];
   sprintf(history_str,"  %d  %s", seqNo, cmdLine);
   fseek(fp,0,SEEK_END);
   fputs(history_str,fp);
	fclose(fp);
}


// showCommandHistory()
// - display the list of 

void showCommandHistory(FILE *outf)
{
   // TODO

}

// getCommandFromHistory()
// - get the command line for specified command
// - returns NULL if no command with this number

char *getCommandFromHistory(int cmdNo)
{
   // TODO

   return 0;
}

// saveCommandHistory()
// - write history to $HOME/.mymysh_history

void saveCommandHistory()
{
   // TODO
}

// cleanCommandHistory
// - release all data allocated to command history

void cleanCommandHistory()
{
   // TODO
}
