TARGET = daim
objects = main.o st.o lex.yy.o y.tab.o ast.o
CC = gcc
INCLUDES = \

$(TARGET): $(objects)
	$(CC) -o $(TARGET) $(objects)

main.o: main.c st.h 
	$(CC) -c main.c

y.tab.h: parse.y
	bison -y -d -v parse.y

y.tab.c: parse.y
	bison -y -d -v parse.y

lex.yy.c: parse.l parse.y y.tab.h 
	flex parse.l

y.tab.o: y.tab.c
	$(CC) -c -g $*.c $(INCLUDES)

lex.y.o: lex.yy.c 
	$(CC) -c -g $*.c $(INCLUDES)

st.o: st.c st.h
	$(CC) -c st.c

ast.o: ast.c ast.h daim.h
	$(CC) -c ast.c

clean:
	rm -rf *.o lex.yy.c y.tab.*
