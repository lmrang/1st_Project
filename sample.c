#include "local.h"

int main() {
	//char* values = "'A100', '�÷�(blue)', 50";
	char* values;
	//char* conditional = "TP='q'";
	char* conditional = "����=100";
	char* set = "TP='c'";
	//char* select_column = "code, number, TP, FLT, DBL";
	char* select_column = "code, number, TP";
	char input[20];
	int ininput;

	result* _result;
	result* find;
	int result_count;

	//_create("abcd", "ǰ�� VARCHAR(20) ǰ�� VARCHAR(20) ���� INT");      //���̺� ���� - ���ʻ��� �ÿ��� �ʿ�

	if (initalizing("D:\\c\\�˰���\\Project\\abcd") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	print_data();
	printf("\n");

	values = (char*)malloc(sizeof(input));
	printf("ǰ�� : ");
	gets(input);
	strcpy(values, "'");
	strcat(values, input);
	strcat(values, "', ");
	
	printf("ǰ�� : ");
	gets(input);
	strcat(values, "'");
	strcat(values, input);
	strcat(values, "', ");

	printf("���� : ");
	gets(input);
	strcat(values, input);


	if (_insert(values) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_delete("ǰ��=NULL") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");

	/*if (_update(conditional, set) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}*/

	/*if (_select(conditional, select_column, &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		printf("%s\n\n", select_result_str);
	}*/

	/*print_data();
	printf("\n");
	file_column_free();*/


	/*if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}*/
	/*result_print(_result, result_count);
	printf("\n\n");
	file_column_free();
	result_free(_result, result_count);*/

	/*if ((find = find_result(_result, "code")) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		result_free(_result, result_count);
		return -1;
	}
	printf("     %s\n", find->name);
	printf("=============\n");
	for (int i = 0; i < result_count; i++) {
		switch (find->type) {
		case INT:
			if (int_is_null(find->_int_data[i]))
				printf("     (null)\n");
			else
				printf("     %d\n", find->_int_data[i]);
			break;
		case FLOAT:
			if (float_is_null(find->_float_data[i]))
				printf("     (null)\n");
			else
				printf("     %.5f\n", find->_float_data[i]);
			break;
		case DOUBLE:
			if (double_is_null(find->_double_data[i]))
				printf("     (null)\n");
			else
				printf("     %.12lf\n", find->_double_data[i]);
			break;
		case CHAR:
			if (char_is_null(find->_char_data[i]))
				printf("     (null)\n");
			else
				printf("     %c\n", find->_char_data[i]);
			break;
		case VARCHAR:
			if (string_is_null(find->_string_data[i]))
				printf("     (null)\n");
			else
				printf("     %s\n", find->_string_data[i]);
			break;
		}
	}*/

	/*file_column_free();
	result_free(_result, result_count);*/
}