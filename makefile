OBJ = corePJ.o functions.o display.o game.o
FLAGS = -Wall -std=c++11 -lm -O2
NAME = -o PJEngine
PKG = `pkg-config --cflags --libs allegro-5 allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_dialog-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5`

PJEngine: $(OBJ)
	g++ $(FLAGS) $(NAME) $(OBJ) $(PKG)

corePJ.o: corePJ.cpp game.cpp functions.h
functions.o: functions.cpp functions.h globals.h
display.o: display.cpp entities.cpp
game.o: game.cpp display.cpp functions.h

clean:
	rm *.o
