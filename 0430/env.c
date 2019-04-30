//전역변수 environ을 통해 시스템 환경변수 확인하기

#include <stdio.h>
#include <stdlib.h>

extern char ** environ;

int main(int argc, char * argv[]){
	char **p;

	for(p=environ; *p; p++){
		printf("%s\n", *p);
	}
	exit(0);
}
