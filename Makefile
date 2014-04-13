TARGET = daim
objects = main.o st.o lex.yy.o y.tab.o ast.o dm_memory.o
CC = gcc
INCLUDES = \

$(TARGET): $(objects)
	$(CC) -o $(TARGET) $(objects)

main.o: st.h dm_memory.h
	$(CC) -c main.c

y.tab.h: parse.y
	bison -y -d -v parse.y

y.tab.c: parse.y
	bison -y -d -v parse.y

lex.yy.c: parse.l parse.y y.tab.h 
	flex parse.l

y.tab.o: ast.h st.h dm_memory.h
	$(CC) -c -g $*.c $(INCLUDES)

lex.y.o: lex.yy.c 
	$(CC) -c -g $*.c $(INCLUDES)

st.o: 
	$(CC) -c st.c

ast.o: daim.h st.h dm_memory.h
	$(CC) -c ast.c

dm_memory.o: st.h
	$(CC) -c dm_memory.c

clean:
	rm -rf *.o lex.yy.c y.tab.*
