cc = g++
CFLAGS = -g -Wall -std=c++11
OBJDIR = obj
OBJS = $(OBJDIR)/main.o $(OBJDIR)/game.o
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
Include = -I/usr/include/SDL2

all: dir bin/main

dir:
	mkdir -p bin
	mkdir -p $(OBJDIR)

bin/main: $(OBJS)
	$(cc) $(CFLAGS) $(OBJS) -o main $(LIBS)

$(OBJDIR)/game.o: src/game.cpp
	$(cc) $(CFLAGS) -c src/game.cpp -o $(OBJDIR)/game.o $(Include)

$(OBJDIR)/main.o: main.cpp src/game.h
	$(cc) $(CFLAGS) -c main.cpp -o $(OBJDIR)/main.o $(Include)

clean:
	rm -rf $(OBJDIR)/*.o main
