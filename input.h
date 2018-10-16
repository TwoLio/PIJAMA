#ifndef PIJAM_INPUT_H
#define PIJAM_INPUT_H 1

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_opengl.h>

class GameInput {
private:
	ALLEGRO_KEYBOARD_STATE	keyState;
	ALLEGRO_MOUSE_STATE		mouseState;

	bool					keys[ALLEGRO_KEY_MAX];
	unsigned int			mouseNumButtons;
	unsigned int			mouseNumAxis;

public:
	GameInput();
	~GameInput();

	bool getKey(int keyCode);
	void setKey(int keyCode, bool keyFlag);

	bool keyDown(int keyCode);
	bool buttonDown(int button);
	
	void updateKeyboard();
	void updateMouse();

	int getMouseStateAxis(int axis);	//	0: x-axis, 1: y-axis, 2: z-axis, 3: w-axis
	
	ALLEGRO_KEYBOARD_STATE& getKeyState();
	ALLEGRO_MOUSE_STATE& getMouseState();
};

#endif // PIJAM_INPUT_H