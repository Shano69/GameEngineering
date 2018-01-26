#include "Bullet.h"
#include "Ship.h"
#include <iostream>

using namespace sf;
using namespace std;

unsigned char Bullet::bulletPointer;
Bullet Bullet::bullets[256];



void Bullet::Update(const float & dt)
{
	
	for (auto& a : bullets)
	{
		a._Update(dt);
	}
}

void Bullet::Render(sf::RenderWindow & window)
{
	
	
	for (auto& a : bullets)
	{
		a.setTexture(spritesheet);
		if (!a._mode) {
			a.setTextureRect(IntRect(64.0f, 32.0f, 32.0f, 32.0f));
		}
		else {
			a.setTextureRect(IntRect(32.0f, 32.0f, 32.0f, 32.0f));
		}
		window.draw(a);
	}
}

void Bullet::Fire(const sf::Vector2f & pos, const bool mode)
{
	auto bulletIndex = static_cast<int>(++bulletPointer);
	std::cout << "Firing Bullet num:" << bulletIndex << std::endl;

	
	
	bullets[bulletIndex].setPosition(pos);
	bullets[bulletIndex].setMode(mode);
	std::cout <<"Bullet position"<< bullets[bulletIndex].getPosition().x << " " << bullets[bulletIndex].getPosition().y << std::endl;

}



Bullet::Bullet()
{
}

void Bullet::_Update(const float &dt) {
	if (getPosition().y <-32 || getPosition().y>gameHeight + 32)
	{
		return;
	}
	else {
		move(0, dt *200* (_mode ? 1.0f : -1.0f));
		
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships) {
			if ( !_mode && s == player) {
				continue;
			}
			if (_mode && s !=player) {
				continue;
			}
			
			if (!s->is_exploded() && s->getGlobalBounds().intersects(boundingBox))
			{
				s->Explode();
				
				setPosition(-100, -100);
				return;
			}
		}
	}
}