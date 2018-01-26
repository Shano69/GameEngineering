#pragma once

#include "game.h"

class Bullet : public sf::Sprite {
public:
	static void Update(const float &dt);

	static void Render(sf::RenderWindow &window);
	
	static void Fire(const sf::Vector2f &pos, const bool mode);
	static Bullet bullets[256];
	~Bullet() = default;

	void setMode(bool mode) { _mode = mode; }
protected:
	Bullet();
	bool  _mode;
	static unsigned char bulletPointer;
	
	void _Update(const float &dt);
};