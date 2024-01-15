CC = g++
CFLAGS = -std=c++11 -Wall -Werror
LDFLAGS =
SOURCES = main.cpp Person.cpp Book.cpp Librarian.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = library

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

	

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)