OBJ = PiJama.o display.o function.o
FLAGS = -Wall -std=c++0x -lGL -lm
PKG = `pkg-config --cflags --libs allegro-5 allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_dialog-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5`

PiJama: $(OBJ)
	g++ $(FLAGS) -o PiJama $(OBJ) $(PKG)

PiJama.o: PiJama.cpp global.h function.h object.cpp display.cpp
	g++ -c PiJama.cpp
function.o: function.cpp function.h
	g++ -c function.cpp
object.o: object.cpp
	g++ -c object.cpp
display.o: display.cpp
	g++ -c display.cpp

clean:
	rm *.o
