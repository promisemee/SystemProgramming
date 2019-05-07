#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int fd;
    pid_t pid;
    caddr_t addr;
    struct stat statbuf;

    if (argc != 2) {
        fprintf(stderr, "Usage : %s filename\n", argv[0]);
        exit(1);
    }

    if (stat(argv[1], &statbuf) == -1) {
        perror("stat");
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror("open");
        exit(1);
    }

	addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)0);
    //mmap을 이용해 메모리 맵핑 실시

    close(fd);

    switch (pid = fork()) {
        case -1 :  /* fork failed */
            perror("fork");
            exit(1);
            break;
        case 0 :   /* child process */
			printf("C : %s", addr);
			addr[0] = 'A';
			msync(addr, statbuf.st_size, MS_SYNC);
            printf("C : %s", addr);//바뀐 데이터 확인
            break;
        default :   /* parent process */
            printf("P : %s", addr);//printf로 데이터 확인
            addr[1] = 'T';//데이터 변경 및 동기화
			msync(addr, statbuf.st_size, MS_SYNC);
            printf("P : %s", addr);//바뀐 데이터 확인
            break;
    }

    return 0;
}
