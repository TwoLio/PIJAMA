#ifndef PIJAM_CONFIG_H
#define PIJAM_CONFIG_H 1

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_opengl.h>

class GameConfig {
private:
	ALLEGRO_CONFIG	*config;

public:
	GameConfig();
	~GameConfig();
	
	bool loadConfig(const char* path);
};

#endif