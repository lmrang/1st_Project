#include "local.h"

int main() {
	int i;

	while (1) {
	system("cls");
	i = P_menu_select();

	if (i == 1) P_use();
	if (i == 2) P_update();
	if (i == 3) P_delete();
	if (i == 4) P_view();
	if (i == 5) management_view();
	if (i == 6) break;
	}

	/*if (_create("PCount", "RNumber VARCHAR(10) RName VARCHAR(10) UseCount INT PUnit VARCHAR(10)") == -1) {
		printf("%s", err_msg);
		file_column_free();
		return -1;
	}

	if (initalizing("PCount") == -1) {
		printf("%s", err_msg);
		file_column_free();
		return -1;
	}
	_insert("'M0001', '����', 100, 'EA'");
	_insert("'M0002', '����', 1000, 'mL'");
	_insert("'M0003', '��н÷�', 500, 'mL'");
	_insert("'M0004', '��л���', 100, 'g'");
	_insert("'M0005', '�������', 100, 'mL'");
	_insert("'M0006', '����', 1000, 'g'");
	_insert("'M0007', '����Ĩ', 500, 'g'");
	_insert("'M0008', '���ݸ�', 700, 'g'");

	print_data();*/

	return 0;
}