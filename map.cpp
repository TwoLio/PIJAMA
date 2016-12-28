#include <fstream>
#include <vector>
#include <string>

#include "globals.h"

class GameMap
{
	protected:
	std::vector< std::vector<int> >	map;

	ALLEGRO_BITMAP					*mapTile;
	int								size;

	load_state						loadState;

	public:
	GameMap()
	{
		this->mapTile = NULL;
	}

	~GameMap()
	{
		al_destroy_bitmap(mapTile);
	}

	void loadRT(const char *path)		//	Run-time loading for debugging
	{
		this->map.clear();
		this->load(path);
	}

	bool load(const char *path)
	{
		std::ifstream file(path);
		if (file.is_open())
		{
			std::string line, value;

			while (!file.eof())
			{
				std::getline(file, line);

				if (line.find("[Name]") != std::string::npos)
				{
					this->loadState = NAME;
					continue;
				}
				else if (line.find("[Size]") != std::string::npos)
				{
					this->loadState = SIZE;
					continue;
				}
				else if (line.find("[Map]") != std::string::npos)
				{
					this->loadState = MAP;
					continue;
				}

				switch (this->loadState)
				{
				case NAME:
					if (line.length() > 0)
						this->mapTile = al_load_bitmap(line.c_str());
					break;
				case SIZE:
					if (line.length() > 0)
						this->size = atoi(line.c_str());
					break;
				case MAP:
					std::stringstream str(line);
					std::vector<int> temp;

					while (!str.eof())
					{
						std::getline(str, value, ' ');
						if (value.length() > 0)
							temp.push_back(atoi(value.c_str()));
					}
					this->map.push_back(temp);
					break;
				}
			}

			return true;
		}
		else
			return false;
	}

	void draw(int startX = 0, int startY = 0)
	{
		for (int i = 0; i < this->map.size(); i++)
			for (int j = 0; j < this->map[i].size(); j++)
				al_draw_bitmap_region(this->mapTile, this->map[i][j] * this->size, 0, this->size, this->size, startX + j*this->size, startY + i*this->size, 0);
	}
};
