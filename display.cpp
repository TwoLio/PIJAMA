class GameDisplay
{
	protected:
	ALLEGRO_BITMAP			*icon = nullptr;
	ALLEGRO_DISPLAY_MODE	displayMode;
	int						numDisplayModes;

	public:
	ALLEGRO_DISPLAY 		*display = nullptr;

	GameDisplay()
	{
		al_inhibit_screensaver(true);

		al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
		//al_set_new_display_flags(ALLEGRO_OPENGL_3_0);

		numDisplayModes = al_get_num_display_modes();
		al_get_display_mode(0, &displayMode);									//Risoluzione minima 'al_get_num_display_modes() - 1' /Risoluzione massima '0'

		display = al_create_display(displayMode.width, displayMode.height);
		al_set_window_title(display, "PIJAMA");
		//al_set_display_icon(display, icon);

		al_hide_mouse_cursor(display);
	}

	~GameDisplay()
	{
		al_show_mouse_cursor(display);
		al_destroy_display(display);
		al_inhibit_screensaver(false);
	}

	void draw()
	{
		al_flip_display();
	}

	int getScreenWidth()
	{
		return displayMode.width;
	}
	int getScreenHeight()
	{
		return displayMode.height;
	}

	int getDisplayWidth()
	{
		return al_get_display_width(display);
	}
	int getDisplayHeight()
	{
		return al_get_display_height(display);
	}

};
