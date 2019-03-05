The tool should work on most Linux Versions.
Be sure to have nmap installed.

** Fedora: rpm -vhU https://nmap.org/dist/nmap-4.68-1.i386.rpm
** Centos: yum install nmap
** Debian: apt-get install nmap
** Ubuntu: sudo apt-get install nmap

To compile go to the terminal:
	* Change Directory to where to downloaded the filees
	* Compile : "make" (a makefile is included with your download)
	* Execute : "./NetworkTool"

You can use :
	"make clean" 	to clean your directory from .o files.
	"make debug" 	to add -g flag so you can debug the program
	"make run"	to make and run the program at the same time
	"make cleanLog"	to remove the log file (logFile.txt)

List of Errors that could occur:

Number		| Meaning					|
----------------|-----------------------------------------------|
1		| Network's Ip could not be found               |
----------------|-----------------------------------------------|
2		| Creating Host/Port without parameters		|
----------------|-----------------------------------------------|
3		| File could not be opened			|
----------------|-----------------------------------------------|
4		|
----------------|-----------------------------------------------|
5		|
----------------|-----------------------------------------------|
6		|
----------------|-----------------------------------------------|
