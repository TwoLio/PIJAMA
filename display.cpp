#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>


// TODO Fix icon

class GameDisplay
{
	protected:
	ALLEGRO_DISPLAY 		*display;
	ALLEGRO_DISPLAY_MODE	displayMode;
	int						numDisplayModes;

	ALLEGRO_TIMER			*timerFPS;
	float					gameTime;
	int						frames,	gameFPS;

	ALLEGRO_FONT			*font[2];
	ALLEGRO_SAMPLE			*sound;
	//ALLEGRO_BITMAP			*icon;

	public:
	GameDisplay(const float FPS)
	{
		al_reserve_samples(1);
		sound = al_load_sample("sfx/relax.wav");
		//icon = al_load_bitmap("gfx/sheet/sun32.png");

		font[0] = al_load_ttf_font("gfx/font/amsterdam.ttf", 36, 0);
		font[1] = al_load_ttf_font("gfx/font/amsterdam.ttf", 15, 0);

		timerFPS = al_create_timer(1.0f / FPS);
		gameTime = 0.0f;
		frames = 0;
		gameFPS = 0;

		al_inhibit_screensaver(true);
		al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

		numDisplayModes = al_get_num_display_modes();
		al_get_display_mode(0, &displayMode);									//Risoluzione minima 'al_get_num_display_modes() - 1' /Risoluzione massima '0'
		display = al_create_display(displayMode.width, displayMode.height);

		//al_set_display_icon(display, icon);
		al_set_window_title(display, "PiJam Engine (version A)");
		al_hide_mouse_cursor(display);
	}

	~GameDisplay()
	{
		al_show_mouse_cursor(display);
		for (int i = 0; i < 2; i++)
			al_destroy_font(font[i]);
		//al_destroy_bitmap(icon);
		al_destroy_sample(sound);
		al_destroy_timer(timerFPS);
		al_destroy_display(display);
		al_inhibit_screensaver(false);
	}

	void draw()
	{
		al_draw_textf(font[0], al_map_rgb(255, 255, 0), 10, 70,
					ALLEGRO_ALIGN_LEFT, "%i", gameFPS);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	void updateFPS()
	{
		frames++;
		if(al_current_time() - gameTime >= 1)
		{
			gameTime = al_current_time();
			gameFPS = frames;
			frames = 0;
		}
	}

	void startSFX()
	{
		al_play_sample(sound, 1.0f, 0.0f, 1.0f,
					ALLEGRO_PLAYMODE_LOOP, NULL);
	}

	void startTimerFPS()
	{
		gameTime = al_current_time();
		al_start_timer(timerFPS);
	}

	ALLEGRO_DISPLAY* getDisplay()
	{
		return display;
	}

	ALLEGRO_TIMER* getTimerFPS()
	{
		return timerFPS;
	}

	ALLEGRO_FONT* getFont(int i)
	{
		return font[i];
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
