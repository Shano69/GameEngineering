#pragma once

#include<SFML\Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "maths.h"

#define ls LevelSystem

class LevelSystem {

public:
    enum TILE {EMPTY, START,END, WALL, ENEMY, WAYPOINT};

    static void loadLevelFile(const std::string&, float tileSize=100.0f);
    static void render(sf::RenderWindow &window);
    static sf::Color getColor(TILE t);
    static void setColor(TILE t, sf::Color c);

	static size_t getHeight() { return _height; }
	static size_t getWidth() { return _width; }

    //get tile at grid coordinate
    static TILE getTile (sf::Vector2ul);
    //get Screenspace coordinate of tile
    static sf::Vector2f getTilePosition(sf::Vector2ul);
    //get the tile screanspace pos
    static TILE getTileAt(sf::Vector2f);

protected:
    static std::unique_ptr<TILE[]> _tiles;
    static size_t _width;
    static size_t _height;
    static sf::Vector2f _offset;
    static float _tileSize;
	static std::map<TILE, sf::Color> _colours;

    static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;
    static void buildSprites();

private:    
    LevelSystem() = delete;
    ~LevelSystem() = delete;
};