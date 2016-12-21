#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

class GameInput
{
	protected:
	ALLEGRO_KEYBOARD_STATE	keyState;
	ALLEGRO_MOUSE_STATE		mouseState;

	bool					keys[ALLEGRO_KEY_MAX];
	unsigned int			mouseNumButtons;

	public:
	GameInput()
	{
		for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
			this->keys[i] = false;

		this->mouseNumButtons = al_get_mouse_num_buttons();
	}

	bool getKey(int keyCode)
	{
		return this->keys[keyCode];
	}

	void setKey(int keyCode, bool keyFlag)
	{
		this->keys[keyCode] = keyFlag;
	}	

	void getKeyState()
	{
		al_get_keyboard_state(&keyState);
	}

	void getMouseState()
	{
		al_get_mouse_state(&mouseState);
	}

	bool keyDown(int keyCode)
	{
		return al_key_down(&keyState, keyCode);
	}

	bool mouseButtonDown(int button)
	{
		return al_mouse_button_down(&mouseState, button);
	}

	int getMouseStateAxis(int axis)				//	0: x-axis	1: y-axis	2: z-axis	3: w-axis
	{
		return al_get_mouse_state_axis(&mouseState, axis);
	}
};
