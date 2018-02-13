#include "player.h"
using namespace sf;
using namespace std;


void Player::update(double dt) {

	Vector2f direction;
	if (Keyboard::isKeyPressed(Keyboard::A) )
	{
		direction.x--;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		direction.x++;
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		direction.y--;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		direction.y++;
	}
	move(direction*_speed);

	Entity::update(dt);
}

Player::Player()
	: _speed(.1f), Entity(make_unique<CircleShape>(25.0f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}