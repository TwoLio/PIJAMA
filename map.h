#ifndef PIJAM_MAP_H
#define PIJAM_MAP_H 1

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_opengl.h>

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "state.h"

class GameMap {
private:
	ALLEGRO_BITMAP*					mapTile;
	int								size;
	load_state						loadState;
	std::vector< std::vector<int> >	map;

public:
	GameMap();
	~GameMap();

	bool loadRT(const char *path);		//	Run-time loading for debugging
	bool load(const char *path);

	void render(int startX = 0, int startY = 0);
};

#endif // PIJAM_MAP_H