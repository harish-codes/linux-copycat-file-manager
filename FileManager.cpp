/*Harish Nagallapati
Cpp file for class containing all function definitions that were prototyped in class header file.
Oct. 3, 2019 */

#include "FileManager.h"
using namespace std;

/*Name: DEFAULT Constructor
Description: Creates FileManager object and initializes all data attributes with default values since no file has been passed as an argument.
Parameter Descriptions: N/A
Return: N/A
*/
FileManager::FileManager(void)
{
	this->name = "";
	this->type = "";
	this->size = 0;
	this->ownerUserID = 0;
	this->ownerUserName = "";
	this->groupID = 0;
	this->groupName = "";
	this->perms = "";
	this->accessTime = "";
	this->modTime = "";
	this->statChangeTime = "";
	this->blkSize = 0;
	this->errornum = 0;
	
}

/*Name: Constructor
Description: Creates FileManager object and initializes all data attributes.
Parameter Descriptions: fileName is the name of the file for which the object will be created for.
Return: N/A
*/
FileManager::FileManager(string fileName)
{
	this->name = fileName;

	struct stat buf;
	stat(fileName.c_str(), &buf);

	switch (buf.st_mode & S_IFMT) {
		case S_IFBLK:  this->type = "block";	break;
		case S_IFCHR:  this->type = "char";		break;
		case S_IFDIR:  this->type = "dir";		break;
		case S_IFIFO:  this->type = "fifo";     break;
		case S_IFLNK:  this->type = "link";     break;
		case S_IFREG:  this->type = "reg";		break;
		case S_IFSOCK: this->type = "socket";   break;
	default:       
		this->type = "unknown";  
		break;
	}

	this->size = buf.st_size;

	this->ownerUserID = buf.st_uid;
	struct passwd * pwd = getpwuid(this->ownerUserID);
	this->ownerUserName = pwd->pw_name;

	this->groupID = buf.st_gid;
	struct group * grp = getgrgid(this->groupID);
	this->groupName = grp->gr_name;

	if (buf.st_mode & S_IRUSR) {
		this->perms = this->perms + "r";
	}
	else {
		this->perms = this->perms + "-";
	}
	if (buf.st_mode & S_IWUSR) {
		this->perms = this->perms + "w";
	}
	else {
		this->perms = this->perms + "-";
	}
	if (buf.st_mode & S_IXUSR) {
		this->perms = this->perms + "x";
	}
	else {
		this->perms = this->perms + "-";
	}
	if (buf.st_mode & S_IRGRP) {
		this->perms = this->perms + "r";
	}
	else {
		this->perms = this->perms + "-";
	}
	if (buf.st_mode & S_IWGRP) {
		this->perms = this->perms + "w";
	}
	else {
		this->perms = this->perms + "-";
	}
	if (buf.st_mode & S_IXGRP) {
		this->perms = this->perms + "x";
	}
	else {
		this->perms = this->perms + "-";
	}
	if (buf.st_mode & S_IROTH) {
		this->perms = this->perms + "r";
	}
	else {
		this->perms = this->perms + "-";
	}
	if (buf.st_mode & S_IWOTH) {
		this->perms = this->perms + "w";
	}
	else {
		this->perms = this->perms + "-";
	}
	if (buf.st_mode & S_IXOTH) {
		this->perms = this->perms + "x";
	}
	else {
		this->perms = this->perms + "-";
	}
	
	//this->accessTime = ctime(&buf.st_atime);
	this->modTime = ctime(&buf.st_mtime);
	this->statChangeTime = ctime(&buf.st_ctime);

	string time = ctime(&buf.st_mtime);
	time = time.substr(0, time.length() - 1);
	this->accessTime = time;

	this->blkSize = buf.st_blksize;

	expand(fileName);
}

/*Name: Destructor
Description: Destroys FileManager object.
Parameter Descriptions: N/A
Return: N/A
*/
FileManager::~FileManager()
{
	//cout << "Object deleted.\n";
}

