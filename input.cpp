#include "globals.h"

class GameInput
{
	protected:
	ALLEGRO_KEYBOARD_STATE	keyState;
	bool					keys[ALLEGRO_KEY_MAX];

	ALLEGRO_MOUSE_STATE		mouseState;
	unsigned int			numMouseAxes;
	unsigned int			numMouseButtons;

/*	ALLEGRO_JOYSTICK		*joystick;
	ALLEGRO_JOYSTICK_STATE	joyState;
	unsigned int			numJoysticks;
	unsigned int			numButtons;
	unsigned int			numSticks;
*/
	public:
	GameInput()
	{
		al_install_mouse();
		al_install_keyboard();
//		al_install_joystick();

		for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
			this->keys[i] = false;

		this->numMouseButtons = al_get_mouse_num_buttons();
		this->numMouseAxes = al_get_mouse_num_axes();

//		if (al_is_joystick_installed())
//			this->initJoystick();
	}

	~GameInput()	{}

	bool getKey(int keyCode)
	{
		return this->keys[keyCode];
	}

	void setKey(int keyCode, bool keyFlag)
	{
		this->keys[keyCode] = keyFlag;
	}	

	bool keyDown(int keyCode)
	{
		return al_key_down(&keyState, keyCode);
	}

	void updateKeyboardState()
	{
		al_get_keyboard_state(&keyState);
	}

	ALLEGRO_KEYBOARD_STATE* getKeyState()
	{
		return &keyState;
	}

	int getMouseStateAxis(int axis)				//	0: x-axis	1: y-axis	2: z-axis	3: w-axis
	{
		return al_get_mouse_state_axis(&mouseState, axis);
	}

	bool mouseButtonDown(int button)
	{
		return al_mouse_button_down(&mouseState, button);
	}

	void updateMouseState()
	{
		al_get_mouse_state(&mouseState);
	}

	ALLEGRO_MOUSE_STATE* getMouseState()
	{
		return &mouseState;
	}

/*	void initJoystick()
	{
		this->numJoysticks = al_get_num_joysticks();
//		this->joystick = new ALLEGRO_JOYSTICK* [this->numJoysticks];
//		for (int i = 0; i < this->numJoysticks; i++)
//			this->joystick[i] = al_get_joystick(i);
		this->joystick = al_get_joystick(0);
		this->numSticks = al_get_joystick_num_sticks(joystick);
		this->numButtons = al_get_joystick_num_buttons(joystick);
	}

	void reconfigJoystick()
	{
		if (al_reconfigure_joysticks())
			this->initJoystick();
	}

	bool getJoystickActive()
	{
		return al_get_joystick_active(joystick);
	}

	void updateJoystickState()
	{
		al_get_joystick_state(joystick, &joyState);
	}

	ALLEGRO_JOYSTICK_STATE* getJoystickState()
	{
		return &joyState;
	}
*/
};
