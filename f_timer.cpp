#include "f_timer.h"

FrameTimer::FrameTimer(float t) :
	GameTimer(t),
	gameTime(0.f),
	gameFrames(0),
	frames(0) {}

FrameTimer::~FrameTimer() {}

void FrameTimer::start() {
	gameTime = al_current_time();
	this->GameTimer::start();
}

void FrameTimer::update() {
	++frames;
	if(al_current_time() - gameTime >= 1) {
		gameTime = al_current_time();
		gameFrames = frames;
		frames = 0;
	}
}

int FrameTimer::getFPS() const {
	return gameFrames;
}