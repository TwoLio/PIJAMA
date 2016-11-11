#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

bool initAllegro()
{
	if (!al_init())
		return false;

	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_init_native_dialog_addon();

	return true;
}


void changeState(int &state, int newState)
{
	state = newState;
}

int showMessageBox(const char *text, int flag, const char *button = NULL)
{
	switch (flag)
	{
	case ALLEGRO_MESSAGEBOX_WARN:
		std::cerr << text << std::endl;
		return al_show_native_message_box(al_get_current_display(),
										"Attenzione",
										"Potrebbe esserci un problema!",
										text,
										button,
										ALLEGRO_MESSAGEBOX_WARN);
	case ALLEGRO_MESSAGEBOX_ERROR:
		std::cerr << text << std::endl;
		return al_show_native_message_box(al_get_current_display(),
										"Errore Allegro 5",
										"Errore inizializzazione!",
										text,
										button,
										ALLEGRO_MESSAGEBOX_ERROR);
	case ALLEGRO_MESSAGEBOX_QUESTION:
		std::cerr << text << std::endl;
		return al_show_native_message_box(al_get_current_display(),
										"Domanda",
										"Scegliere come procedere.",
										text,
										button,
										ALLEGRO_MESSAGEBOX_QUESTION);

	case ALLEGRO_MESSAGEBOX_OK_CANCEL:
		std::cerr << text << std::endl;
		return al_show_native_message_box(al_get_current_display(),
										"Ok / Cancella",
										"Cosa vuoi fare?",
										text,
										button,
										ALLEGRO_MESSAGEBOX_OK_CANCEL);
	case ALLEGRO_MESSAGEBOX_YES_NO:
		std::cerr << text << std::endl;
		return al_show_native_message_box(al_get_current_display(),
										"Si / No",
										"Scelta.",
										text,
										button,
										ALLEGRO_MESSAGEBOX_YES_NO);
	default:
		std::cerr << text << std::endl;
		return al_show_native_message_box(al_get_current_display(),
										"Errore",
										"Errore del programma",
										text,
										button,
										ALLEGRO_MESSAGEBOX_ERROR);
	}

	return -1;																	// -1: Errore // 0: Chiusura // 1: Ok/Yes // 2: Cancel/No
}

/*	bad.bmp = al_create_bitmap(bad.size, bad.size);
	al_set_target_bitmap(bad.bmp);
	al_clear_to_color(al_map_rgb(255, 0, 255));
	al_set_target_bitmap(al_get_backbuffer(display));	*/