/*Name: expand
Description: If argument passed is a directory, it will popular a vector with all the director's contents.
Parameter Descriptions: dirName is the name of the directory
Return: N/A
*/
void FileManager::expand(string dirName) {

	DIR *dirOpen = opendir(dirName.c_str());
	struct dirent *dir;

	if (dirOpen == NULL) {	//ERROR
		this->errornum = errno;
		//cout << "Opening Directory ERROR #: " << this->errornum << "\n";
		//cout << "ERROR string: " << strerror(this->errornum) << endl;
	}
	else {
	errno = 0;
	while ((dir = readdir(dirOpen)) != NULL) {	//As long as we don't reach the end of the directory's contents..
		if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))	//Do NOT include current directory or directory one level up in file hierarchy as children
		{
			// do nothing
		}
		else {	//Add directory content to vector
			this->children.push_back(dir->d_name);
			//cout << dir->d_name << endl;
		}
	}
	if (dir == NULL) {	//If readdir() gives error update errno
		if (errno != 0) {
			this->errornum = errno;
		}
	}
	int close = closedir(dirOpen);
	if (close != 0) {	//If error when closing directory, set internal object errornum
		this->errornum = errno;
	}
	}

}

/*Name: getName
Description: Allows name of file in FileManager Object to be used outside of the class.
Parameter Descriptions: N/A
Return: Name of the file in string format.
*/
std::string FileManager::getName()
{
	return this->name;
}

/*Name: getType
Description: Allows type of file in FileManager Object to be used outside of the class.
Parameter Descriptions: N/A
Return: Type of the file in string format.
*/
std::string FileManager::getType()
{
	return this->type;
}

/*Name: getSize
Description: Allows size of file in FileManager Object to be used outside of the class.
Parameter Descriptions: N/A
Return: Size of the file in int format.
*/
int FileManager::getSize()
{
	return this->size;
}

/*Name: getOwnerUserID
Description: Allows owner of file's User ID in FileManager Object to be used outside of the class.
Parameter Descriptions: N/A
Return: Owner's User ID in int format.
*/
int FileManager::getOwnerUserID()
{
	return this->ownerUserID;
}

/*Name: getOwnerUserName
Description: Allows owner of file's username in FileManager Object to be used outside of the class.
Parameter Descriptions: N/A
Return: Owner's user name in string format.
*/
std::string FileManager::getOwnerUserName()
{
	return this->ownerUserName;
}

/*Name: getGroupID
Description: Allows group ID of file in FileManager Object to be used outside of the class.
Parameter Descriptions: N/A
Return: Group ID of file in int format.
*/
int FileManager::getGroupID()
{
	return this->groupID;
}

/*Name: getGroupName
Description: Allows group name of file in FileManager Object to be used outside of the class.
Parameter Descriptions: N/A
Return: Group name of file in string format.
*/
std::string FileManager::getGroupName() {
	return this->groupName;
}

/*Name: getPerms
Description: Allows permissions of file in FileManager Object to be used outside of the class.
Parameter Descriptions: N/A
Return: Permissions of file in string format.
*/
std::string FileManager::getPerms()
{
	return this->perms;
}

/*Name: getAccessTime
Description: Allows last access time of the file in FileManager Object to be used outside of the class.
Parameter Descriptions: N/A
Return: Last access time of file in string format.
*/
std::string FileManager::getAccessTime()
{
	return this->accessTime;
}

/*Name: getModTime
Description: Allows last modification time of the file in FileManager Object to be used outside of the class.
Parameter Descriptions: N/A
Return: Last modification time of file in string format.
*/
std::string FileManager::getModTime()
{
	return this->modTime;
}

/*Name: getStatChangeTime
Description: Allows last status change time of the file in FileManager Object to be used outside of the class.
Parameter Descriptions: N/A
Return: Last status change time of file in string format.
*/
std::string FileManager::getStatChangeTime()
{
	return this->statChangeTime;
}

/*Name: getBlkSize
Description: Allows block size of the file in FileManager Object to be used outside of the class.
Parameter Descriptions: N/A
Return: Block size of file in int format.
*/
int FileManager::getBlkSize(){
	return this->blkSize;
}

/*Name: getErrorNum
Description: Allows error number of the file in FileManager Object to be used outside of the class.
Parameter Descriptions: N/A
Return: Error number of file in int format.
*/
int FileManager::getErrorNum() {
	return this->errornum;
}

