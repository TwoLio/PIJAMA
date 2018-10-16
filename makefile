NAME = PJEngine
OBJ = corePJ.o display.o game.o entities.o input.o map.o
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -lm -O2
PKG = `pkg-config --cflags --libs allegro-5 allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_dialog-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5`

PJEngine: $(OBJ)
	g++ -o $(NAME) $(OBJ) $(PKG)

.PHONY: rave clean sert

rave:
	g++ -MM *.cpp > dipendenze
clean:
	rm *.o
sert:
	rm $(NAME) *.o dipendenze