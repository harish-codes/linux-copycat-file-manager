/*Harish Nagallapati
Header file for class containing all neccessary headers, function protoypes and data members.
Oct. 3, 2019 */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <errno.h>
#include <fstream>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

class FileManager{

	public:
		FileManager(void);	//DEFAULT CONSTRUCTOR
		FileManager(std::string fileName);	//CONSTRUCTOR
		~FileManager();	//DESTRUCTOR

		void expand(std::string dirName);	//INITIALIZATION FUNCTIONS

		std::string getName();	//GETTERS
		std::string getType();
		int getSize();
		int getOwnerUserID();
		std::string getOwnerUserName();
		int getGroupID();
		std::string getGroupName();
		std::string getPerms();
		std::string getAccessTime();
		std::string getModTime();
		std::string getStatChangeTime();
		int getBlkSize();
		int getErrorNum();
		std::string getErrorNumStr();
		std::vector<std::string> getChildren();

		void dump(std::fstream& streamArg);
		void renameFile(std::string newName);	//OTHER FUNCTIONS
		void remove(void);
		bool compare(std::string fileName);

	private:
		std::string name;
		std::string type;
		int size;
		int ownerUserID;
		std::string ownerUserName;
		int groupID;
		std::string groupName;
		std::string perms;
		std::string accessTime;
		std::string modTime;
		std::string statChangeTime;
		int blkSize;
		std::vector<std::string> children;
		int errornum;
};
#endif