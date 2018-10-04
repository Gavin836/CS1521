// COMP1521 18s2 mysh ... command history
// Implements an abstract data object

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

   struct _history_list = malloc(sizeof( struct _history_list));

   FILE *fp;
   fp = fopen(HISTFILE, 'a');
  
   while (ch = fgetc(fp) != NULL) {
      if (ch = '\n') {
         line_no++;
      }
   }

   if (line_no == 0) {

   } else {
      
   }
   fclose(fp);

}

// addToCommandHistory()
// - add a command line to the history list
// - overwrite oldest entry if buffer is full

void addToCommandHistory(char *cmdLine, int seqNo)
{

   // TODO
   int start_read = 0;
	FILE *fp;
	fp = fopen("HISTFILE", 'a');

	//int lines = 0;
//	
//   while(!feof(fp))
//	{
//	  ch = fgetc(fp);
//	  if(ch == '\n')
//	  {
//	    lines++;
//	  }
//	}
   char history_str[MAXSTR];
   sprintf(history_str,"  %d  %s", seqNo, cmdLine)
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
