#include "local.h"
#include <time.h>

void Find_choose(result* result_head, int result_count, int select_num);
void make_conditional(char* choose);

//작업지시번호, 작업실적번호 불러오기
//품번, 품명, 단위 입력
void P_use(){
	int i;
	char* values;
	char use[10];
	int r_count;
	int select_num=0;
	result* _result;   //연결리스트
	char choose[30] = "\0";
	char WorkNumber[30] = "WorkNumber=";
	/*char Pnum_con[30] = "PNumber=";
	char PName[30] = "PName=";
	char PUnit[30] = "PUnit=";*/
	char date_set[30] = "UseDate=";
	char use_count[15] = "UseCount=";
	char date[DATE_LENGTH+5];
	char conditional[70]="\0";
    /********************************************************************************************/

	if (initalizing("Result") == -1) {
		printf("%s", err_msg);
		file_column_free();
		return -1;
	}
	
	if (_select("*","WorkNumber, RNumber", &select_result_str) == -1) {                 //작업지시 번호 선택
		printf("%s\n", err_msg);
		file_column_free();
			return -1;
	}
	select_num = 5;
	r_count=recv_result(&_result, select_result_str);
	i=select_task(_result, r_count);

	Find_choose(_result, i, &choose, select_num);           //conditional 만들기
	strcpy(conditional, choose);
	file_column_free();

	/*******************************************************************************************/

	//if (initalizing("Result") == -1) {
	//	printf("%s", err_msg);
	//	file_column_free();
	//	return -1;
	//}

	//if (_select("*", "WorkNumber", &select_result_str) == -1) {                 //작업지시 번호 선택
	//	printf("%s\n", err_msg);
	//	file_column_free();
	//	return -1;
	//}

	//r_count = recv_result(&_result, select_result_str);
	//Find_choose(_result, i, &choose, 0);           //conditional 만들기
	//strcat(WorkNumber, choose);
	//printf("%s", WorkNumber);

	/*******************************************************************************************/
	
	/*자재테이블*/
	if (initalizing("D:\\c\\알고리즘\\Project\\product_table") == -1) {
		if (_create("product_table", "PNumber VARCHAR(10) PName VARCHAR(20) PUnit VARCHAR(10)") == -1)
			printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_select("*", "PNumber, PName, PUnit", &select_result_str) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	
	r_count = recv_result(&_result, select_result_str);
	i = select_task(_result, r_count);
	select_num = 3;
	Find_choose(_result, i, &choose, select_num);           //conditional 만들기
	strcat(conditional, choose);
	//printf("%s\n", conditional);
	file_column_free();
	
	/*******************************************************************************************/
	printf("사용일자 : ");
	Input_date(date, 1);
	make_conditional(&date, 1);                   //usedate set만들기
	strcat(conditional, date);


	printf("사용갯수 : ");
	scanf("%s", use);
	make_conditional(&use, 0);
	strcat(conditional, use);
	printf("\n\n");

	//printf("%s\n", conditional);
	/*******************************************************************************************/
	/*자재사용테이블*/
	if (initalizing("D:\\c\\알고리즘\\Project\\PUse") == -1) {
		if (_create("PUse", "WorkNumber VARCHAR(10) RNumber VARCHAR(10) UseDate VARCHAR(10) SNumber VARCHAR(10) SName VARCHAR(10) Unit VARCHAR(10) UseCount INT") == -1)
			printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_insert(conditional) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}

	print_data();
	file_column_free();

	return 0;
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
	int i, j;
	char** menu;
	result* cur;
	menu = (char*)malloc(sizeof(char*) * count);
	
	for (i = 0; i < count; i++) {
		menu[i] = (char*)malloc(sizeof(char) * 10);
	}

	for (i = 0; i < count; i++) {
		cur = _result;
		j = 0;
		while (1) {
			printf(" i=%d, j=%d\n", i, j);
			if (j <= 0) {
				strcpy(menu[i], cur->_string_data[i]);
				strcat(menu[i], "   ");
			}
			else {
				strcat(menu[i], cur->_string_data[i]);
				strcat(menu[i], "   ");
			}

			if (cur->next == 0) {
				break;
			}
			else {
				cur = cur->next;
			}
			j++;
		}
	}

	i=Menu_select("\0", menu, "\n", count);
	return i;
	free(menu);
}

void Find_choose(result* result_head, int result_count, char* choose, int select_num) {
	result* cur;
	int cur_num;
	char copy[40]="\0";
	for (int i = 0; i < result_count; i++) {
		cur = result_head;
		cur_num = 0;
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
					if (i == result_count - 1) {
						strcpy(choose, cur->_string_data[i]);
						make_conditional(choose, select_num);
						select_num--;
						strcat(copy, choose);
					}
				}
				break;
			}
			if (cur->next == 0) {
				strcpy(choose, copy);
				break;
			}
			else {
				cur = cur->next;
				cur_num++;
			}
		}
		//printf("\n");
	}
}

void make_conditional(char* choose, int select_num) {
	char CON[30] = "\0";
	strcat(CON, "'");
	strcat(CON, choose);
	//printf("%d, %d\n", i, select_num);
	if (select_num==0) {
		strcat(CON, "'");
	}

	else strcat(CON, "', ");
	strcpy(choose, CON);
}