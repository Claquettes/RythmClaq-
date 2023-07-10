cc = g++
CFLAGS = -g -Wall -std=c++17
OBJDIR = obj
OBJS = $(OBJDIR)/main.o $(OBJDIR)/game.o $(OBJDIR)/note.o $(OBJDIR)/judgementLine.o $(OBJDIR)/main_menu.o $(OBJDIR)/editor.o $(OBJDIR)/song_selection_menu.o $(OBJDIR)/map.o $(OBJDIR)/pannel.o $(OBJDIR)/animations.o 
LIBS = -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2
Include = -I/usr/include/SDL2

all: dir bin/main

dir:
	mkdir -p bin
	mkdir -p $(OBJDIR)
	touch highscore.txt

bin/main: $(OBJS)
	$(cc) $(CFLAGS) $(OBJS) -o bin/main $(LIBS)

$(OBJDIR)/game.o: src/game.cpp  src/note.h src/judgementLine.h src/map.h
	$(cc) $(CFLAGS) -c src/game.cpp -o $(OBJDIR)/game.o $(Include)

$(OBJDIR)/main.o: main.cpp src/game.h src/main_menu.h
	$(cc) $(CFLAGS) -c main.cpp -o $(OBJDIR)/main.o $(Include)

$(OBJDIR)/main_menu.o: src/main_menu.cpp src/main_menu.h src/editor.h src/pannel.h src/animations.h 
	$(cc) $(CFLAGS) -c src/main_menu.cpp -o $(OBJDIR)/main_menu.o $(Include)

$(OBJDIR)/editor.o: src/editor.cpp src/editor.h 
	$(cc) $(CFLAGS) -c src/editor.cpp -o $(OBJDIR)/editor.o $(Include)

$(OBJDIR)/song_selection_menu.o: src/song_selection_menu.cpp src/song_selection_menu.h src/game.h src/map.h
	$(cc) $(CFLAGS) -c src/song_selection_menu.cpp -o $(OBJDIR)/song_selection_menu.o $(Include)

$(OBJDIR)/note.o: src/note.cpp src/note.h
	$(cc) $(CFLAGS) -c src/note.cpp -o $(OBJDIR)/note.o $(Include)

$(OBJDIR)/map.o: src/map.cpp src/map.h
	$(cc) $(CFLAGS) -c src/map.cpp -o $(OBJDIR)/map.o $(Include)

$(OBJDIR)/judgementLine.o: src/judgementLine.cpp src/judgementLine.h
	$(cc) $(CFLAGS) -c src/judgementLine.cpp -o $(OBJDIR)/judgementLine.o $(Include)

$(OBJDIR)/pannel.o: src/pannel.cpp src/pannel.h
	$(cc) $(CFLAGS) -c src/pannel.cpp -o $(OBJDIR)/pannel.o $(Include)

$(OBJDIR)/animations.o: src/animations.cpp src/animations.h src/pannel.h src/main_menu.h
	$(cc) $(CFLAGS) -c src/animations.cpp -o $(OBJDIR)/animations.o $(Include)



clean:
	rm -rf $(OBJDIR)/*.o main
