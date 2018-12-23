CXXFLAGS = -O0 -Wall
CCFLAGS = -O0 -Wall

EXECFILE = 2048-Rev
OUTPUT = ../bin/$(EXECFILE)
OBJECTS = myheader.o author.o mysort.o myalgorithm.o antidebug.o 2048-Rev.o

all: executable

.PHONY:debug
debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: OUTPUT = ../debug/$(EXECFILE)
debug: executable

.PHONY:hard
hard: CXXFLAGS += -s
hard: CCFLAGS += -s
hard: OUTPUT = ../bin/$(EXECFILE)
hard: executable

CC = cc $(CCFLAGS)
CXX = g++ $(CXXFLAGS)

executable: $(OBJECTS)
	$(CC) -o $(OUTPUT) $^

#编译所有的.c 文件为 .o
.c.o: 
	$(CC) -c $<

clean:
	rm -rf *.o