#include "timer.h"

GameTimer::GameTimer(float t) :
	timer(nullptr),
	time(t) {
	timer = al_create_timer(1.0f / time);
}

GameTimer::~GameTimer() {
	al_destroy_timer(timer);
}

void GameTimer::start() {
	al_start_timer(timer);
}

ALLEGRO_TIMER* GameTimer::get() const {
	return timer;
}