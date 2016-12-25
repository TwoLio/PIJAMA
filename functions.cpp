#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

#define DISPLAY	al_get_current_display()

bool initAllegro()
{
	if (!al_init())
		return false;

	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_native_dialog_addon();

	return true;
}

void changeState(int &state, int newState)
{
	state = newState;
}

ALLEGRO_BITMAP*	createBitmapFromLayers(ALLEGRO_BITMAP *texture[], int n)
{
	ALLEGRO_BITMAP *bmp = al_create_bitmap(al_get_bitmap_width(texture[0]), al_get_bitmap_height(texture[0]));
	al_set_target_bitmap(bmp);

	for (int i = 0; i < n; i++)
		al_draw_bitmap(texture[i], 0, 0, 0);

	al_save_bitmap("gfx/bmp/bitmap.png", bmp);
	al_set_target_bitmap(al_get_backbuffer(DISPLAY));

	return bmp;
}

int showMessageBox(const char *text, int flag, const char *button = NULL)
{
	switch (flag)
	{
	case ALLEGRO_MESSAGEBOX_WARN:
		return al_show_native_message_box(DISPLAY, "Attenzione", "Potrebbe esserci un problema!", text, button, ALLEGRO_MESSAGEBOX_WARN);
	case ALLEGRO_MESSAGEBOX_ERROR:
		return al_show_native_message_box(DISPLAY, "Errore Allegro 5", "Errore inizializzazione!", text, button, ALLEGRO_MESSAGEBOX_ERROR);
	case ALLEGRO_MESSAGEBOX_QUESTION:
		return al_show_native_message_box(DISPLAY, "Domanda", "Scegliere come procedere.", text, button, ALLEGRO_MESSAGEBOX_QUESTION);
	case ALLEGRO_MESSAGEBOX_OK_CANCEL:
		return al_show_native_message_box(DISPLAY, "Ok / Cancella", "Cosa vuoi fare?", text, button, ALLEGRO_MESSAGEBOX_OK_CANCEL);
	case ALLEGRO_MESSAGEBOX_YES_NO:
		return al_show_native_message_box(DISPLAY, "Si / No", "Scelta.", text, button, ALLEGRO_MESSAGEBOX_YES_NO);
	default:
		return al_show_native_message_box(DISPLAY, "Errore", "Errore del programma", text, button, ALLEGRO_MESSAGEBOX_ERROR);
	}

	return -1;																	// -1: Errore // 0: Chiusura // 1: Ok/Yes // 2: Cancel/No
}
