#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

class GameDisplay
{
	protected:
	//ALLEGRO_BITMAP		*icon = NULL;
	ALLEGRO_DISPLAY 		*display = NULL;
	ALLEGRO_DISPLAY_MODE	displayMode;
	int						numDisplayModes;

	public:
	GameDisplay()
	{
		al_inhibit_screensaver(true);

		al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

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
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	ALLEGRO_DISPLAY* getDisplay()
	{
		return display;
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
