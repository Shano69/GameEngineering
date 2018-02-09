#include <SFML/Graphics.hpp>
#include <iostream>
#include "levelsystem.h"
#include "player.h"


using namespace sf;
using namespace std;

void Load() {
	
	ls::loadLevelFile("res/maze_2.txt");

}



void Update()
{
	

}


void Render(RenderWindow &window)
{
	
}

int main()
{

	RenderWindow window;
	Load();

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

