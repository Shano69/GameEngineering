#pragma once
#include <SFML/Graphics.hpp>
#include "game.h"
#include "Bullet.h"

class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	Ship();
	bool _exploded;

public:

	explicit Ship(sf::IntRect ir);

	virtual ~Ship() = 0;

	virtual void Update(const float &dt);

	bool is_exploded() const;
	virtual void Explode();


};

class Invader : public Ship {
public:
	static bool direction;
	static float speed;
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float &dt) override;
};

class Player : public Ship {
public:
	
	static float speed;
	Player();
	void Update(const float &dt) override;
};