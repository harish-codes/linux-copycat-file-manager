/*Harish Nagallapati
Moves a file to designated path and renames.
Oct. 3, 2019 */

#include "FileManager.h"
using namespace std;

int main(int argc, char** argv) {
	FileManager * fileManage_1 = new FileManager(argv[1]);

	fileManage_1->renameFile(argv[2]);
	delete fileManage_1;

	return 0;
}