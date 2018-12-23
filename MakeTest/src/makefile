CXXFLAGS = -O0 -Wall
CCFLAGS = -O0 -Wall

EXECFILE = test
OUTPUT = ../bin/$(EXECFILE)
OBJECTS = a.o b.o test.o

all: executable

.PHONY:debug
debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: OUTPUT = ../debug/$(EXECFILE)
debug: executable

CC = cc $(CCFLAGS)
CXX = g++ $(CXXFLAGS)

executable: $(OBJECTS)
	$(CC) -o $(OUTPUT) $^

#编译所有的.c 文件为 .o
.c.o: 
	$(CC) -c $<

clean:
	rm -rf *.o