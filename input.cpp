#include "input.h"

GameInput::GameInput() :
	nMouseButtons(al_get_mouse_num_buttons()),
	nMouseAxis(al_get_mouse_num_axes()) {
	for (int i = 0; i < ALLEGRO_KEY_MAX; ++i)
		keys[i] = false;
}

GameInput::~GameInput() {}

bool GameInput::getKey(int keyCode) {
	return keys[keyCode];
}

void GameInput::setKey(int keyCode, bool keyFlag) {
	keys[keyCode] = keyFlag;
}	

bool GameInput::keyDown(int keyCode) {
	return al_key_down(&keyState, keyCode);
}

bool GameInput::buttonDown(int button) {
	return al_mouse_button_down(&mouseState, button);
}

void GameInput::updateKeyboard() {
	al_get_keyboard_state(&keyState);
}

void GameInput::updateMouse() {
	al_get_mouse_state(&mouseState);
}

int GameInput::getMouseStateAxis(int axis) {
	return al_get_mouse_state_axis(&mouseState, axis);
}

ALLEGRO_KEYBOARD_STATE& GameInput::getKeyState() {
	return keyState;
}

ALLEGRO_MOUSE_STATE& GameInput::getMouseState() {
	return mouseState;
}