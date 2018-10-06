// COMP1521 18s2 Week 10 Lab
// dns.c ... simple DNS lookup client

#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char **argv)
{
    struct in_addr ip;    // see "man 3 inet_aton"
    struct hostent *hp;  // see "man 3 gethostbyname"

    if (argc < 2) {
        printf("Usage: %s HostName|IPaddr\n", argv[0]);
        return 1;
    }

    // TODO  
    
    // If IP format
    if (inet_aton(argv[1], &ip)) {
    
        hp = gethostbyaddr(&ip, sizeof(ip), AF_INET);
        
        if (hp == NULL) {
            printf("No name associated with %s\n", argv[1]);
        
        } else {
            printf("%s -> %s\n", argv[1], hp->h_name);
        }
    
    } else {
        hp = gethostbyname(argv[1]);
        
        if (hp == NULL) {
            printf("Can't resolve %s\n", argv[1]);
        
        } else {

            memcpy(&ip, hp->h_addr_list[0], hp->h_length);

            printf("%s -> %s\n", argv[1], inet_ntoa(ip));
            
           
            
            printf("alias: %s", hp->h_aliases[0]);
        }
    }
    
    

    return 0;
}



// char alias[100];
//          while(strcpy(alias, hp.
