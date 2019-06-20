########       Network Tool Makefile      ########
#####                                        #####
#####      		Makefile written by 		 #####
#####				Joe Abdo	             #####
#####                                        #####
#####         Inspired by - Grégory Lerbret  #####
##### 	       https://gl.developpez.com/ 	 #####
##################################################

EXEC = NetworkTool
CXXFLAGS = -Wall 
DEBUG = no
CC= g++

.PHONY: all clean debug-memory debuging

all: $(EXEC)

$(EXEC): main.o Network.o Host.o Port.o DataBase.o Algorithm.o LinuxNotification.o
	$(CC) -o $@ $^ -L/usr/lib -lsqlite3

main.o: main.cpp Network.h 
	$(CC) $(CXXFLAGS) -o $@ -c $< 

Network.o: Network.cpp Network.h Host.h Algorithm.h DataBase.h Compare.h LinuxNotification.h
	$(CC) $(CXXFLAGS) -o $@ -c $<

Host.o: Host.cpp Host.h Port.h
	$(CC) $(CXXFLAGS) -o $@ -c $<

Port.o: Port.cpp Port.h
	$(CC) $(CXXFLAGS) -o $@ -c $<

DataBase.o: DataBase.cpp DataBase.h Network.h Host.h
	$(CC) $(CXXFLAGS) -o $@ -c $<	

Algorithm.o: Algorithm.cpp Algorithm.h Network.h Host.h
	$(CC) $(CXXFLAGS) -o $@ -c $<

LinuxNotification.o: LinuxNotification.cpp LinuxNotification.h Host.h
	$(CC) $(CXXFLAGS) -o $@ -c $<

#Compare.o: Compare.cpp Compare.h
#	$(CC) $(CXXFLAGS) -o $@ -c $<

# Instruction to clean file generated by compilation
# 	as well as text files used
clean:
	rm *.o && rm NetworkTool && rm NmapOutput.txt

# Instruction to clean the log file containing error message
cleanLog:
	rm logFile.txt

	
# Instruction to check for memory leaks with valgrind
debug-memory: $(EXEC)
	valgrind --leak-check=full -v --show-leak-kinds=all\
	 --track-origins=yes ./$(EXEC)

# Instruction to compile and run at the same time
run: $(EXEC)
	./$(EXEC)
