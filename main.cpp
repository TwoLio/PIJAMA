#include <cstdlib>
#include <iostream>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_opengl.h>
#include <glm/glm.hpp>
#include "global.h"
#include "object.cpp"
#include "function.cpp"
#include "display.cpp"

int main(int argc, char **argv)
{
	const float 			FPS = 60.0f;
	float 					gameTime = 0.0f;
	int 					frames = 0;
	int						gameFPS = 0;

	ALLEGRO_TIMER			*timerFPS = nullptr;

	ALLEGRO_FONT			*font = nullptr;
	ALLEGRO_SAMPLE			*sample = nullptr;

//	ALLEGRO_KEYBOARD_STATE	keyState;
//	ALLEGRO_MOUSE_STATE		mouseState;

	ALLEGRO_EVENT_QUEUE		*eventQueue = nullptr;

	bool 					renderScene = true;

	if (!initAllegro())
		return showMessageBox("Inizializzazione fallita a causa di un errore sconosciuto.", ALLEGRO_MESSAGEBOX_ERROR);


	GameDisplay				*gameDisplay = new GameDisplay();

	if (!gameDisplay->display)
		return showMessageBox("Errore creazione display", ALLEGRO_MESSAGEBOX_ERROR);

	SCREEN_WIDTH = gameDisplay->getScreenWidth();
	SCREEN_HEIGHT = gameDisplay->getScreenHeight();

	//initOpenGL(SCREEN_WIDTH, SCREEN_HEIGHT);

	GameObject 			*bad = new GameObject(20, true, 250, 0, 200.0f);
	GameObject 			*p1 = new GameObject(20, false, -250, -20);
	GameObject 			*p2 = new GameObject(20, false, -250, 20);

	al_reserve_samples(1);
	sample = al_load_sample("sfx/relax.wav");
	font = al_load_ttf_font("gfx/font/amsterdam.ttf", 36, 0);
	timerFPS = al_create_timer(1.0f / FPS);
	eventQueue = al_create_event_queue();

	al_register_event_source(eventQueue, al_get_timer_event_source(timerFPS));
	al_register_event_source(eventQueue, al_get_display_event_source(gameDisplay->display));
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	al_play_sample(sample, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_LOOP, NULL);

	al_start_timer(timerFPS);
	gameTime = al_current_time();

	while(!exitGame)
	{
		ALLEGRO_EVENT 		event;
		//ALLEGRO_TIMEOUT		timeout;
		//al_init_timeout(&timeout, 0.06);
		//bool getEvent = al_wait_for_event_until(eventQueue, &event, &timeout);
		al_wait_for_event(eventQueue, &event);

		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			p1->input(event.keyboard.keycode, true);
			//p2->input(event.keyboard.keycode, true);
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			p1->input(event.keyboard.keycode, false);
			//p2->input(event.keyboard.keycode, false);
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_AXES ||
				 event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
		{
			//p1->setX(event.mouse.x);
			//p1->setY(event.mouse.y);
			p2->setX(event.mouse.x);
			p2->setY(event.mouse.y);
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}
		else if (event.type == ALLEGRO_EVENT_TIMER)
		{
			frames++;
			if(al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}

			//al_get_keyboard_state(&keyState);
			//al_get_mouse_state(&mouseState);

			p1->update();

			if (bad->getDistance(p1) < bad->getDistance(p2))
				bad->update(p1);
			else
				bad->update(p2);

			renderScene = true;
		}

		if (renderScene && al_is_event_queue_empty(eventQueue))
		{
			renderScene = false;

			al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 70,
							ALLEGRO_ALIGN_LEFT, "FPS: %i", gameFPS);

			p1->render(0, 0, 255);
			p2->render(0, 255, 0);
			bad->render();

			gameDisplay->draw();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	delete bad;
	delete p2;
	delete p1;

	delete gameDisplay;

	al_shutdown_native_dialog_addon();

	al_destroy_event_queue(eventQueue);
	al_destroy_sample(sample);
	al_destroy_timer(timerFPS);

	return 0;
}
