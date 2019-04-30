//전에 구현했던 ls 함수를 이용해 출력시 getuid와 ctime함수를 이용해 
//각 파일들의 소유자와 마지막 갱신시간을 표시해보자
//hint)
//마지막 갱신시간의 경우 stat 구조체와 lstat 함수를 사용
//stat 구조체 선언 후 lstat(const char *filename, struct stat *buf) 함수를 이용해
//stat 구조체에 데이터를 채워넣는다
//stat 구조체에 존재하는 변수인st_mtime을 ctime으로 호출시 갱신시간 확인가능


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

static void do_ls(char *path);

int main(int argc, char *argv[])
{
	
    int i;

    if (argc < 2) {
        fprintf(stderr, "%s: no arguments\n", argv[0]);
        exit(1);
    }
    for (i = 1; i < argc; i++) {
        do_ls(argv[i]);
    }
    exit(0);
}

static void
do_ls(char *path)
{
    DIR *d;
    struct dirent *ent;
	struct stat st;
	char *mtime;

    d = opendir(path);          /* (1) */
    if (!d) {
        perror(path);
        exit(1);
    }
    while (ent = readdir(d)) {  /* (2) */
		char * buf = ent->d_name;
		if (lstat(buf, &st)<0) exit(1);
		mtime = ctime(&st.st_mtime);
        printf("%s\t%d\t%s\n", buf, st.st_uid, mtime);
		//파일, 파일들의 소유자와 마지막 갱신시간
    }
    closedir(d);                /* (1') */
}
