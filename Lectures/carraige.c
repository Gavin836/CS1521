#include <stdio.h>

int main(void){
	char *msg = "Hello big world";
	char *msg2 = "Hello little world";
	char *msg3 = "WELL WELL";
	printf("%s\n%s\r\n\r\n%s\n", msg, msg2, msg3);

	return 0;
}