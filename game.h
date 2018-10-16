#ifndef PIJAM_GAME_H
#define PIJAM_GAME_H 1

#include "config.h"
#include "display.h"
#include "input.h"
#include "map.h"

class Game {
private:
	ALLEGRO_EVENT_QUEUE		*eventQueue;

	GameConfig				*gameConfig;
	GameDisplay				*gameDisplay;
	GameInput				*gameInput;
	GameMap					*gameMap;

	Player					*p1;
	Bot						*f_bot;
	EnemyBot				*e_bot;

	bool					render;
	bool					exit;

	game_state				gameState;

	bool initAllegro();
	bool initConfig();
	bool initEventQueue();

public:
	Game();
	~Game();

	bool init();
	void run();

	game_state getState() const;
	void setState(game_state gameState);

	ALLEGRO_BITMAP*	createBitmapFromLayers(ALLEGRO_BITMAP *texture[], int n) const;
	int showMessage(const char *text, int flag, const char *button = nullptr) const;
};

#endif // PIJAM_GAME_H