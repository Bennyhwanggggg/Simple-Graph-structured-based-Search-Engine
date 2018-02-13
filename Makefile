CC = gcc

CFLAGS = -g -Wall -Werror

TARGET = executable

OBJ = readData.o charOp.o LinkedList.o Graph.o BSTree.o AdjList.o pagerank.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o pagerank $(OBJ)
