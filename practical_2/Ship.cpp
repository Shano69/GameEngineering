#include "ship.h"

using namespace sf;
using namespace std;

bool Invader::direction=true;
float Invader::speed = 30.f;

float Player::speed =.05f;
Ship::Ship() {};

Ship::~Ship() {}



Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt){
	if (toFade) {
		auto color = Color(getColor().r, getColor().g, getColor().b, getColor().a - dt);
		setColor(color);
	}
}



Invader::Invader() : Ship() {}

void Invader::Update(const float & dt)
{
	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f)* speed, 0);

	if ((direction&&getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16))
	{
		direction = !direction;
		for (int i = 0; i < ships.size()-1; ++i) {
			ships[i]->move(0, 24);
		}
	}
	
	static float firetime = 0.0f;
	firetime -= dt;
	if (firetime <= 0 && rand() % 100 == 0 && !toFade)
	{
		Bullet::Fire(getPosition(), true);
		firetime = 4 + (rand() % 60);
	}
	
	
}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight* .5f,gameHeight - 32.f });
}

void Player::Update(const float &dt) {
	Ship::Update(dt);
	
	
	float direction=0;
	if (Keyboard::isKeyPressed(controls[0])&&getPosition().x>0)
	{
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1]) && getPosition().x<gameWidth-32.0f)
	{
		direction++;
	}

	//PEW PEW CODE
	static float firetime = 0.0f;
	firetime -= dt;

	if (firetime <=0 && Keyboard::isKeyPressed(controls[2]))
	{
		Bullet::Fire(getPosition(), false);
		firetime = 0.7f;
	}

	move(direction*speed,0);
}

bool Ship::is_exploded() const
{
	return _exploded;
}

void Ship::Explode() {
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
	//auto color = Color(getColor().r, getColor().g, getColor().b, getColor().a);
	toFade = true;
}