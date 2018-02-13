#include <SFML/Graphics.hpp>
#include <iostream>
#include "levelsystem.h"
#include "player.h"


using namespace sf;
using namespace std;
Player* player;
int gameHeight; 
int gameWidth;
Vector2f okPos;
Vector2f Spos;
Font font;
Text text;
float currentTime =0;
float bestTime =0;
float lastTime = 0;
bool firstPlay = true;

bool validmove(Vector2f pos) {
	return(ls::getTileAt(pos) != ls::WALL);
}

bool completeLevel(Vector2f pos) {
	return(ls::getTileAt(pos) == ls::END);
}

void Load() {
	
	ls::loadLevelFile("res/maze_2.txt");

	Spos.x =  ls::getTilePosition(Vector2ul(1, 1)).x + 50;
	Spos.y =  ls::getTilePosition(Vector2ul(1, 1)).y + 50;
	player->setPosition(Spos);
}



void Update()
{	
	text.setString("Best Time: " + std::to_string(bestTime) + " Last Time: " + std::to_string(lastTime) + " Current Time: " + std::to_string(currentTime));
	static Clock clock;
	float dt = clock.restart().asSeconds();
	currentTime += dt;
	//check if move is possible and if possible move
	if (validmove(Vector2f(player->getPosition().x,player->getPosition().y+25))) {
		okPos = player->getPosition();
		player->update(dt);
		
	}
	else {
		player->setPosition(okPos);
	}
	// complete level 
	if (completeLevel(player->getPosition()))
	{
		cout << "level complete" << endl;
		player->setPosition(Spos);
		lastTime = currentTime;
		if (firstPlay) {
			bestTime = currentTime;
			firstPlay = false;
		}
		else if (currentTime < bestTime) {
			bestTime = currentTime;
		}
		currentTime = 0.0f;
	}
}


void Render(RenderWindow &window)
{
	ls::render(window);
	player->render(window);
	window.draw(text);
	
}

int main()
{
	//score board
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	text.setFont(font);
	text.setColor(sf::Color::Black);
	text.setCharacterSize(16);
	text.setPosition((gameWidth *0.5f) - (text.getLocalBounds().width * 0.5f), 0);
	
	
	player = new Player();
	Load();
	gameHeight = ls::getHeight() * 100;
	gameWidth = ls::getWidth() * 100;
	RenderWindow window(VideoMode(gameWidth, gameHeight), "maze");
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

