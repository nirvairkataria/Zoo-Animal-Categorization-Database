katariaNirvairA1: katariaNirvairA1.o katariaNirvairA1Main.o
	gcc katariaNirvairA1.o katariaNirvairA1Main.o -o katariaNirvairA1 -lm
katariaNirvairA1.o: katariaNirvairA1.c givenA1.h
	gcc -Wall -std=c99 -c katariaNirvairA1.c
katariaNirvairA1Main.o: katariaNirvairA1Main.c givenA1.h
	gcc -Wall -std=c99 -c katariaNirvairA1Main.c
clean:
	rm *.o katariaNirvairA1