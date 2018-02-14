#include "ghost.h"
using namespace sf;
using namespace std;


void Ghost::update(double dt) {

	Vector2f direction;
	//Code for random movement
	//COllision as well i guess
	move(direction*_speed);

	Entity::update(dt);
}

Ghost::Ghost()
	: _speed(.1f), Entity(make_unique<CircleShape>(5.0f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Ghost::render(sf::RenderWindow & window) const
{
	window.draw(*_shape);
}
