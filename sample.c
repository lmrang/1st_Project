#include "local.h"

int main() {
	
	P_use();
	//_create("Work", "WorkNumber VARCHAR(20) OrderDate VARCHAR(20) DueDate INT OrderCount INT Status VARCHAR(10)");
	//_create("Result", "WorkNumber VARCHAR(20) RNumber VARCHAR(20)");
	//_create("Product", "PNumber VARCHAR(20) PName VARCHAR(20) PUnit VARCHAR(20)");

	/*if (initalizing("D:\\c\\알고리즘\\Project\\product_table") == -1) {
		if (_create("product_table", "PNumber VARCHAR(10) PName VARCHAR(20) PUnit VARCHAR(10)") == -1)
			printf("%s", err_msg);
		file_column_free();
		return -1;
	}*/

	//if (_create("PUse", "WorkNumber VARCHAR(10) RNumber VARCHAR(10) UseDate VARCHAR(10) SNumber VARCHAR(10) SName VARCHAR(10) Unit VARCHAR(10) UseCount VARCHAR(10)") == -1)

	return 0;
}