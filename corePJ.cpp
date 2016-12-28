#include "game.cpp"

int main(int argc, char **argv)
{
	Game	*game = new Game();
	if (!game->init())
		return game->showMessageBox("Inizializzazione fallita a causa di un errore sconosciuto.", ALLEGRO_MESSAGEBOX_ERROR);

	game->run();

	delete game;
	return 0;
}
