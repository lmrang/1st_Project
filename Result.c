#include "local.h"
#include <time.h>
//작업지시번호, 작업실적번호 불러오기
//품번, 품명, 단위 입력
void P_use(){
	char* values;

	if (initalizing("D:\\c\\알고리즘\\Project\\PUse") == -1) {
		_create("PUse", "WorkNumber VARCHAR(20) RNumber VARCHAR(20) UseDate VARCHAR(20) SNumber VARCHAR(20) SName VARCHAR(20) Unit VARCHAR(10) UseCount INT");
		//printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}

	if (_select(conditional, select_column, &select_result_str) == -1) {
				printf("%s\n", err_msg);
		
				file_column_free();
				return -1;
			}
	else {
		printf("%s\n\n", select_result_str);
	}

	input_values(values);  //사용수량 입력

	
	
}


char Time() {                                 //현재시간구하기
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char MTime[20];
	char Time[5];

	sprintf(Time, "%d", tm.tm_year + 1900);
	strcpy(MTime, Time);
	strcat(MTime, "/");
	sprintf(Time, "%d", tm.tm_mon + 1);
	strcat(MTime, Time);
	strcat(MTime, "/");
	sprintf(Time, "%d", tm.tm_mday);
	strcat(MTime, Time);
}

void input_values(char* values) {  //사용수량 입력
	
	char input[20];

	values = (char*)malloc(sizeof(input));
	values= "UseCount=";
	printf("사용수량 : ");
	gets(input);
	strcat(values, input);
}