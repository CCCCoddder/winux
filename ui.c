#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAX_SPACE 98
int getch() {
    int c;
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr); // 현재 터미널 설정 읽음
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO); // CANONICAL과 ECHO 끔
    newattr.c_cc[VMIN] = 1;  // 최소 입력 문자 수를 1로 설정
    newattr.c_cc[VTIME] = 0; // 최소 읽기 대기 시간을 0으로 설정
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr); // 터미널에 설정 입력
    c = getchar();                              // 키보드 입력 읽음
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); // 원래의 설정으로 복구
    return c;
}

char *p[20] = {"calculate","movie","battleGround","mypc", "LOL", "paint", "internet", "study","asdf"};

int flag = 0;
char cc;


int getsize(){	//���� �̸��� ���� �迭�� ���� 
	char** ptr=p;
	int size=0;
	while(*ptr!=NULL){
		size++;
		*ptr++;
	}
	return size;
}

int getmax(){	//���� �̸��� ���� �� �̸��� ���� +2 ��ȯ 
	int max=0;
	for(int i=1;i<getsize();i++){
		if(strlen(p[max])<strlen(p[i]))
			max=i;
	}
	return strlen(p[max])+2;
}

void colorOn() { printf("\033[1;33m"); }
void colorOff() { printf("\033[0m"); }

void getFlag() {
    if (cc == 'a') {
        if (flag != 0)
            flag--;
    } else if (cc == 's') {
        if (flag != getsize())
            flag++;
    }
}

void start() {
    int space=getmax();
    int num=MAX_SPACE / space;
    int sur=MAX_SPACE % space;

    printf("----------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < getsize();i++) {
	/*
	if((i+1)% num==1)
		printf("|");
	*/	 
	if (flag == i)
            colorOn();
	printf("%-*s",space,p[i]);
	if (flag == i)
            colorOff();

	if((i+1)% num==0)
		printf("\n");
    }
    printf("\n");
    printf("----------------------------------------------------------------------------------------------------\n");
}

int main() {
    char mov;
    while (1) {
        start();
        cc = getch();
        getFlag();
        system("clear");
    }
    return 0;
}
