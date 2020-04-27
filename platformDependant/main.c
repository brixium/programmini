#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[]){
	char * platform;

	if( ( platform = malloc(sizeof(char)*12) ) ){
		#if defined(_WIN32)
		strcpy(platform, "Windows");
		#elif defined(__APPLE__)
		strcpy(platform, "macOS");
		#elif defined(__linux__)
		strcpy(platform, "Linux");
		#elif defined(__sun)
		strcpy(platform, "Solaris");
		#elif defined(__FreeBSD__)
		strcpy(platform, "FreeBSD");
		#elif defined(__NetBSD__)
		strcpy(platform, "NetBSD");
		#elif defined(__OpenBSD__)
		strcpy(platform, "OpenBSD");
		#elif defined(__hpux)
		strcpy(platform, "HP-UX");
		#elif defined(__osf__)
        strcpy(platform, "Tru64 UNIX");
        #elif defined(__sgi)
        strcpy(platform, "Irix");
		#elif defined(_AIX)
        strcpy(platform, "AIX");
		#endif
		if(strcmp(platform, "") == 0 )
			printf("Your OS is not on my list :(\n");
		else
			printf("You are running %s\n", platform);
	}else{
		printf("OOM ERROR\n");
		return 1;
	}
	return 0;
}

