/*Harish Nagallapati
Copy a file's contents into another file. If the other file does not exist it will create it.
Oct. 3, 2019 */

#include "FileManager.h"
using namespace std;

int main(int argc, char** argv) {

	if (argc != 3) {	//ERROR
		cout << "ERROR: 3 Arguments must be passed for this command.\n";
	}
	else {
		FileManager* fileManage_1 = new FileManager(argv[1]);

		ifstream orig (argv[1],ifstream::binary);
		ofstream newFile(argv[2], ifstream::binary);

		orig.seekg(0, orig.end);
		long size = orig.tellg();	//Get size of original file
		orig.seekg(0);

		char* buffer = new char[size];

		orig.read(buffer, size);	//READ from original file
		newFile.write(buffer, size);	//WRITE to newFile

		delete[] buffer;	//CLOSE buffer, file streams
		orig.close();
		newFile.close();

		delete fileManage_1;
	}
	return 0;
}