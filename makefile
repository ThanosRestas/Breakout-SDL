CC=g++
CFLAGS = -O0 -Wall -pedantic -w -g
OBJECTS = ball.o timer.o player.o globals.o tile.o
LIBS = -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer 

all:breakout

breakout:main.cpp $(OBJECTS)
	$(CC) main.cpp $(OBJECTS) $(LIBS) $(CLFAGS) -o breakout

globals.o:globals.cpp globals.h
	$(CC) -c globals.cpp $(CFLAGS)

tile.o:tile.cpp tile.h
	$(CC) -c tile.cpp $(CFLAGS)

player.o:player.cpp player.h globals.o
	$(CC) -c player.cpp $(CFLAGS)

ball.o:ball.cpp ball.h globals.o
	$(CC) -c ball.cpp $(CFLAGS)

timer.o:timer.cpp timer.h globals.o
	$(CC) -c timer.cpp $(CFLAGS)
clean:
	rm *.o breakout
	

	
	
	
	



