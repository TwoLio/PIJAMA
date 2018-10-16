#include "config.h"

GameConfig::GameConfig() :
	config(nullptr) {}

GameConfig::~GameConfig() {
	al_destroy_config(config);
}

bool GameConfig::loadConfig(const char* path) {
	config = al_load_config_file(path);
	if (!config) {
		config = al_create_config();
		if (!al_save_config_file(path, config))
			return false;

		config = al_load_config_file(path);
	}

	return true;
}