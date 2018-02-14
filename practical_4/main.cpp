#include <SFML/Graphics.hpp>
#include <iostream>
#include "levelsystem.h"
#include "player.h"
#include  "pacman.h"
#include "system_renderer.h"

using namespace sf;
using namespace std;
Font font;
Text text;
int gameHeight;
int gameWidth;
Player* player;
Vector2f Spos;

void Load() {
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	gameScene->load();
	menuScene->load();

	activeScene = menuScene;
}



void Update()
{
	static Clock clock;
	float dt = clock.restart().asSeconds();
	activeScene->update(dt);
}



void Render(RenderWindow &window)
{
	activeScene->render();
	Renderer::render();
}

int main()
{
	player = new Player();
	Load();
	//score board
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	text.setFont(font);
	text.setColor(sf::Color::Black);
	text.setCharacterSize(16);

	gameHeight = ls::getHeight() * 20;
	gameWidth = ls::getWidth() * 20;

	
	RenderWindow window(VideoMode(gameWidth, gameHeight), "pacman");
	while (window.isOpen())
	{


		window.clear();
		Update();
		Render(window);
		window.display();
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
	}


	return 0;

}

