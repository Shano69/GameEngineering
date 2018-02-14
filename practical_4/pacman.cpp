#include "pacman.h"

MenuScene::MenuScene()
{
}

void MenuScene::update(double dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
	text.setString("Almost Pacman ");
}

void MenuScene::render()
{
	Renderer::queue(&text);

}

void MenuScene::load()
{
}

void GameScene::respawn()
{
}

void GameScene::update(double dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
}

void GameScene::render()
{

}

void GameScene::load()
{

}
