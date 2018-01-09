#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

const Keyboard::Key controls[4] =
{
	Keyboard::A,
	Keyboard::S,
	Keyboard::K,
	Keyboard::L,
};

int scoreLeft=0;
int scoreRight=0;
Font font;
Text text;
Vector2f ballVel;
bool server = false;
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

CircleShape ball;
RectangleShape paddles[2];

void Reset()
{
	ballVel = { server ? 100.0f : -100.0f, 60.0f };
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - paddleSize.x, gameHeight / 2);
	ball.setPosition(gameWidth / 2, gameHeight / 2);

	text.setString(std::to_string(scoreLeft) + ":" + std::to_string(scoreRight));
	text.setPosition((gameWidth *0.5f) - (text.getLocalBounds().width * 0.5f), 0);
}

void Load()
{
	for (auto &p : paddles)
	{
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	Reset();

	ballVel = { server ? 100.0f : -100.0f, 60.0f };
	

	//score board
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
		
	

}



void Update(RenderWindow &window)
{
	static Clock clock;
	float dt = clock.restart().asSeconds();
	
	Event event;
	while (window.pollEvent(event)) 
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}
	//input checks
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}

	float directionPleft = 0.0f;
	if (Keyboard::isKeyPressed(controls[0]))
	{
		directionPleft--;
	}
	if (Keyboard::isKeyPressed(controls[1]))
	{
		directionPleft++;
	}
	float directionPright = 0.0f;
	if (Keyboard::isKeyPressed(controls[2]))
	{
		directionPright--;
	}
	if (Keyboard::isKeyPressed(controls[3]))
	{
		directionPright++;
	}
	

	//checking for collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if (by > gameHeight)
	{
		ballVel.x *= 1.1f;
		ballVel.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by <0 )
	{
		ballVel.x *= 1.1f;
		ballVel.y *= -1.1f;
		ball.move(0, 10);
	}
	//reset bounce
	else if (bx > gameWidth)
	{
		scoreLeft += 1;
		Reset();
	}
	else if (bx < 0)
	{
		scoreRight += 1;
		Reset();
	}

	//bounce left
	else if (
		//ball is inline or behind paddle
		bx<paddleSize.x &&
		//And Ball is bellow top ednge of paddle
		by> paddles[0].getPosition().y - (paddleSize.y *0.5f) &&
		//And Ball is above the bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y*0.5f)
		)
	{
		ballVel.x *= -1.1f;
		ballVel.y *= 1.1f;
		ball.move(10, 0);
	}
	// bounce off right
	else if (
		//ball is inline or behind paddle
		bx>gameWidth - paddleSize.x &&
		//And Ball is bellow top ednge of paddle
		by> paddles[1].getPosition().y - (paddleSize.y *0.5f) &&
		//And Ball is above the bottom edge of paddle
		by < paddles[1].getPosition().y + (paddleSize.y*0.5f)
		)
	{
		ballVel.x *= -1.1f;
		ballVel.y *= 1.1f;
		ball.move(-10, 0);
	}

	// AI play for left
	bool shouldAIplayLeft = !Keyboard::isKeyPressed(controls[0]) && !Keyboard::isKeyPressed(controls[1]);
	 if (ball.getPosition().y > paddles[0].getPosition().y && shouldAIplayLeft)
	{
		directionPleft++;
	}
	else if (ball.getPosition().y < paddles[0].getPosition().y && shouldAIplayLeft)
	{
		directionPleft--;
	}
	 //AI play for right
	 bool shouldAIplayRight = !Keyboard::isKeyPressed(controls[2]) && !Keyboard::isKeyPressed(controls[3]);
	 if (ball.getPosition().y > paddles[1].getPosition().y && shouldAIplayRight)
	 {
		 directionPright++;
	 }
	 else if (ball.getPosition().y < paddles[1].getPosition().y && shouldAIplayRight)
	 {
		 directionPright--;
	 }

	//movement of objects
	paddles[0].move(0, directionPleft*paddleSpeed * dt);
	paddles[1].move(0, directionPright*paddleSpeed * dt);
	ball.move(ballVel*dt);
}

void Render(RenderWindow &window) 
{
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(text);
}


int main ()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
    return 0;
}