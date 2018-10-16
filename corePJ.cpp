#include "game.h"

int main()
{
	Game game;
	if (!game.init())
		return game.showMessage("Inizializzazione fallita a causa di un errore sconosciuto.", ALLEGRO_MESSAGEBOX_ERROR);

	game.run();

	return 0;
}