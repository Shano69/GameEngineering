#include "ship.h"

using namespace sf;
using namespace std;

bool Invader::direction=true;
float Invader::speed = 20.f;

float Player::speed = .05f;
Ship::Ship() {};

Ship::~Ship() {}



Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt){}



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
	if (Keyboard::isKeyPressed(controls[0]))
	{
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1]))
	{
		direction++;
	}

	//PEW PEW CODE
	static vector<Bullet*> bullets;
	static float firetime = 0.0f;
	firetime -= dt;

	if (firetime <=0 && Keyboard::isKeyPressed(controls[2]))
	{
		Bullet::Fire(getPosition(), false);
		firetime = 0.7f;
	}

	

	ships[ships.size() - 1]->move(direction*speed,0);
}