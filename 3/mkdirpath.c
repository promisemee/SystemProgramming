#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

//Making directoreis

int main(int argc, char *argv[]){
	int i;
	mode_t old;
	old = umask(0);	

	if(argc<2){
		fprintf(stderr, "%s : no arguments\n", argv[0]);
		exit(1);
	}
	for(i = 1 ; i<argc ; i++){
		mkdir(argv[i], 0777);
	}
	umask(old);
	return 0;
}
