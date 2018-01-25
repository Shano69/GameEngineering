#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;
constexpr uint16_t invaders_rows = 5;
constexpr uint16_t invaders_columns = 8;

const Keyboard::Key controls[3] =
{
	Keyboard::A,
	Keyboard::D,
	Keyboard::Space,
};
class Player;
extern Player* player;
extern sf::Texture spritesheet;
class Ship;
extern std::vector<Ship *> ships;
