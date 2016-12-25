#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_opengl.h>

#include "game.cpp"

int main(int argc, char **argv)
{
	Game	*game = new Game();
	if (!game->init())
		return showMessageBox("Inizializzazione fallita a causa di un errore sconosciuto.", ALLEGRO_MESSAGEBOX_ERROR);

	game->run();

	delete game;
	return 0;
}
