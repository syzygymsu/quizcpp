cc = gcc
CFLAGS = -c 
haff: main.o tree.o file1.o print.o file6.o file7.o file8.o list.o 
		${cc} main.o tree.o file1.o print.o  file6.o file7.o file8.o list.o  -o  haff
main.o: main.c
		${cc} ${CFLAGS} main.c
tree.o: tree.c
		${cc} ${CFLAGS}tree.c
file1.o: file1.c
		${cc} ${CFLAGS} file1.c

print.o: print.c
		${cc} ${CFLAGS}print.c

file6.o: file6.c
		${cc} ${CFLAGS} file6.c
file7.o: file7.c
		${cc} ${CFLAGS} file7.c
file8.o: file8.c
		${cc} ${CFLAGS} file8.c

list.o: list.c
		${cc} ${CFLAGS} list.c

