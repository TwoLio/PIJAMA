#pragma once
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

void initOpenGL(int width, int height)
{
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -200, 200);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void renderOpenGL()
{
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex3f(100.0f, 100.0f, 0.0f);
	glVertex3f(200.0f, 200.0f, 0.0f);
	glVertex3f(200.0f, 100.0f, 0.0f);

	glEnd();
	glFlush();
	glPopMatrix();

	al_wait_for_vsync();
	al_flip_display();
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
