//시스템 시간 확인

//Char* ctime(const time_t *t);
//time_t 시간값을 읽기편한 문자열로 변환

#include <stdio.h>
#include <time.h>

int main(void){
	time_t current_time;
	time(&current_time);
	printf(ctime(&current_time));
	return 0;
}
