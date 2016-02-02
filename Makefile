CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lm -lcurl `pkg-config --cflags --libs opencv`
SOURCES=phych.cpp store_phych.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=phych

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o phych phych.jpg
