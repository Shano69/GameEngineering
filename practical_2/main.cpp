#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.h"

using namespace sf;
using namespace std;

sf::Texture spritesheet;
sf::Sprite invader;
std::vector<Ship *> ships;
Player* player;

void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		std::cerr << "Failed to load spritesheet!" << std::endl;
	}
	
	/*Invader* inv = new Invader(sf::IntRect(0, 0, 32, 32), { 100,100 });
	ships.push_back(inv);*/
	 player = new Player();
	

	for (int r = 0; r < invaders_rows; ++r)
	{
		auto rect = IntRect(0, 0, 32, 32);
		for (int c = 0; c < invaders_columns; ++c) 
		{
			Vector2f position = {50.0f+c*70,50.0f+r*50};
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}
	ships.push_back(player);
}



void Update()
{
	static Clock clock;
	float dt = clock.restart().asSeconds();

	for(auto &a :ships) {
		a->Update(dt);
	}

}


void Render(RenderWindow &window)
{
	for (const auto &a : ships) {
		window.draw(*a);
	}
}

int main()
{
	
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
	Load();
	while (window.isOpen())
	{
		window.clear();
		Update();
		Render(window);
		window.display();
	}
	return 0;
}

