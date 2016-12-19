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
	static const float		FPS = 60.;

	ALLEGRO_DISPLAY 		*display;
	ALLEGRO_DISPLAY_MODE	displayMode;
	int						numDisplayModes;

	ALLEGRO_TIMER			*timerFPS;
	float					gameTime;
	int						frames,	gameFPS;

	ALLEGRO_TIMER			*timerAnim;
	float					animFPS;

	ALLEGRO_FONT			*font[2];
	ALLEGRO_SAMPLE			*sound[3];
	ALLEGRO_SAMPLE_INSTANCE	*soundInstance[3];
//	ALLEGRO_BITMAP			*icon;

	public:
	GameDisplay()
	{
		al_inhibit_screensaver(true);
		al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

		this->numDisplayModes = al_get_num_display_modes();
		al_get_display_mode(0, &displayMode);									//Risoluzione minima 'al_get_num_display_modes() - 1' /Risoluzione massima '0'
		this->display = al_create_display(this->displayMode.width, this->displayMode.height);

		//al_set_display_icon(this->display, this->icon);
		al_set_window_title(this->display, "PiJam Engine (version A)");

		al_reserve_samples(3);
		this->sound[0] = al_load_sample("sfx/relax.wav");
		this->sound[1] = al_load_sample("sfx/frogs.wav");
		this->sound[2] = al_load_sample("sfx/sea.flac");

		for (int i = 0; i < 3; i++)
		{
			this->soundInstance[i] = al_create_sample_instance(this->sound[i]);
			al_set_sample_instance_playmode(this->soundInstance[i], ALLEGRO_PLAYMODE_LOOP);
			al_attach_sample_instance_to_mixer(this->soundInstance[i], al_get_default_mixer());
		}

		//icon = al_load_bitmap("gfx/sheet/sun32.png");

		this->font[0] = al_load_ttf_font("gfx/font/amsterdam.ttf", 36, 0);
		this->font[1] = al_load_ttf_font("gfx/font/amsterdam.ttf", 15, 0);

		this->animFPS = 10.;
		this->timerAnim = al_create_timer(1.0 / this->animFPS);

		this->timerFPS = al_create_timer(1.0f / this->FPS);
		this->gameTime = 0.0f;
		this->frames = 0;
		this->gameFPS = 0;

		al_hide_mouse_cursor(this->display);
	}

	~GameDisplay()
	{
		al_show_mouse_cursor(this->display);
		for (int i = 0; i < 2; i++)
			al_destroy_font(this->font[i]);
		for (int i = 0; i < 3; i++)
		{
			al_destroy_sample_instance(this->soundInstance[i]);
			al_destroy_sample(this->sound[i]);
		}
		al_destroy_timer(this->timerFPS);
		al_destroy_timer(this->timerAnim);
		//al_destroy_bitmap(this->icon);
		al_destroy_display(this->display);
		al_inhibit_screensaver(false);
	}

	void draw()
	{
		al_draw_textf(this->font[0], al_map_rgb(255, 255, 0), 10, 70, ALLEGRO_ALIGN_LEFT, "%i", this->gameFPS);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	void updateFPS()
	{
		this->frames++;
		if(al_current_time() - this->gameTime >= 1)
		{
			this->gameTime = al_current_time();
			this->gameFPS = this->frames;
			this->frames = 0;
		}
	}

	void startSFX()
	{
		al_play_sample_instance(this->soundInstance[0]);
//		al_play_sample_instance(this->soundInstance[1]);
//		al_play_sample(this->sound[0], 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_LOOP, NULL);
	}

	void startTimerFPS()
	{
		this->gameTime = al_current_time();
		al_start_timer(this->timerFPS);
	}

	void startTimerAnimation()
	{
		al_start_timer(this->timerAnim);
	}

	ALLEGRO_DISPLAY* getDisplay()
	{
		return this->display;
	}

	ALLEGRO_TIMER* getTimerFPS()
	{
		return this->timerFPS;
	}

	ALLEGRO_TIMER* getTimerAnimation()
	{
		return this->timerAnim;
	}

	ALLEGRO_FONT* getFont(int i)
	{
		return this->font[i];
	}

	int getScreenWidth()
	{
		return this->displayMode.width;
	}

	int getScreenHeight()
	{
		return this->displayMode.height;
	}

	int getDisplayWidth()
	{
		return al_get_display_width(this->display);
	}

	int getDisplayHeight()
	{
		return al_get_display_height(this->display);
	}
};