/*Name: getErrorNumStr
Description: Allows error string of the file in FileManager Object to be used outside of the class.
Parameter Descriptions: N/A
Return: Error string of file in string format.
*/
string FileManager::getErrorNumStr() {
	return strerror(this->errornum);
}

/*Name: getChildren
Description: Allows vector contents of a directory in FileManager Object to be used outside of the class.
Parameter Descriptions: N/A
Return: Vector contents of a directory in string format.
*/
vector<string> FileManager::getChildren() {
	return this->children;
}

/*Name: dump
Description: Dumps (prints) all contents of file that's passed in as argument to the terminal.
Parameter Descriptions: File stream to be used for reading and writing to file/terminal.
Return: N/A
*/
void FileManager::dump(fstream& streamArg) {
	if (this->type != "reg"){//ERROR, not a regular file
		this->errornum = errno;
		cout << "ERROR: To dump, the file must me a regular file!\n";
	}
	else {//Regular file
		streamArg.open(this->name,ios::in);	//Open the file
		if (streamArg.is_open()) {	//File is open, SUCCESS
			char* buffer = new char[this->blkSize];
			//cout << "File is open!\n";

			while (streamArg.readsome(buffer, this->blkSize)) {//WHILE there is content in the file to read, keep reading it
			
			}

			if (streamArg) {	//READ WAS SUCCESSFUL
				//cout << "Successful.\n";
				cout << buffer << endl;
			}
			else {	//ERROR
				this->errornum = errno;
			}
			delete[] buffer;
		}
		else {	//ERROR, file not opened
			this->errornum = errno;
			cout << "ERROR #: " << this->errornum << ", " << strerror(this->errornum) << endl;
		}
		streamArg.close();
	}
}

/*Name: renameFile
Description: Renames the FileManager Object and renames the file on disk.
Parameter Descriptions: newName is the new name of the file.
Return: N/A
*/
void FileManager::renameFile(string newName) {
	
	int renamed = rename(this->name.c_str(), newName.c_str());
	if (renamed != 0) {	//ERROR
		this->errornum = errno;
		cout << "ERROR #: " << errornum << ". " << strerror(this->errornum) << ".\n";
	}
	else {	//SUCCESS, so rename object's name attribute
		this->name = newName;
	}

}

/*Name: remove
Description: Deletes the file on the disk and resets all of the FileManager object's attributes associated with it.
Parameter Descriptions: N/A
Return: N/A
*/
void FileManager::remove(void) {

	int unlinkedCheck = unlink(this->name.c_str());	//Remove the file
	if (unlinkedCheck != 0) {	//ERROR removing file
		this->errornum = errno;
	}
	else {	//SUCCESSFUL REMOVAL OF FILE. Set all file object string attributes to an EMPTRY STRING. -1 for integer data attributes.
		this->name = "";
		this->type = "";
		this->size = -1;
		this->ownerUserID =-1;
		this->ownerUserName = "";
		this->groupID = -1;
		this->groupName = "";
		this->perms = "";
		this->accessTime = "";
		this->modTime = "";
		this->statChangeTime = "";
		this->blkSize = -1;
		this->errornum = -1;
	}
}

/*Name: compare
Description: Checks to see if the file passed in as argument has the same contents with the FileManager object's file.
Parameter Descriptions: Takes the name of a file as argument.
Return: True or false. True - identical file contents. False - nonidentical file contents.
*/
bool FileManager::compare(string fileName) {
	ifstream in1(this->name); //open two ins and one out
	ifstream in2(fileName);

	ofstream end("Matches.txt");
	
		while ((!in1.eof()) && (!in2.eof())) { //continue you get til the end of both

				string line1, line2;
				getline(in1, line1); //get lines
				getline(in2, line2);
			
				if (line1 != line2) {	//NON-IDENTICAL CONTENTS
					return false;
				}
		}
		if (in1.eof() && in2.eof()) {	//IDENTICAL CONTENTS
			return true;
		}
		in1.close();
		in2.close();   //close file streams
		end.close();
}
