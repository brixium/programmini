#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 255

int main(int argc, char * argv[]){
	if(argc != 2)
		printf("Usage: crittografa nomefile.ext\n");
	else{
		int l;
		char * filename;

		l = strlen(argv[1]);
		if((filename = (char *)malloc(sizeof(char)*l))){
			FILE * fp = NULL;
			FILE * fd = NULL;
			char tarocco[MAX];

			filename = argv[1];
			strcpy(tarocco, filename);
			tarocco[l] = 'a';
			tarocco[l+1] = 'p';
			tarocco[l+2] = '\0';
			printf("Lunghezza: %d\nTarocco: %s\nOriginale: %s\n", l, tarocco, filename);
			if((fp = fopen(filename, "rb"))){
				if((fd = fopen(tarocco, "wb"))){
					char key[MAX], cipher;
					int i;
					printf("Insert the encryption / decryption key [max 255 char]:");
					scanf("%s", &key[0]);
					for(i=0; !feof(fp); i++){
						fscanf(fp, "%c", &cipher);
						cipher = cipher ^ *(key+(i%MAX));
						fprintf(fd, "%c", cipher);
					}
					fclose(fd);	
					printf("Tutto fatto, andrò a casa...\n");
				}else
					printf("Fatal error: source file not found or the file is already opened by another process!\n");
				fclose(fp);
				printf("Fatto?\n");
			}else
				printf("Fatal error: destination file not found or the file is already opened by another process!\n");
			printf("incrocia le dita\n");
			free(filename);
			printf("Spero di si\n");
		}else
			printf("Fatal error: there's no memory left for this program, close some apps and retry!\n");
		printf("Cerchi rogne?\n");
	}

	return 0;
}
