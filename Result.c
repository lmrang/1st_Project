#include "local.h"
#include <time.h>
//작업지시번호, 작업실적번호 불러오기
//품번, 품명, 단위 입력
void P_use(){
	char* values;
	int r_count;
	result* _result;   //연결리스트
	char choose[10];
	char conditional[20]="WorkNumber=";
	char set[20] = "RNumber=";
	//char* choose="\0";
	char* input;
	int i;

	
    /********************************************************************************************/

	if (initalizing("D:\\c\\알고리즘\\Project\\Result") == -1) {
		printf("%s", err_msg);
		file_column_free();
		return -1;
	}
	
	if (_select("*","WorkNumber", &select_result_str) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
			return -1;
	}
	
	r_count=recv_result(&_result, select_result_str);
	result_print(_result, r_count);

	//scanf("%d", &i);
	//strcpy(choose,Find_choose(_result, i));    //글자찾고
	//strcpy(choose, make_work_sen(&choose));		//set 만들기
	//printf("%s", choose);
	//strcat(conditional, choose);
	//file_column_free();
	select_task(_result, r_count);
	/********************************************************************************************/
	/*자재사용테이블*/
	/*if (initalizing("D:\\c\\알고리즘\\Project\\PUse") == -1) {
		if (_create("PUse", "WorkNumber VARCHAR(10) RNumber VARCHAR(10) UseDate VARCHAR(10) SNumber VARCHAR(10) SName VARCHAR(10) Unit VARCHAR(10) UseCount INT") == -1)
			printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_insert(choose) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}

	print_data();
	file_column_free();*/
	/********************************************************************************************/

}

//void P_use() {
//	char* values;
//	int r_count;
//	result* _result;   //연결리스트
//	
//
//	if (initalizing("D:\\c\\알고리즘\\Project\\task_order_table") == -1) {
//		printf("%s", err_msg);
//		file_column_free();
//		return -1;
//	}
//
//	if (_select("*", "WorkNumber", &select_result_str) == -1) {
//		printf("%s\n", err_msg);
//		file_column_free();
//		return -1;
//	}
//
//	r_count = recv_result(&_result, select_result_str);
//	result_print(_result, r_count);
//	file_column_free();
//	printf("\n");
//
//	return 0;
//}


int select_task(result* _result, int count) {
	int i;
	char** menu;
	result* cur;
	cur = _result;
	menu = (char*)malloc(sizeof(char*) * count);
	
	for (i = 0; i < count; i++) {
		menu[i] = (char*)malloc(sizeof(char) * 10);
	}

	for (i = 0; i < count; i++) {
		strcpy(menu[i], cur->_string_data[i]);
		printf("%s", menu[i]);
	}

	Menu_select("WorkNumber\n======================\n", menu[0], "\n", count);

	free(menu);
}

int Find_choose(result* result_head, int result_count) {
	result* cur;
	char choose[20]="\0";
	for (int i = 0; i < result_count; i++) {
		cur = result_head;
		//printf("%d", i);
		while (1) {
			switch (cur->type) {
			case _INT:
				if (int_is_null(cur->_int_data[i]))
					printf("     (NULL)");
				else
					printf("     %d", cur->_int_data[i]);
				break;
			case _FLOAT:
				if (float_is_null(cur->_float_data[i]))
					printf("     (NULL)");
				else
					printf("     %.5f", cur->_float_data[i]);
				break;
			case _DOUBLE:
				if (double_is_null(cur->_double_data[i]))
					printf("     (NULL)");
				else
					printf("     %.12lf", cur->_double_data[i]);
				break;
			case _CHAR:
				if (char_is_null(cur->_char_data[i])) {
					printf("     (NULL)");
				}
				else {
					printf("     %c", cur->_char_data[i]);
				}
				break;
			case _VARCHAR:
				if (string_is_null(cur->_string_data[i]))
					strcpy(choose, "(NULL)");
				else {
					strcpy(choose,cur->_string_data[i]);
				}
				break;
			}
			break;
		}
		printf("\n");
	}
	return choose;
}

int make_work_sen(char *choose) {
	char CON[30] = "\0";
	strcpy(CON, "'");
	strcat(CON, choose);
	strcat(CON, "'");
	return CON;
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