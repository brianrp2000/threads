all: simplethread1 simplethread2

simplethread1: simplethread1.c
	gcc -Wall -std=gnu99 -pthread -o simplethread1 simplethread1.c

simplethread2: simplethread2.c
	gcc -Wall -std=gnu99  -pthread -o simplethread2 simplethread2.c

clean:
	rm simplethread1 simplethread2