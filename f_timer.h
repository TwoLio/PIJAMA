#ifndef PIJAM_FRAME_TIMER_H
#define PIJAM_FRAME_TIMER_H 1

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_opengl.h>

#include "timer.h"

class FrameTimer : public GameTimer {
private:
	float	gameTime;
	int		gameFrames, frames;

public:
	FrameTimer(float t = 60.f);
	~FrameTimer();

	void start();
	void update();

	int getFPS() const;
};

#endif
