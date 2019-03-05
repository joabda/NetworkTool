CFLAGS = -Wall -g
CC= g++
EXEC = NetworkTool

$(EXEC): main.o Host.o Network.o Port.o
	$(CC) -o $@ $^ $(CFLAGS)

main.o: main.cpp Host.o Network.o Port.o
	$(CC) -o $@ -c $< $(CFLAGS)

Network.o: Network.cpp Network.h Host.h
	$(CC) -o $@ -c $< $(CFLAGS)

Host.o: Host.cpp Host.h Port.h
	$(CC) -o $@ -c $< $(CFLAGS)

Port.o: Port.cpp Port.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm *.o && rm NetworkTool 
#&& rm temporary.txt && rm NmapOutput.txt

cleanLog:
	rm logFile.txt

debug: 
	CFLAGS+= -g
	$(EXEC)
	
debug-memory: $(EXEC)
	valgrind --leak-check=full -v --show-leak-kinds=all --track-origins=yes ./$(EXEC)

run: $(EXEC)
	./$(EXEC)
