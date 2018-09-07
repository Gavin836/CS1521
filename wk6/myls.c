// myls.c ... my very own "ls" implementation

#include <stdlib.h>
#include <stdio.h>
#include <bsd/string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define MAXDIRNAME 100
#define MAXFNAME   200
#define MAXNAME    20

char *rwxmode(mode_t, char *);
char *username(uid_t, char *);
char *groupname(gid_t, char *);

int main(int argc, char *argv[])
{
   // string buffers for various names
   char dirname[MAXDIRNAME];
   char uname[MAXNAME+1];
   char gname[MAXNAME+1];
   char mode[MAXNAME+1];

   // collect the directory name, with "." as default
   if (argc < 2)
      strlcpy(dirname, ".", MAXDIRNAME);
   else
      strlcpy(dirname, argv[1], MAXDIRNAME);

   // check that the name really is a directory
   struct stat info;
   if (stat(dirname, &info) < 0)
      { perror(argv[0]); exit(EXIT_FAILURE); }
   if ((info.st_mode & S_IFMT) != S_IFDIR)
      { fprintf(stderr, "%s: Not a directory\n",argv[0]); exit(EXIT_FAILURE); }

   // open the directory to start reading
    
   DIR *df = opendir(dirname);
   
   // ... TODO ...

   // read directory entries
   struct dirent *entry;
   char *ObjectName;
   char full_path[MAXFNAME] = {0};
   mode_t ModeInfo;
   int Size;
   uid_t OwnerUID;
   gid_t GroupGID;
   
   while ((entry = readdir(df)) != NULL) {
       strcpy(full_path, dirname);
       if (strncmp(entry->d_name, ".", 1) != 0) {
            
           ObjectName = strcat(full_path, "/");
           ObjectName = strcat(full_path, entry->d_name);
           
           lstat(ObjectName, &info);
           Size = info.st_size;
           OwnerUID = info.st_uid;
           GroupGID = info.st_gid;
           ModeInfo = info.st_mode;
           
           
           printf("%s  %-8.8s %-8.8s %8lld  %s\n",
                rwxmode(ModeInfo, mode),
                username(OwnerUID, uname),
                groupname(GroupGID, gname),
                (long long)Size,
                entry->d_name);
           
       }
   }
   
   
   // ... TODO ...

   // finish up
   closedir(df); // UNCOMMENT this line
   

       
   return EXIT_SUCCESS;
}

// convert octal mode to -rwxrwxrwx string
char *rwxmode(mode_t mode, char *str)
{
    /*
   char ob_type[1];
   switch (mode & S_IFMT) {
   case S_IFDIR:  strcpy(ob_type,"d");             break;
   case S_IFLNK:  strcpy(ob_type,"l");             break;
   case S_IFREG:  strcpy(ob_type,"-");             break;
   default:       strcpy(ob_type,"?");             break;
   }
   
   str[0] = '1';
   
   char user_perms[3];
   switch (mode & S_IRWXU) {
   case S_IRUSR:  strcpy(user_perms, "r--");       break;
   case S_IWUSR:  strcpy(user_perms, "-w-");       break;
   case S_IXUSR:  strcpy(user_perms, "--x");       break;
   default:       strcpy(user_perms, "?");         break;
   }
   str[1] = *strdup(user_perms);
   
   char group_perms[3];
   switch (mode & S_IRWXG) {
   case S_IRGRP:  strcpy(group_perms, "r--");             break;
   case S_IWGRP:  strcpy(group_perms, "-w-");             break;
   case S_IXGRP:  strcpy(group_perms, "--x");             break;
   default:       strcpy(group_perms, "?");               break;
   }
   str[4] = *strdup(group_perms);
   
   char all_perms[3];
   switch (mode & S_IRWXO) {
   case S_IROTH:  strcpy(all_perms, "r--");              break;
   case S_IWOTH:  strcpy(all_perms, "-w-");              break;
   case S_IXOTH:  strcpy(all_perms, "--x");              break;
   }
   str[7] = *strdup(all_perms);
   str[10] = '\0';
   */
   
   
   strcpy(str, "?rwxrwxrwx");
   
   mode_t ob_type = mode & S_IFMT;
   mode_t general_perms;
   
   if (ob_type == S_IFDIR) {
       str[0] = 'd';
       
   } else if (ob_type == S_IFLNK) {
       str[0] = 'l';
       
   } else if (ob_type == S_IFREG) {
       str[0] = '-';;
   }
   
   int i = 0;
     
   // Check read perms
   for (i = 1; i < 10; i = i + 3) {
       general_perms = mode & S_IRUSR;
       if (general_perms != S_IRUSR  && i == 1) {
            str[i] = '-';
       }
       general_perms = mode & S_IRGRP;
       if (general_perms != S_IRGRP && i == 4) {
            str[i] = '-';
       }
       general_perms = mode & S_IROTH;
       if (general_perms != S_IROTH  && i == 7) {
            str[i] = '-';
       }
   }
   
   
    // Check write perms
   for (i = 2; i < 10; i = i + 3) {
       general_perms = mode & S_IWUSR;
       if (general_perms != S_IWUSR && i == 2) {
            str[i] = '-';
       }
       general_perms = mode & S_IWGRP;
       if (general_perms != S_IWGRP && i == 5) {
            str[i] = '-';
       }
       general_perms = mode & S_IWOTH;
       if (general_perms != S_IWOTH && i == 8) {
            str[i] = '-';
       }

   }
   
    // Check execute perms
   for (i = 3; i < 10; i = i + 3) {
       general_perms = mode & S_IXUSR;
       if (general_perms != S_IXUSR && i == 3) {
            str[i] = '-';
       }
       general_perms = mode & S_IXGRP;
       if (general_perms != S_IXGRP && i == 6) {
            str[i] = '-';
       }
       general_perms = mode & S_IXOTH;
       if (general_perms != S_IXOTH && i == 9) {
            str[i] = '-';
       }
   }    
   
   
   return str;
   // ... TODO  rwxmode(ModeInfo, mode),
   //             username(OwnerUID, uname),
   //             groupname(GroupGID, gname),...
}

// convert user id to user name
char *username(uid_t uid, char *name)
{
   struct passwd *uinfo = getpwuid(uid);
   if (uinfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)uid);
   else
      snprintf(name, MAXNAME, "%s", uinfo->pw_name);
   return name;
}

// convert group id to group name
char *groupname(gid_t gid, char *name)
{
   struct group *ginfo = getgrgid(gid);
   if (ginfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)gid);
   else
      snprintf(name, MAXNAME, "%s", ginfo->gr_name);
   return name;
}
