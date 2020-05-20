/*Harish Nagallapati
Prints our the contents of as many files as passed as an argument to the terminal.
Oct. 3, 2019 */

#include "FileManager.h"
using namespace std;

int main(int argc, char** argv) {
	fstream stream;
	for (int i = 1; i < argc; i++) {
		FileManager* fileManage_1 = new FileManager(argv[i]);	//Create FileManager object for each file passed as an argument

		cout << endl << "File " << argv[i] << " dump: \n";
		fileManage_1->dump(stream);

		delete fileManage_1;	//Delete the current FileManager object
	}
	return 0;
}