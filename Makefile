CC = cc
BIN = main
OBJ = main.o Lib.o List.o Set.o
CFLAGS = -std=c99

$(BIN): $(OBJ)
	$(CC) -g -o $(BIN) -std=c99 $(OBJ)
main.o:
	$(CC) -o main.o $(CFLAGS) -c main.c
Lib.o:
	$(CC) -o Lib.o $(CFLAGS) -c Lib.c
List.o:
	$(CC) -o List.o $(CFLAGS) -c List.c
Set.o:
	$(CC) -o Set.o $(CFLAGS) -c Set.c
clean:
	rm $(BIN) $(OBJ)
