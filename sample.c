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
	if (i == 5) break;
	}
	//_create("PUse", "Check_Num INT WorkNumber VARCHAR(10) RNumber VARCHAR(10) SNumber VARCHAR(10) SName VARCHAR(10) Unit VARCHAR(10) UseDate VARCHAR(20) UseCount INT");

	/*if (initalizing("D:\\c\\알고리즘\\Project\\product_table") == -1) {
		if (_create("product_table", "PNumber VARCHAR(10) PName VARCHAR(20) PUnit VARCHAR(10)") == -1)
			printf("%s", err_msg);
		file_column_free();
		return -1;
	}*/
	return 0;
}