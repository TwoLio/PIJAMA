#ifndef PIJAM_TIMER_H
#define PIJAM_TIMER_H 1

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_opengl.h>

class GameTimer {
private:
	ALLEGRO_TIMER	*timer;
	float			time;

public:
	GameTimer(float t);
	virtual ~GameTimer();

	void start();

	ALLEGRO_TIMER* get() const;
};

#endif