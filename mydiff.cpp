/*Harish Nagallapati
Compares two files to see if their contents are the same.
Oct. 3, 2019 */

#include "FileManager.h"
using namespace std;

int main(int argc, char** argv) {
	if (argc != 3) {	//ERROR
		cout << "ERROR: The mydiff command takes exactly two filenames/filepaths as arguments.\n";
		return -1;
	}
	else {
		FileManager* fileManage_1 = new FileManager(argv[1]);

		bool same = fileManage_1->compare(argv[2]);
		if (same) {	//IDENTICAL
			cout << "The files have identical contents.\n";
		}
		else {
			cout << "The files are NOT identical.\n";
		}
			delete fileManage_1;
	}
	return 0;
}