#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include "SpriteManager.h"
#include "Unite.h"
#include "UniteArmee.h"

class Interface
{
private:
	bool modeNormal,  modeBatiment;
public:
	Interface();

	bool getModeNormal();
	bool getModeBatiment();

	void setModeNormal();
	void setModeBatiment();

	void render(sf::RenderWindow *renderWindow,SpriteManager *manager);
	void renderInfoUnite(sf::RenderWindow *renderWindow, Unite *unite);
	void ecrireMessage(sf::RenderWindow *renderWindow, float posX, float posY, std::string msg, std::string pathToFont, int fontSize, sf::Color color);
};