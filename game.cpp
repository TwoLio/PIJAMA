#include "display.cpp"
#include "map.cpp"

class Game
{
	protected:
	ALLEGRO_EVENT_QUEUE		*eventQueue;
	ALLEGRO_CONFIG			*gameConfig;

	GameDisplay				*gameDisplay;
	GameInput				*gameInput;
	GameMap					*gameMap;

	Player					*p1;
	Bot						*f_bot;
	EnemyBot				*e_bot;

	bool					render;
	bool					exit;

	game_state				gameState;


	public:
	Game()
	{
		this->gameDisplay = NULL;
		this->gameInput = NULL;
		this->gameMap = NULL;
		this->gameConfig = NULL;
		this->eventQueue = NULL;

		this->p1 = NULL;
		this->e_bot = NULL;
		this->f_bot = NULL;

		this->render = false;
		this->exit = false;
	}

	~Game()
	{
		al_shutdown_native_dialog_addon();
		al_destroy_config(gameConfig);
		al_destroy_event_queue(eventQueue);

		delete e_bot;
		delete f_bot;
		delete p1;
		delete gameMap;
		delete gameInput;
		delete gameDisplay;
	}

	bool initAllegro()
	{
		if (!al_init())
			return false;

		al_init_image_addon();
		al_init_primitives_addon();
		al_init_font_addon();
		al_init_ttf_addon();
		al_init_native_dialog_addon();

		return true;
	}

	bool initConfig()
	{
		this->gameConfig = al_load_config_file("cfg/base.cfg");
		if (!gameConfig)
		{
			this->gameConfig = al_create_config();
			if (!al_save_config_file("cfg/base.cfg", gameConfig))
				return false;

			this->gameConfig = al_load_config_file("cfg/base.cfg");
		}

		return true;
	}

	bool init()
	{
		if (!this->initAllegro())
			return false;

		this->gameDisplay = new GameDisplay();
		if (!gameDisplay->getDisplay())
			return false;

		this->gameInput = new GameInput();

		if (!this->initConfig())
			return false;

		this->gameMap = new GameMap();
		if (!this->gameMap->load("cfg/map.txt"))
			return false;

		this->p1 = new Player(gameInput, 800, 800, 100.);
		this->f_bot = new Bot(800, 850, 100.);
		this->e_bot = new EnemyBot(1280, 1440, 100.);

		p1->setFont(gameDisplay->getFont(1));
		f_bot->setFont(gameDisplay->getFont(1));
		e_bot->setFont(gameDisplay->getFont(1));

		eventQueue = al_create_event_queue();
		if (!eventQueue)
			return false;

		al_register_event_source(eventQueue, al_get_mouse_event_source());
		al_register_event_source(eventQueue, al_get_keyboard_event_source());
//		al_register_event_source(eventQueue, al_get_joystick_event_source());
		al_register_event_source(eventQueue, al_get_timer_event_source(gameDisplay->getTimerFPS()));
		al_register_event_source(eventQueue, al_get_timer_event_source(gameDisplay->getTimerAnimation()));
		al_register_event_source(eventQueue, al_get_display_event_source(gameDisplay->getDisplay()));

		return true;
	}

	void run()
	{
		this->gameDisplay->startSFX();
		this->gameDisplay->startTimerAnimation();
		this->gameDisplay->startTimerFPS();

		while(!this->exit)
		{
			ALLEGRO_EVENT event;
			al_wait_for_event(eventQueue, &event);

			//this->gameInput->updateJoystickState();

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
/*			else if (event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN)
			{
				std::cout << event.joystick.button << std::endl;
			}
			else if (event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_UP)
			{

			}
			else if (event.type == ALLEGRO_EVENT_JOYSTICK_AXIS)
			{
				//std::cout << event.joystick.pos << std::endl;
				std::cout << event.joystick.axis << std::endl;
				std::cout << event.joystick.stick << std::endl;
			}
			else if (event.type == ALLEGRO_EVENT_JOYSTICK_CONFIGURATION)
			{
				//this->gameInput->reconfigJoystick();
			}*/
			else if (event.type == ALLEGRO_EVENT_MOUSE_AXES ||
					 event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
			{
				//p1->setDirection(event.mouse.x, event.mouse.y);
				//gameDisplay->setScale(event.mouse.dz/10.);
			}
			else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				this->exit = true;
			}
			else if (event.type == ALLEGRO_EVENT_TIMER)
			{
				if (event.timer.source == this->gameDisplay->getTimerFPS())
				{
					this->gameDisplay->updateFPS();

					if (this->gameInput->keyDown(ALLEGRO_KEY_ESCAPE))
						this->exit = true;
					if (this->gameInput->keyDown(ALLEGRO_KEY_L))
						this->gameMap->loadRT("cfg/map.txt");

					this->p1->update(this->e_bot);
					this->f_bot->update(this->e_bot, this->p1);
					this->e_bot->update(this->p1);

					this->gameDisplay->updateCamera(this->p1);
				}
				else if (event.timer.source == this->gameDisplay->getTimerAnimation())
				{
					this->p1->updateAnimation();
					this->f_bot->updateAnimation();
					this->e_bot->updateAnimation();
				}

				this->render = true;
			}

			if (render && al_is_event_queue_empty(eventQueue))
			{
				this->render = false;

				this->gameMap->draw(500, 500);

				this->p1->render();
				this->f_bot->render();
				this->e_bot->render();

				this->gameDisplay->draw();
			}
		}
	}

	game_state getState()
	{
		return this->gameState;
	}

	void setState(game_state gameState)
	{
		this->gameState = gameState;
	}

	ALLEGRO_BITMAP*	createBitmapFromLayers(ALLEGRO_BITMAP *texture[], int n)
	{
		ALLEGRO_BITMAP *bmp = al_create_bitmap(al_get_bitmap_width(texture[0]), al_get_bitmap_height(texture[0]));
		al_set_target_bitmap(bmp);

		for (int i = 0; i < n; i++)
			al_draw_bitmap(texture[i], 0, 0, 0);

		al_save_bitmap("gfx/bmp/bitmap.png", bmp);
		al_set_target_bitmap(al_get_backbuffer(this->gameDisplay->getDisplay()));

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
};
