cc = g++
CFLAGS = -g -Wall -std=c++11
OBJDIR = obj
OBJS = $(OBJDIR)/main.o $(OBJDIR)/game.o $(OBJDIR)/note.o $(OBJDIR)/judgementLine.o
LIBS = -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2
Include = -I/usr/include/SDL2

all: dir bin/main

dir:
	mkdir -p bin
	mkdir -p $(OBJDIR)
	touch highscore.txt

bin/main: $(OBJS)
	$(cc) $(CFLAGS) $(OBJS) -o main $(LIBS)

$(OBJDIR)/game.o: src/game.cpp  src/note.h src/judgementLine.h
	$(cc) $(CFLAGS) -c src/game.cpp -o $(OBJDIR)/game.o $(Include)

$(OBJDIR)/main.o: main.cpp src/game.h
	$(cc) $(CFLAGS) -c main.cpp -o $(OBJDIR)/main.o $(Include)

$(OBJDIR)/note.o: src/note.cpp src/note.h
	$(cc) $(CFLAGS) -c src/note.cpp -o $(OBJDIR)/note.o $(Include)

$(OBJDIR)/judgementLine.o: src/judgementLine.cpp src/judgementLine.h
	$(cc) $(CFLAGS) -c src/judgementLine.cpp -o $(OBJDIR)/judgementLine.o $(Include)

clean:
	rm -rf $(OBJDIR)/*.o main
