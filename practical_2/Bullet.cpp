#include "Bullet.h"
#include "Ship.h"


using namespace sf;
using namespace std;

unsigned char Bullet::bulletPointer;
Bullet Bullet::bullets[256];



void Bullet::Update(const float & dt)
{
	
	for (auto a : bullets)
	{
		a.move(0, dt * 200.0f * (a._mode ? 1.0f : -1.0f));
		a._Update(dt);
		
	}
}

void Bullet::Render(sf::RenderWindow & window)
{
	for( auto a:bullets)
	{
		window.draw(a);
	}
}

void Bullet::Fire(const sf::Vector2f & pos, const bool mode)
{


}

bool Ship::is_exploded() const
{
	return false;
}

void Ship::Explode() {
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
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
		move(0, dt *200.0f * (_mode ? 1.0f : -1.0f));
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