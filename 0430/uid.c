//유저 확인
//해당 코드를 일반 id에서 실행시켜보고
//Root로 로그인 후 실행해본뒤 id 값이 다르게 나옴을 확인해보자

#include <stdio.h>
#include <unistd.h>

int main(){
	printf("user id\n");
	printf("%d\n", getuid());
	printf("%d\n", geteuid());

	printf("group id\n");
	printf("%d\n", getgid());
	printf("%d\n", getegid());

	return 0;
}
