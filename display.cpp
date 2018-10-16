#include "display.h"

// TODO Fix icon

GameDisplay::GameDisplay(const char* title) :
	display(nullptr),
	nDisplayModes(al_get_num_display_modes()),
	timerFPS(60.f),
	timerAnim(8.f),
	scale(1.f) {
	al_inhibit_screensaver(true);
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

	al_get_display_mode(0, &displayMode);									//Risoluzione minima 'al_get_num_display_modes() - 1' /Risoluzione massima '0'
	display = al_create_display(displayMode.width, displayMode.height);

	//this->icon = al_load_bitmap("gfx/bmp/sun32.png");
	//al_set_display_icon(this->display, this->icon);
	al_set_window_title(display, title);

	al_reserve_samples(DSP_SOUNDS);
	this->sound[0] = al_load_sample("sfx/relax.wav");
	this->sound[1] = al_load_sample("sfx/frogs.wav");
	this->sound[2] = al_load_sample("sfx/sea.flac");

	for (int i = 0; i < DSP_SOUNDS; ++i) {
		this->soundInstance[i] = al_create_sample_instance(this->sound[i]);
		al_set_sample_instance_playmode(this->soundInstance[i], ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(this->soundInstance[i], al_get_default_mixer());
	}

	this->font[0] = al_load_ttf_font("gfx/font/amsterdam.ttf", 36, 0);
	this->font[1] = al_load_ttf_font("gfx/font/amsterdam.ttf", 15, 0);

	al_hide_mouse_cursor(this->display);
}

GameDisplay::~GameDisplay() {
	al_show_mouse_cursor(display);
	for (int i = 0; i < DSP_FONTS; ++i)
		al_destroy_font(font[i]);
	for (int i = 0; i < DSP_SOUNDS; ++i) {
		al_destroy_sample_instance(soundInstance[i]);
		al_destroy_sample(sound[i]);
	}
	//al_destroy_bitmap(this->icon);
	al_destroy_display(display);
	al_inhibit_screensaver(false);
}

void GameDisplay::render() {
	al_draw_textf(font[0], al_map_rgb(255, 255, 0), cameraX + 10, cameraY + 10, ALLEGRO_ALIGN_LEFT, "%i", timerFPS.getFPS());
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void GameDisplay::start() {
	al_play_sample_instance(this->soundInstance[0]);
	timerFPS.start();
	timerAnim.start();
//		al_play_sample_instance(this->soundInstance[1]);
//		al_play_sample_instance(this->soundInstance[2]);
//		al_play_sample(this->sound[0], 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_LOOP, NULL);
}

FrameTimer& GameDisplay::getFramesTimer() {
	return timerFPS;
}

GameTimer& GameDisplay::getAnimationTimer() {
	return timerAnim;
}

ALLEGRO_DISPLAY* GameDisplay::getDisplay() {
	return this->display;
}

ALLEGRO_FONT* GameDisplay::getFont(int i) {
	return this->font[i];
}

int GameDisplay::getScreenWidth() {
	return this->displayMode.width;
}

int GameDisplay::getScreenHeight() {
	return this->displayMode.height;
}

int GameDisplay::getDisplayWidth() {
	return al_get_display_width(this->display);
}

int GameDisplay::getDisplayHeight() {
	return al_get_display_height(this->display);
}

int GameDisplay::getCameraX() {
	return cameraX;
}

int GameDisplay::getCameraY() {
	return cameraY;
}

float GameDisplay::getScale() {
	return scale;
}

void GameDisplay::setScale(float s) {
	scale = s;
}

void GameDisplay::updateCamera(GameObject *obj) {
	updateCamera(obj->getX(), obj->getY(), obj->getWidthSize(), obj->getHeightSize());
}

void GameDisplay::updateCamera(float x, float y, float sizeW, float sizeH) {
	this->cameraX = -(getScreenWidth()/2) + (x + sizeW/2);
	this->cameraY = -(getScreenHeight()/2) + (y + sizeH/2);

	if (this->cameraX < 0)
		this->cameraX = 0;
	if (this->cameraY < 0)
		this->cameraY = 0;

	al_identity_transform(&camera);
	al_translate_transform(&camera, -(x - sizeW/2), -y);
	al_scale_transform(&camera, scale, scale);
	al_translate_transform(&camera, -this->cameraX + (x+sizeW/2), -this->cameraY + (y+sizeH/2));
	al_use_transform(&camera);
}