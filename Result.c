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
void num_management(result* result_head, int num);
void management_view();
void del_num_management(result* result_head, int num);
void update_num_management(int update, int num);

int check_num = 0;

int P_menu_select() {
	int select, i;
	int menu_num = 6;
	char** menu;

	menu = (char*)malloc(sizeof(char*) * menu_num);

	for (i = 0; i < menu_num; i++) {
		menu[i] = (char*)malloc(sizeof(char) * 50);
	}

	menu[0] = "자재사용등록";
	menu[1] = "자재사용등록 변경";
	menu[2] = "자재사용내역 삭제";
	menu[3] = "자재사용조회";
	menu[4] = "재고현황조회";
	menu[5] = "뒤로가기";
	printf("      메뉴선택    \n");
	printf("====================");
	select = Menu_select("\0", menu, "\0", menu_num, 0, 2);

	//free(menu[0]);

	free(menu);
	return select;
}

void P_use() {
	int i;
	char check[10];
	char* values;
	int use_num;
	char use[10] = "\0";
	int r_count, m_r_count, s_r_count;
	int select_num = 0;
	result* _result;   //연결리스트
	result* S_result;
	result* M_result;
	char choose[30] = "\0";
	char WorkNumber[30] = "WorkNumber=";
	char date[DATE_LENGTH + 5];
	char conditional[70] = "\0";
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

	if (_select("*", "WorkNumber, RNumber", &select_result_str) == -1) {                 //작업지시 번호 선택
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	select_num = 5;
	r_count = recv_result(&_result, select_result_str);
	gotoxy(21, 0);
	printf("작업지시번호  작업실적번호\n");
	gotoxy(21, 1);
	printf("==========================");
	i = select_task(_result, r_count, 25, 2);

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
	
	if (_select("PType=3", "PNumber, PName, PUnit", &select_result_str) == -1) {                    //type=3 자재만 출력, BOM연결 필요!
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	r_count = recv_result(&_result, select_result_str);
	
	gotoxy(48, 0);
	printf("  품번     품명   단위\n");
	gotoxy(48, 1);
	printf("======================");
	i = select_task(_result, r_count, 48, 2);
	select_num = 4;
	Find_choose(_result, i, &choose, select_num);           //conditional 만들기
	strcat(conditional, choose);


	/*******************************************************************************************/
	gotoxy(77, 0);
	printf("UseDate : ");
	Input_date(date, 1);
	make_conditional(&date, 1);                   //usedate set만들기
	strcat(conditional, date);

	file_column_free();

	num_management(_result, i, &use);                   //재고 수량 변경 함수
	strcat(conditional, use);
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
	//연결리스트를 이중포인터로 만들어서 Menu_select함수에 바로 연결된 함수
	char cur_int_data[10];
	int i, j;
	char** menu;
	result* cur;
	menu = (char*)malloc(sizeof(char*) * count);

	for (i = 0; i < count; i++) {
		menu[i] = (char*)malloc(sizeof(char) * 100);
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

	i = Menu_select("\0", menu, "\n", count, x, y);
	/*for (i = 0; i < count; i++) {
		free(menu[i]);
	}*/
	free(menu);
	return i;
}

void Find_choose(result* result_head, int result_count, char* choose, int select_num) {
	//해당되는 글자를 찾아주는 함수
	result* cur;
	int cur_num;
	char copy[40] = "\0";
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
	}
}

void make_conditional(char* choose, int select_num) {
	//conditional 조건에 맞게 변경
	char CON[30] = "\0";
	strcat(CON, "'");
	strcat(CON, choose);
	//printf("%d, %d\n", i, select_num);
	if (select_num == 0) {
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
	a = _getch();
}

void P_update() {
	int r_count;
	result* _result;   //연결리스트
	int select, i, colum_num, j;
	int menu_num = 2;
	char** menu;
	int update = 0;
	char update_input[20];
	char UseDate[30] = "UseDate=";
	char UseCount[20] = "UseCount=";
	char CheckNum[20] = "Check_Num= ";
	char choose[30] = "\0";

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
	gotoxy(24, 0);
	printf("지시번호 실적번호  품번   품명   단위   등록일  사용갯수\n");
	gotoxy(22, 1);
	printf("=============================================================");
	i = select_task(_result, r_count, 25, 2);
	file_column_free();

	if (initalizing("PUse") == -1) {
		printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_select("*", "Check_Num", &select_result_str) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	r_count = recv_result(&_result, select_result_str);
	colum_num = 1;
	Find_choose(_result, i, &choose, colum_num);           //conditional 만들기
	strcat(CheckNum, choose);
	file_column_free();

	/****************************************************************************/
	//printf("변경 선택\n");
	menu = (char*)malloc(sizeof(char*) * menu_num);
	for (j = 0; j < menu_num; j++) {
		menu[j] = (char*)malloc(sizeof(char) * 100);
	}
	menu[0] = "UseDate 변경";
	menu[1] = "UseCount 변경";

	select = Menu_select("\0", menu, "\0", menu_num, 80, 0);
	free(menu);
	/****************************************************************************/
	if (select == 1) {   //UseDate 변경
		gotoxy(100, 0);
		printf("UseDate : ");
		Input_date(update_input, 1);
		make_conditional(&update_input, 0);                   //usedate set만들기
		strcat(UseDate, update_input);

		if (initalizing("PUse") == -1) {
			printf("%s", err_msg);
			file_column_free();
			return -1;
		}

		if (_update(CheckNum, UseDate) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}
		system("cls");
		printf("UseDate 변경이 완료되었습니다.\n");
		file_column_free();
		//_getch();
	}
	/***************************************************************************/
	if (select == 2) {    //UseCount 변경
		gotoxy(100, 0);
		printf("UseCount : ");
		scanf("%d", &update);
		sprintf(update_input, "%d", update);;
		strcat(UseCount, update_input);

		update_num_management(update, i);

		if (initalizing("PUse") == -1) {
			printf("%s", err_msg);
			file_column_free();
			return -1;
		}

		if (_update(CheckNum, UseCount) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}
		system("cls");
		printf("UseCount 변경이 완료되었습니다.\n");
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
	gotoxy(24, 0);
	printf("지시번호 실적번호  품번   품명   단위   등록일  사용갯수\n");
	gotoxy(22, 1);
	printf("=============================================================");
	i = select_task(_result, r_count, 25, 2);
	file_column_free();

	/******************************************************************************************************/
	if (initalizing("PUse") == -1) {
		printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_select("*", "SNumber", &select_result_str) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	r_count = recv_result(&_result, select_result_str);
	file_column_free();
	del_num_management(_result, i);
	/******************************************************************************************************/
	if (initalizing("PUse") == -1) {
		printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_select("*", "Check_Num", &select_result_str) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	r_count = recv_result(&_result, select_result_str);
	colum_num = 1;
	Find_choose(_result, i, &choose, colum_num);           //conditional 만들기
	strcat(CheckNum, choose);

	if (_delete(CheckNum) == -1) {							//삭제
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	file_column_free();
	/******************************************************************************************************/
	system("cls");
	printf("삭제가 완료되었습니다.\n");
	_getch();
}

void num_management(result* result_head, int num, char* use) {     //등록시 자재수량테이블 삭감
	result* _result;   //연결리스트
	char conditional[50] = "RNumber='";
	char count[20] = "UseCount=";
	int point = 0;
	result* cur;
	int r_count;
	int use_num = 0;
	char c_use_num[20] = "\0";
	char copy[20];
	int material;
	int material_check = 0;

	for (int i = 0; i < num; i++) {
		cur = result_head;

		while (1) {
			switch (cur->type) {
			case _VARCHAR:
				if (string_is_null(cur->_string_data[i]))
					strcat(conditional, "(NULL)");
				else {
					if (point == 0 && i == num - 1) {
						strcpy(copy, cur->_string_data[i]);
						material = material_choose(copy);
						point++;
					}
				}
				break;
			}
			if (cur->next == 0) {
				break;
			}
			else {
				cur = cur->next;
			}
		}
	}
	strcat(conditional, copy);
	strcat(conditional, "'");

	gotoxy(77, 1);
	printf("UseCount : ");
	scanf("%d", &use_num);
	sprintf(use, "%d", use_num);

	if (initalizing("PCount") == -1) {
		if (_create("PCount", "RNumber VARCHAR(10) RName VARCHAR(10) UseCount INT PUnit VARCHAR(10)") == -1)
			printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_select(conditional, "UseCount", &select_result_str) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	r_count = recv_result(&_result, select_result_str);

	for (int i = 0; i < r_count; i++) {
		cur = _result;
		while (1) {
			switch (cur->type) {
			case _INT:
				if (int_is_null(cur->_int_data[i]))
					printf("     (NULL)");
				else {
					point = cur->_int_data[i];
					break;
				}
			}
			if (cur->next == 0) {
				break;
			}
			else {
				cur = cur->next;
			}
		}
	}
	use_num = point - use_num;
	sprintf(c_use_num, "%d", use_num);
	strcat(count, c_use_num);
	file_column_free();

	/*******************************************************************************************/
	if (initalizing("PCount") == -1) {
		if (_create("PCount", "RNumber VARCHAR(10) RName VARCHAR(10) UseCount INT PUnit VARCHAR(10)") == -1)
			printf("%s", err_msg);
		file_column_free();
		return -1;
	}
	if (_update(conditional, count) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	file_column_free();
}

void del_num_management(result* result_head, int num) {			//삭제 시 재고 수량 복구
	result* cur;
	result* _result;
	char U_conditional[50] = "SNumber='";
	char conditional[50] = "RNumber='";
	char count[20] = "UseCount=";
	int point = 0;
	int U_point = 0, C_point = 0;
	char copy[20] = "\0";
	int material = 0, r_count = 0;
	char use_num[20] = "\0";

	for (int i = 0; i < num; i++) {
		cur = result_head;

		while (1) {
			switch (cur->type) {
			case _VARCHAR:
				if (string_is_null(cur->_string_data[i]))
					strcat(conditional, "(NULL)");
				else {
					if (point == 0 && i == num - 1) {
						strcpy(copy, cur->_string_data[i]);
						material = material_choose(copy);
						point++;
					}
				}
				break;
			}
			if (cur->next == 0) {
				break;
			}
			else {
				cur = cur->next;
			}
		}
	}
	strcat(U_conditional, copy);			//PNumber
	strcat(U_conditional, "'");

	strcat(conditional, copy);
	strcat(conditional, "'");
	/*******************************************************************************************/
	if (initalizing("PUse") == -1) {
		if (_create("PCount", "RNumber VARCHAR(10) RName VARCHAR(10) UseCount INT PUnit VARCHAR(10)") == -1)
			printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_select(U_conditional, "UseCount", &select_result_str) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	r_count = recv_result(&_result, select_result_str);

	for (int i = 0; i < r_count; i++) {
		cur = _result;
		while (1) {
			switch (cur->type) {
			case _INT:
				if (int_is_null(cur->_int_data[i]))
					printf("     (NULL)");
				else {
					U_point = cur->_int_data[i];
					break;
				}
			}
			if (cur->next == 0) {
				break;
			}
			else {
				cur = cur->next;
			}
		}
	}
	file_column_free();
	/*******************************************************************************************/
	if (initalizing("PCount") == -1) {
		if (_create("PCount", "RNumber VARCHAR(10) RName VARCHAR(10) UseCount INT PUnit VARCHAR(10)") == -1)
			printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_select(conditional, "UseCount", &select_result_str) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	r_count = recv_result(&_result, select_result_str);

	for (int i = 0; i < r_count; i++) {
		cur = _result;
		while (1) {
			switch (cur->type) {
			case _INT:
				if (int_is_null(cur->_int_data[i]))
					printf("     (NULL)");
				else {
					C_point = cur->_int_data[i];
					break;
				}
			}
			if (cur->next == 0) {
				break;
			}
			else {
				cur = cur->next;
			}
		}
	}
	file_column_free();

	C_point += U_point;
	sprintf(use_num, "%d", C_point);
	strcat(count, use_num);
	/**************************************************************************************************/
	if (initalizing("PCount") == -1) {
		if (_create("PCount", "RNumber VARCHAR(10) RName VARCHAR(10) UseCount INT PUnit VARCHAR(10)") == -1)
			printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_update(conditional, count) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	file_column_free();
}

void update_num_management(int update, int num) {
	result* cur;
	result* _result;
	char U_conditional[50] = "SNumber='";
	char conditional[50] = "RNumber='";
	char count[50] = "UseCount=";
	int point = 0;
	int U_point = 0, C_point = 0;
	char copy[20] = "\0";
	int material = 0, r_count = 0;
	char use_num[20] = "\0";

	/*************************************************************************/
	if (initalizing("PUse") == -1) {
		printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_select("*", "SNumber", &select_result_str) == -1) {  
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	r_count = recv_result(&_result, select_result_str);
	file_column_free();

	for (int i = 0; i < num; i++) {
		cur = _result;

		while (1) {
			switch (cur->type) {
			case _VARCHAR:
				if (string_is_null(cur->_string_data[i]))
					strcat(conditional, "(NULL)");
				else {
					if (point == 0 && i == num - 1) {
						strcpy(copy, cur->_string_data[i]);
						material = material_choose(copy);
						point++;
					}
				}
				break;
			}
			if (cur->next == 0) {
				break;
			}
			else {
				cur = cur->next;
			}
		}
	}

	strcat(U_conditional, copy);			//PNumber
	strcat(U_conditional, "'");

	strcat(conditional, copy);
	strcat(conditional, "'");

	/*******************************************************************************************/
	if (initalizing("PUse") == -1) {
		if (_create("PCount", "RNumber VARCHAR(10) RName VARCHAR(10) UseCount INT PUnit VARCHAR(10)") == -1)
			printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_select(U_conditional, "UseCount", &select_result_str) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	r_count = recv_result(&_result, select_result_str);

	for (int i = 0; i < r_count; i++) {
		cur = _result;
		while (1) {
			switch (cur->type) {
			case _INT:
				if (int_is_null(cur->_int_data[i]))
					printf("     (NULL)");
				else {
					U_point = cur->_int_data[i];
					printf("%d", U_point);
					break;
				}
			}
			if (cur->next == 0) {
				break;
			}
			else {
				cur = cur->next;
			}
		}
	}
	file_column_free();

	/*******************************************************************************************/
	if (initalizing("PCount") == -1) {
		if (_create("PCount", "RNumber VARCHAR(10) RName VARCHAR(10) UseCount INT PUnit VARCHAR(10)") == -1)
			printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_select(conditional, "UseCount", &select_result_str) == -1) {
		printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	r_count = recv_result(&_result, select_result_str);

	for (int i = 0; i < r_count; i++) {
		cur = _result;
		while (1) {
			switch (cur->type) {
			case _INT:
				if (int_is_null(cur->_int_data[i]))
					printf("     (NULL)");
				else {
					C_point = cur->_int_data[i];
					break;
				}
			}
			if (cur->next == 0) {
				break;
			}
			else {
				cur = cur->next;
			}
		}
	}
	file_column_free();

	C_point += U_point;
	C_point -= update;
	sprintf(use_num, "%d", C_point);
	strcat(count, use_num);
	/*******************************************************************************************************/
	if (initalizing("PCount") == -1) {
		if (_create("PCount", "RNumber VARCHAR(10) RName VARCHAR(10) UseCount INT PUnit VARCHAR(10)") == -1)
			printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (_update(conditional, count) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	file_column_free();
}

void management_view() {
	char a;

	if (initalizing("PCount") == -1) {
		printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	print_data();
	file_column_free();
	a = _getch();
}

int material_choose(char conditional[]) {
	//글자비교함수........... 정렬되어 있어야 한다는 단점이 있다.
	if (strcmp(conditional, "M0001") == 0) return 1;
	if (strcmp(conditional, "M0002") == 0) return 2;
	if (strcmp(conditional, "M0003") == 0) return 3;
	if (strcmp(conditional, "M0004") == 0) return 4;
	if (strcmp(conditional, "M0005") == 0) return 5;
	if (strcmp(conditional, "M0006") == 0) return 6;
	if (strcmp(conditional, "M0007") == 0) return 7;
	if (strcmp(conditional, "M0008") == 0) return 8;
	if (strcmp(conditional, "M0009") == 0) return 9;
}
