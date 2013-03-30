CC = cc
BIN = main
OBJ = main.o Lib.o List.o Set.o Follow.o Scanner.o
CFLAGS = -g -std=c99

$(BIN): $(OBJ)
	$(CC) -o $(BIN) -std=c99 $(OBJ)
main.o:
	$(CC) -o main.o $(CFLAGS) -c main.c
Lib.o:
	$(CC) -o Lib.o $(CFLAGS) -c Lib.c
List.o:
	$(CC) -o List.o $(CFLAGS) -c List.c
Set.o:
	$(CC) -o Set.o $(CFLAGS) -c Set.c
Follow.o:
	$(CC) -o Follow.o $(CFLAGS) -c Follow.c
Scanner.o:
	$(CC) -o Scanner.o $(CFLAGS) -c Scanner.c
clean:
	rm $(BIN) $(OBJ)
