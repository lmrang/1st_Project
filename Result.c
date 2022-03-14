#include "local.h"
#include <time.h>

int P_menu_select();
void P_use();
int select_task();
void Find_choose(result* result_head, int result_count, int select_num);
void make_conditional(char* choose);
void P_view(); 
void P_update();
void P_delete();

int check_num = 0;

int P_menu_select() {
	int select, i;
	int menu_num = 5;
	char** menu;

	menu = (char*)malloc(sizeof(char*) * menu_num);

	for (i = 0; i < menu_num; i++) {
		menu[i] = (char*)malloc(sizeof(char) * 10);
	}

	menu[0] = "자재사용등록";
	menu[1] = "자재사용등록 변경";
	menu[2] = "자재사용내역 삭제";
	menu[3] = "자재사용조회";
	menu[4] = "뒤로가기";

	select = Menu_select("\0", menu, "\0", menu_num, 0, 0);
	free(menu);
	return select;
}

void P_use(){
	int i;
	char check[10];
	char* values;
	int use_num;
	char use[10]="\0";
	int r_count;
	int select_num=0;
	result* _result;   //연결리스트
	char choose[30] = "\0";
	char WorkNumber[30] = "WorkNumber=";
	char date[DATE_LENGTH+5];
	char conditional[70]="\0";
	char result[30] = "\0";
	/********************************************************************************************/
	check_num++;
	sprintf(check, "%d", check_num);
	strcpy(conditional, check);
	strcat(conditional, ", ");
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
	i=select_task(_result, r_count, 25, 0);

	Find_choose(_result, i, &choose, select_num);           //conditional 만들기
	strcat(conditional, choose);
	strcpy(result, choose);
	file_column_free();

	/*******************************************************************************************/
	
	/*자재테이블*/
	if (initalizing("product_table") == -1) {
		if (_create("product_table", "PNumber VARCHAR(10) PName VARCHAR(20) PUnit VARCHAR(10)") == -1)
			printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_select("PType=3", "PNumber, PName, PUnit", &select_result_str) == -1) {                    //type=3 자재만 출력
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	
	r_count = recv_result(&_result, select_result_str);
	i = select_task(_result, r_count, 45 , 0);
	select_num = 4;
	Find_choose(_result, i, &choose, select_num);           //conditional 만들기
	strcat(conditional, choose);
	file_column_free();
	
	/*******************************************************************************************/
	gotoxy(70, 0);
	printf("UseDate : ");
	Input_date(date, 1);
	make_conditional(&date, 1);                   //usedate set만들기
	strcat(conditional, date);

	gotoxy(70, 1);
	printf("UseCount : ");
	scanf("%d", &use_num);
	sprintf(use, "%d", use_num);
	strcat(conditional, use);
	printf("\n\n");

	//printf("%s\n", conditional);
	/*******************************************************************************************/
	/*자재사용테이블*/
	if (initalizing("PUse") == -1) {
		if (_create("PUse", "Check_Num INT WorkNumber VARCHAR(10) RNumber VARCHAR(10) SNumber VARCHAR(10) SName VARCHAR(10) Unit VARCHAR(10) UseDate VARCHAR(10) UseCount INT") == -1)
			printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_insert(conditional) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}

	system("cls");
	printf("등록이 완료되었습니다.\n\n");
	print_data();
	_getch();
	file_column_free();

	return 0;
}

int select_task(result* _result, int count, int x, int y) {
	char cur_int_data[10];
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
			if (j <= 0) {
				switch (cur->type) {
				case _INT:
					if (int_is_null(cur->_int_data[i]))
						printf("     (NULL)");
					else {
						sprintf(cur_int_data, "%d", cur->_int_data[i]);
						strcpy(menu[i], cur_int_data);
						strcat(menu[i], "   ");
					}
					break;


				case _VARCHAR:
					if (string_is_null(cur->_string_data[i]))
						printf("     (NULL)");
					else {
						strcpy(menu[i], cur->_string_data[i]);
						strcat(menu[i], "   ");
					}
					break;
				}
			}
			else {
				switch (cur->type) {
				case _INT:
					if (int_is_null(cur->_int_data[i]))
						printf("     (NULL)");
					else {
						sprintf(cur_int_data, "%d", cur->_int_data[i]);
						strcat(menu[i], cur_int_data);
						strcat(menu[i], "   ");
					}
					break;
					

				case _VARCHAR:
					if (string_is_null(cur->_string_data[i]))
						printf("     (NULL)");
					else {
						strcat(menu[i], cur->_string_data[i]);
						strcat(menu[i], "   ");
					}
					break;
				}

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

	i=Menu_select("\0", menu, "\n", count, x, y);
	/*for (i = 0; i < count; i++) {
		free(menu[i]);
	}*/
	free(menu);
	return i;
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
				else {
					sprintf(copy, "%d", cur->_int_data[i]);
				}
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

void P_view() {
	char a;
	int r_count;
	result* _result;   //연결리스트

	if (initalizing("D:\\c\\알고리즘\\Project\\PUse") == -1) {
		printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	print_data();
	file_column_free();
	a=_getch();
}

void P_update() {
	int r_count;
	result* _result;   //연결리스트
	int select, i, colum_num;
	int menu_num = 2;
	char** menu;
	char update_input[20];
	char UseDate[30] = "UseDate=";
	char UseCount[20] = "UseCount=";
	char CheckNum[20] = "Check_Num= ";
	char choose[30] = "\0";

	if (initalizing("D:\\c\\알고리즘\\Project\\PUse") == -1) {
		printf("%s", err_msg);
		file_column_free();
		return -1;
	}
	if (_select("*", "WorkNumber, RNumber, SNumber, SName, Unit, UseDate, UseCount", &select_result_str) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	r_count = recv_result(&_result, select_result_str);
	i = select_task(_result, r_count, 25, 0);
	if (_select("*", "Check_Num", &select_result_str) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	r_count = recv_result(&_result, select_result_str);
	colum_num = 1;
	Find_choose(_result, i, &choose, colum_num);           //conditional 만들기
	strcat(CheckNum, choose);
	
	/****************************************************************************/
	printf("변경 선택\n");
	menu = (char*)malloc(sizeof(char*) * menu_num);
	for (i = 0; i < menu_num; i++) {
		menu[i] = (char*)malloc(sizeof(char) * 10);
	}
	menu[0] = "UseDate 변경";
	menu[1] = "UseCount 변경";

	select = Menu_select("\0", menu, "\0", menu_num, 80, 0);
	free(menu);
	/****************************************************************************/
	if (select == 1) {                //UseDate 변경
		printf("UseDate : ");
		Input_date(update_input, 1);
		make_conditional(&update_input, 0);                   //usedate set만들기
		strcat(UseDate, update_input);

		if (_update(CheckNum, UseDate) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}

		printf("UseDate 변경이 완료되었습니다.\n");
		//_getch();
	}
	/***************************************************************************/
	if (select == 2) {                //UseCount 변경
		printf("UseCount : ");
		scanf("%s", update_input);
		strcat(UseCount, update_input);

		if (_update(CheckNum, UseCount) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}

		printf("UseCount 변경이 완료되었습니다.\n");
		//_getch();
	}
	print_data();
	_getch();
	file_column_free();
}

void P_delete() {
	int r_count, i, colum_num;
	result* _result;   //연결리스트
	char choose[30] = "\0";
	char CheckNum[20] = "Check_Num= ";


	if (initalizing("PUse") == -1) {
		printf("%s", err_msg);
		file_column_free();
		return -1;
	}
	if (_select("*", "WorkNumber, RNumber, SNumber, SName, Unit, UseDate, UseCount", &select_result_str) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	r_count = recv_result(&_result, select_result_str);
	i = select_task(_result, r_count, 25, 0);

	if (_select("*", "Check_Num", &select_result_str) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	r_count = recv_result(&_result, select_result_str);
	colum_num = 1;
	Find_choose(_result, i, &choose, colum_num);           //conditional 만들기
	strcat(CheckNum, choose);

	if (_delete(CheckNum) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	system("cls");
	printf("삭제가 완료되었습니다.\n");
	_getch();
	file_column_free();
}