#include "local.h"
#include <time.h>
//�۾����ù�ȣ, �۾�������ȣ �ҷ�����
//ǰ��, ǰ��, ���� �Է�
void P_use(){
	char* values;
	int r_count;
	result* _result;   //���Ḯ��Ʈ
	if (initalizing("D:\\c\\�˰���\\Project\\PUse") == -1) {
		if (_create("PUse", "WorkNumber VARCHAR(20) RNumber VARCHAR(20) UseDate VARCHAR(20) SNumber VARCHAR(20) SName VARCHAR(20) Unit VARCHAR(10) UseCount INT") == -1)
			printf("%s", err_msg);
		//printf("%s\n", err_msg);
		file_column_free();
		return -1;
	}
	
	if (_select("*","WorkNumber, RNumber, SNumber", &select_result_str) == -1) {
		printf("%s\n", err_msg);
		
		file_column_free();
			return -1;
	}
	
	r_count=recv_result(&_result, select_result_str);
	result_print(_result, r_count);


}


char Time() {                                 //����ð����ϱ�
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

void input_values(char* values) {  //������ �Է�
	
	char input[20];

	values = (char*)malloc(sizeof(input));
	values= "UseCount=";
	printf("������ : ");
	gets(input);
	strcat(values, input);
}