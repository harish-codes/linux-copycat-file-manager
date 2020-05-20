/*Harish Nagallapati
Display general info of current directory or a file/directory that is passes as an argument.
Oct. 3, 2019 */

#include <unistd.h>
#include "FileManager.h"
using namespace std;

int main(int argc, char** argv) {

	char cwd[PATH_MAX];
	if (argc == 1) {//myls
		if (getcwd(cwd, sizeof(cwd)) != NULL) {	//If getcwd works
			FileManager* fileManage_1 = new FileManager(string(cwd));	//Create FileManager object for current directory

			for (int i = 0; i < fileManage_1->getChildren().size(); i++) {	//Print contents of current directory.
				cout << fileManage_1->getChildren().at(i) << " ";
			}
			delete fileManage_1;
		}
		else {
			cout << "ERROR: Could not retrieve current directory\n";
			return -1;
		}
	}
	else if (argc == 2) {
		if (string(argv[1]) == "-l") {//myls -l
			if (getcwd(cwd, sizeof(cwd)) != NULL) {
				FileManager* fileManage_1 = new FileManager(string(cwd));	//Create FileManager object for current directory

				int totalSize;
				for (int i = 0; i < fileManage_1->getChildren().size(); i++) {	//Print contents of current directory.
					FileManager* fileManage_child = new FileManager(fileManage_1->getChildren().at(i));//Create object for each child

					cout << fileManage_child->getPerms() << " " << fileManage_child->getOwnerUserID() << " " <<	//Print all info
						fileManage_child->getOwnerUserName() << " " << fileManage_child->getGroupName() << " " <<
						fileManage_child->getSize() << " " << fileManage_child->getAccessTime() << " " << 
						fileManage_child->getName() << endl;

					totalSize += fileManage_child->getSize(); //Add up the sizes of each child file
					delete fileManage_child;	//Delete child
				}
				cout << "Total: " << totalSize << endl;
				delete fileManage_1;
			}
			else {
				cout << "ERROR: Could not retrieve current directory\n";
				return -1;
			}
		}
		else {

			FileManager* fileManage_1 = new FileManager(argv[1]);	//Create FileManager object

			if (fileManage_1->getType() == "dir") {	//myls dirname
				for (int i = 0; i < fileManage_1->getChildren().size(); i++) {	//Print contents of current directory.
					cout << fileManage_1->getChildren().at(i) << " ";
				}
				cout << endl;
			}
			else {	//myls filename
				cout << fileManage_1->getName() << endl;
			}
			delete fileManage_1;
		}
	}
	else if (argc == 3) {
		FileManager* fileManage_1 = new FileManager(argv[1]);

		if ((fileManage_1->getType() != "dir") && (string(argv[2]) == "-l")) {	//myls filename -l
			cout << fileManage_1->getPerms() << " " << fileManage_1->getOwnerUserID() << " " <<	//Print all info
				fileManage_1->getOwnerUserName() << " " << fileManage_1->getGroupName() << " " <<
				fileManage_1->getSize() << " " << fileManage_1->getAccessTime() << " " <<
				fileManage_1->getName() << endl;
			cout << "Total: " << fileManage_1->getSize() << endl;
		}
		else if ((fileManage_1->getType() == "dir") && (string(argv[2]) == "-l")) {	//myls dirname -l
			int totalSize;
			for (int i = 0; i < fileManage_1->getChildren().size(); i++) {	//Print contents of current directory

				FileManager* fileManage_child = new FileManager(fileManage_1->getChildren().at(i));//Create object for each child
			
				cout << fileManage_child->getPerms() << " " << fileManage_child->getOwnerUserID() << " " <<	//Print all info
					fileManage_child->getOwnerUserName() << " " << fileManage_child->getGroupName() << " " <<
					fileManage_child->getSize() << " " << fileManage_child->getAccessTime() << " " <<
					fileManage_child->getName() << endl;

				totalSize += fileManage_child->getSize(); //Add up the sizes of each child file*/

				delete fileManage_child;
			}
			cout << "Total: " << totalSize << endl;
		}
		else {
			cout << "ERROR: Invalid arguments!\n";
			return -1;
		}
		delete fileManage_1;
	}
	else {
		cout << "ERROR: Invalid # of arguments provided.\n";
		return -1;
	}

	return 0;
}