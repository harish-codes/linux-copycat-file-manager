/*Harish Nagallapati
Removes all files passed as arguments.
Oct. 3, 2019 */

#include "FileManager.h"
using namespace std;

int main(int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		FileManager* fileManage_1 = new FileManager(argv[i]);	//Create FileManager object for each file passed as an argument
		
		fileManage_1->remove();	//Remove the current file
		
		if (fileManage_1->getErrorNum() != -1) {	//ERROR
			cout << "ERROR: File # " << i << " does not exist.\n";
		}
		delete fileManage_1;	//Delete the current FileManager object
	}
	return 0;
}