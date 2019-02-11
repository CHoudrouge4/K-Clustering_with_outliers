CC = g++
CFLAGS = -g -Wall
C = -c
VERSION = -std=c++14
OUTPUT  = co.exe
SOURCES = main.cpp FRS.cpp kco.cpp  grid.cpp
OBJECTS = $(SOURCES:.cpp=.o)
REMOVE  = co.exe *.o

$(OUTPUT): $(OBJECTS)
	$(CC) $(CFLAGS) $(VERSION) $(OBJECTS) -o $(OUTPUT)
main.o: $(SOURCES)
	$(CC) $(VERSION) $(C) $(CFLAGS) main.cpp
kco.o: kco.cpp kco.h
	$(CC) $(VERSION) $(C) $(CFLAGS) kco.cpp
FRS.o: FRS.cpp FRS.h
	$(CC) $(VERSION) $(C) $(CFLAGS) FRS.cpp
grid.o: grid.cpp grid.h
	$(CC) $(VERSION) $(C) $(CFLAGS) grid.cpp
.PHONY: clean
clean:
	@rm -rf $(REMOVE)
