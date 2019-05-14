#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd1[2], fd2[2];
    pid_t pid;
    char buf[257];
    int len, status;

    if (pipe(fd1) == -1) {
        perror("pipe");
        exit(1);
    }

	if (pipe(fd2) == -1){
		perror("pipe");
		exit(1);
	}

    switch (pid = fork()) {
        case -1 :
            perror("fork");
            exit(1);
            break;
        case 0 : /* child */
            close(fd2[1]);
			close(fd1[0]);
			buf[0] = '\0';

			//read from fd2[0]
            write(1, "Child Process:", 15);
			len = read(fd2[0], buf, 256);
			write(1, buf, len);

			//write in fd1[1]
			write(fd1[1], "Message from Child Process\n", 28);

			close(fd1[1]);
			close(fd2[0]);
            break;
        default :
            close(fd2[0]);
			close(fd1[1]);
            buf[0] = '\0';
			
			//write in fd2[1]
            write(fd2[1], "Message from Parent Process\n", 29);

			//read from fd1[0]
			waitpid(pid, &status, 0);		//wait until Child process write
			write(1, "Parent Process:", 16);

			len = read(fd1[0], buf, 256);
			write(1, buf, len);

            close(fd2[1]);
			close(fd1[0]);
			break;
    }

    return 0;
}
