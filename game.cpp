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

class Game
{
	protected:
	ALLEGRO_EVENT_QUEUE		*eventQueue;
	GameDisplay				*gameDisplay;

	Player					*p1;
	Bot						*f_bot1;
	EnemyBot				*e_bot;

	bool					render;
	bool					exitGame;

	public:
	Game()
	{
		this->gameDisplay = NULL;
		this->eventQueue = NULL;

		this->p1 = NULL;
		this->f_bot1 = NULL;
		this->e_bot = NULL;

		this->render = false;
		this->exitGame = false;
	}

	~Game()
	{
		delete e_bot;
		delete f_bot1;
		delete p1;
		delete gameDisplay;

		al_shutdown_native_dialog_addon();
		al_destroy_event_queue(eventQueue);
	}

	bool init()
	{
		if (!initAllegro())
			return false;

		this->gameDisplay = new GameDisplay();
		if (!gameDisplay->getDisplay())
			return false;

		this->p1 = new Player(800, 800, 100.);
		this->f_bot1 = new Bot(800, 850, 100.);
		this->e_bot = new EnemyBot(1280, 1440, 100.);

		p1->setFont(gameDisplay->getFont(1));
		f_bot1->setFont(gameDisplay->getFont(1));
		e_bot->setFont(gameDisplay->getFont(1));

		eventQueue = al_create_event_queue();
		if (!eventQueue)
			return false;

		al_register_event_source(eventQueue, al_get_timer_event_source(gameDisplay->getTimerFPS()));
		al_register_event_source(eventQueue, al_get_timer_event_source(gameDisplay->getTimerAnimation()));
		al_register_event_source(eventQueue, al_get_display_event_source(gameDisplay->getDisplay()));
		al_register_event_source(eventQueue, al_get_mouse_event_source());
		al_register_event_source(eventQueue, al_get_keyboard_event_source());

		return true;
	}

	void run()
	{
		this->gameDisplay->startSFX();
		this->gameDisplay->startTimerAnimation();
		this->gameDisplay->startTimerFPS();

		while(!this->exitGame)
		{
			ALLEGRO_EVENT event;
			//ALLEGRO_TIMEOUT timeout;
			//al_init_timeout(&timeout, 0.06);
			//bool getEvent = al_wait_for_event_until(eventQueue, &event, &timeout);
			al_wait_for_event(eventQueue, &event);

			if (event.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				this->p1->input(event.keyboard.keycode, true);
			}
			else if (event.type == ALLEGRO_EVENT_KEY_UP)
			{
				this->p1->input(event.keyboard.keycode, false);
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
				//gameDisplay->setScale(event.mouse.dz/10.);
			}
			else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				this->exitGame = true;
			}
			else if (event.type == ALLEGRO_EVENT_TIMER)
			{
				if (event.timer.source == this->gameDisplay->getTimerFPS())
				{
					this->gameDisplay->updateFPS();

					if (this->p1->getGameInput()->keyDown(ALLEGRO_KEY_ESCAPE))
						this->exitGame = true;

					this->p1->update(this->f_bot1);
					this->f_bot1->update(this->e_bot, this->p1);

					if (this->e_bot->getDistance(this->f_bot1) < this->e_bot->getDistance(this->p1))
						this->e_bot->update(this->f_bot1);
					else
						this->e_bot->update(this->p1);

					this->gameDisplay->updateCamera(this->p1);
				}
				else if (event.timer.source == this->gameDisplay->getTimerAnimation())
				{
					this->p1->updateAnimation();
					this->f_bot1->updateAnimation();
					this->e_bot->updateAnimation();
				}

				this->render = true;
			}

			if (render && al_is_event_queue_empty(eventQueue))
			{
				this->render = false;

				this->p1->render();
				this->f_bot1->render();
				this->e_bot->render();

				this->gameDisplay->draw();
			}
		}
	}
};
