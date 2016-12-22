//#include <cstdlib>
//#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_opengl.h>

#include "functions.h"
#include "display.cpp"
#include "entities.cpp"

int main(int argc, char **argv)
{
	ALLEGRO_EVENT_QUEUE		*eventQueue = NULL;

	bool render = true;

	if (!initAllegro())
		return showMessageBox("Inizializzazione fallita a causa di un errore sconosciuto.", ALLEGRO_MESSAGEBOX_ERROR);

	GameDisplay *gameDisplay = new GameDisplay();
	if (!gameDisplay->getDisplay())
		return showMessageBox("Errore creazione display", ALLEGRO_MESSAGEBOX_ERROR);

	Player		*p1 = new Player(100, gameDisplay->getFont(1));
	Bot			*f_bot = new Bot(100, gameDisplay->getFont(1));
	EnemyBot	*e_bot = new EnemyBot(100, gameDisplay->getFont(1));

	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue, al_get_timer_event_source(gameDisplay->getTimerFPS()));
	al_register_event_source(eventQueue, al_get_timer_event_source(gameDisplay->getTimerAnimation()));
	al_register_event_source(eventQueue, al_get_display_event_source(gameDisplay->getDisplay()));
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	gameDisplay->startSFX();
	gameDisplay->startTimerAnimation();
	gameDisplay->startTimerFPS();

	while(!exitGame)
	{
		ALLEGRO_EVENT event;
		//ALLEGRO_TIMEOUT timeout;
		//al_init_timeout(&timeout, 0.06);
		//bool getEvent = al_wait_for_event_until(eventQueue, &event, &timeout);
		al_wait_for_event(eventQueue, &event);

		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			p1->input(event.keyboard.keycode, true);
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			p1->input(event.keyboard.keycode, false);
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{

		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{

		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_AXES ||
				 event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
		{
			//p1->setX(event.mouse.x);
			//p1->setY(event.mouse.y);
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			exitGame = true;
		}
		else if (event.type == ALLEGRO_EVENT_TIMER)
		{
			if (event.timer.source == gameDisplay->getTimerFPS())
			{
				gameDisplay->updateFPS();

				if (p1->getGameInput()->keyDown(ALLEGRO_KEY_ESCAPE))
					exitGame = true;

				p1->update(f_bot);
				f_bot->update(e_bot, p1);

				if (e_bot->getDistance(p1) < e_bot->getDistance(f_bot))
					e_bot->update(p1);
				else
					e_bot->update(f_bot);
			}
			else if (event.timer.source == gameDisplay->getTimerAnimation())
			{
				p1->updateAnimation();
				f_bot->updateAnimation();
				e_bot->updateAnimation();
			}

			render = true;
		}

		if (render && al_is_event_queue_empty(eventQueue))
		{
			render = false;

			p1->render();
			f_bot->render();
			e_bot->render();

			gameDisplay->draw();
		}
	}

	delete e_bot;
	delete f_bot;
	delete p1;
	delete gameDisplay;
	al_shutdown_native_dialog_addon();
	al_destroy_event_queue(eventQueue);

	return 0;
}
