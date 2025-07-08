flags = -Wall -O2 -std=c2x
objs = word-swapper.o
target = wswap

all: clean1 ${target} clean2

${target}: $(objs)
	gcc ${flags} -o $@ $^

word-swapper.o: word-swapper.c
	gcc ${flags} -c $^

clean1:
	rm -f ${target}

clean2:
	rm -f *.o
