#ifndef PIJAM_DISPLAY_H
#define PIJAM_DISPLAY_H 1

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_opengl.h>

#include "entities.cpp"

class GameDisplay {
private:
	static const int		DSP_FONTS = 2;
	static const int		DSP_SOUNDS = 3;
	constexpr static const float		FPS = 60.;

	ALLEGRO_DISPLAY 		*display;
	ALLEGRO_DISPLAY_MODE	displayMode;
	int						nDisplayModes;

	float					gameTime;
	int						frames,	gameFPS;
	ALLEGRO_TIMER			*timerFPS;

	float					animFrames;		//	Increments for running animation, decrements for walking animation
	ALLEGRO_TIMER			*timerAnim;

	ALLEGRO_FONT			*font[DSP_FONTS];
	ALLEGRO_SAMPLE			*sound[DSP_SOUNDS];
	ALLEGRO_SAMPLE_INSTANCE	*soundInstance[DSP_SOUNDS];
//	ALLEGRO_BITMAP			*icon;

	int					cameraX;
	int					cameraY;
	float				scale;
	ALLEGRO_TRANSFORM	camera;

public:
	GameDisplay(const char* title);
	~GameDisplay();

	void render();
	void updateFPS();

	void startSFX();
	void startTimerFPS();
	void startTimerAnimation();

	ALLEGRO_DISPLAY* getDisplay();
	ALLEGRO_TIMER* getTimerFPS();
	ALLEGRO_TIMER* getTimerAnimation();
	ALLEGRO_FONT* getFont(int i);

	int getScreenWidth();
	int getScreenHeight();

	int getDisplayWidth();
	int getDisplayHeight();

	int getCameraX();
	int getCameraY();

	float getScale();
	void setScale(float s = 1.f);

	void updateCamera(GameObject* obj);
	void updateCamera(float x, float y, float sizeW, float sizeH);
};

#endif // PIJAM_DISPLAY_H