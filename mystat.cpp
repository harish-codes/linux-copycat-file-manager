/*Harish Nagallapati
Print out all the file attributes of the given file.
Oct. 3, 2019 */

#include "FileManager.h"
using namespace std;

int main(int argc, char** argv) {
	if (argc != 2) {	//ERROR
		cout << "ERROR: The mystat command takes exactly 1 filename as an argument.\n";
		return -1;
	}
	else {
		FileManager* fileManage_1 = new FileManager(argv[1]);

		cout << "File Name: " << fileManage_1->getName() << endl;	//PRINT ALL INFO
		cout << "File Type: " << fileManage_1->getType() << endl;
		cout << "File Size: " << fileManage_1->getSize() << "\n";
		cout << "User ID: " << fileManage_1->getOwnerUserID() << "\n";
		cout << "User Name: " << fileManage_1->getOwnerUserName() << "\n";
		cout << "Group ID: " << fileManage_1->getGroupID() << "\n";
		cout << "Group Name: " << fileManage_1->getGroupName() << "\n";
		cout << "Permissions: " << fileManage_1->getPerms() << "\n";
		cout << "Last Access Time: " << fileManage_1->getAccessTime() << endl;
		cout << "Last Mod Time: " << fileManage_1->getModTime();
		cout << "Last Stat Change Time: " << fileManage_1->getStatChangeTime();
		cout << "File Block Size: " << fileManage_1->getBlkSize() << "\n";

		if (fileManage_1->getType() == "dir") {	//IF directory, print its childrens' names
			cout << "Children: ";
			for (int i = 0; i < fileManage_1->getChildren().size(); i++) {
				cout << fileManage_1->getChildren().at(i) << " ";
			}
			cout << endl;
		}
		else {
			cout << "Children: No children.\n";
		}
	}
	return 0;
}