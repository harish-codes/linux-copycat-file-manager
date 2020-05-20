# linux-copycat-file-manager
File management utility that mimics all the basic file management functions of a Linux OS.

**The g++ compiler must be installed in order to build and execute these files.

mymv.cpp - Moves and renames files. 
<br />To build and execute this, type: 
<br />    1. g++ FileManager.cpp mymv.cpp -o mymv
<br />    2. ./mymv oldname newname OR ./mymv pathname1/oldname pathname2/newname

myrm.cpp - Mimics "rm" Linux command. Deletes files.
To build and execute this, type:
<br />    1. g++ FileManager.cpp myrm.cpp -o myrm
<br />    2. ./myrm filename1 filename2 ....etc.				

mydiff.cpp - Mimics "diff" Linux command. Reports if they are same or different.
To build and execute this, type: 
              1. g++ FileManager.cpp mydiff.cpp -o mydiff
					    2. ./mydiff filename1 filename2

mystat.cpp - Mimics "stat" Linux command. Outputs all information of the file.
To build and execute this, type: 
              1. g++ FileManager.cpp mystat.cpp -o mystat
					    2. ./mystat filename

mycat.cpp - Mimics "cat" Linux command. Displays contents of files.
To build and execute this, type: 
              1. g++ FileManager.cpp mycat.cpp -o mycat
					    2. ./mycat filename1 filename2 .....etc.				

myls.cpp - Mimics "ls" Linux command. For directory, lists all contents of directory. For all other file types, displays file's name. If "-l" option used, a long-form listing will be used.
To build and execute this, type: 
              1. g++ FileManager.cpp myls.cpp -o myls
					    2. ./myls OR ./myls -l OR ./myls filename OR ./myls dirname OR ./myls filename -l OR ./myls dirname -l


mycp.cpp - Mimics "cp" Linux command. Copies a file to a destination.
To build and execute this, type: 
              1. g++ FileManager.cpp mycp.cpp -o mycp
					    2. ./mycp filename1 filename2 OR ./mycp pathname1/oldname pathname2/newname			
