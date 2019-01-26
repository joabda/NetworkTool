

CFLAGS = -Wall
CC= g++
EXEC = $(CC) -o $@ -c $< $(CFLAGS)

NetworkTool: main.o Utility.o nmap.o Process.o Output.o Compare.o 
	$(CC) -o $@ $^ $(CFLAGS)

main.o: main.cpp Utility.h nmap.h Process.h Output.h Compare.h
	$(EXEC)

Utility.o: Utility.cpp Utility.h
	$(EXEC)

nmap.o: nmap.cpp nmap.h Utility.h
	$(EXEC)

Process.o: Process.cpp Process.h Utility.h
	$(EXEC)

Output.o: Output.cpp Output.h Utility.h
	$(EXEC)

Compare.o: Compare.cpp Compare.h Utility.h
	$(EXEC)

clean:
	rm *.o && rm NetworkTool
	rm *.txt





