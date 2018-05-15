CC=g++
CFLAGS=-lncurses -g
DEPS = caves.h line.h slime.h constants.h map.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

field: field.o caves.o line.o slime.o constants.o map.o
	$(CC) -o field field.o caves.o line.o slime.o constants.o map.o $(CFLAGS)

clean:
	rm field *.o  
