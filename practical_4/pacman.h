#include "scene.h"
#include <SFML/Graphics.hpp>
#include "system_renderer.h"

class MenuScene :public Scene {
private:
	sf::Text text;

public:
	MenuScene();
	void update(double dt) override;
	void render() override;
	void load() override;
};

class GameScene : public Scene {
private: 
	sf::Text text;
	sf::Clock scoreClock;
	void respawn();

public:
	GameScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
};

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;