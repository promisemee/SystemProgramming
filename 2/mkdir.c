#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

//mkdir program using umask

int main(int argc, char *argv[]){
	int i;
	mode_t old;
	old = umask(0);

	if(argc<2){
		fprintf(stderr,"%s : no arguments\n", argv[0]);
		exit(1);	
	}
	for(i=1; i<argc; i++){
	//mkdir 함수를 이용해 argv를 통해 들어온 디렉토리 이름을 가진 폴더를 권한 0777번으로 생성
		mkdir(argv[i], 0777);
	}
	umask(old);
}
