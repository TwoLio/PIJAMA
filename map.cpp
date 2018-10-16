#include "map.h"

GameMap::GameMap() : mapTile(nullptr) {}

GameMap::~GameMap() {
	al_destroy_bitmap(mapTile);
}

bool GameMap::loadRT(const char *path) {	//	Run-time loading for debugging
	map.clear();
	return load(path);
}

bool GameMap::load(const char *path) {
	std::ifstream file(path);
	if (file.is_open()) {
		std::string line, value;

		while (!file.eof()) {
			std::getline(file, line);

			if (line.find("[Name]") != std::string::npos) {
				loadState = NAME;
				continue;
			}
			else if (line.find("[Size]") != std::string::npos) {
				loadState = SIZE;
				continue;
			}
			else if (line.find("[Map]") != std::string::npos) {
				loadState = MAP;
				continue;
			}

			switch (loadState) {
			case NAME:
				if (line.length() > 0)
					mapTile = al_load_bitmap(line.c_str());
				break;
			case SIZE:
				if (line.length() > 0)
					size = atoi(line.c_str());
				break;
			case MAP:
				std::stringstream str(line);
				std::vector<int> temp;

				while (!str.eof()) {
					std::getline(str, value, ' ');
					if (value.length() > 0)
						temp.push_back(atoi(value.c_str()));
				}
				map.push_back(temp);
				break;
			}
		}

		return true;
	}
	else
		return false;
}

void GameMap::render(int startX, int startY) {
	for (unsigned i = 0; i < map.size(); ++i)
		for (unsigned j = 0; j < map[i].size(); ++j)
			al_draw_bitmap_region(mapTile, map[i][j]*size, 0, size, size, startX+j*size, startY+i*size, 0);
}