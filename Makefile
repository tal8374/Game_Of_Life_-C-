gameOfLife: main.o gameIO.o twoPlayer.o defs.o zeroPlayer.o
	gcc main.o gameIO.o twoPlayer.o defs.o zeroPlayer.o -o gameOfLife

main.o: main.c defs.h
	gcc -c main.c

gameIO.o: gameIO.c defs.h
	gcc -c gameIO.c

twoPlayer.o: twoPlayer.c defs.h
	gcc -c twoPlayer.c

zeroPlayer.o: zeroPlayer.c defs.h
	gcc -c zeroPlayer.c

defs.o: defs.c defs.h
	gcc -c defs.c

clean: 
	rm -f *.o
