#pragma once

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Map.h"
#include "Tile.h"
#include "SpriteManager.h"
#include "Constantes.h"
#include "Player.h"

class Minimap {
private:
	sf::Image m_imageMinimap, m_imageRessource;
	bool m_topo, m_ressource, m_unite;
	int m_width, m_heigth;

public:
	Minimap();
	Minimap(Map *map);
	Minimap(Map *map, Player *player);

	void updateBrouillard(Map *map, Player *player);

	void render(sf::RenderWindow* renderWindow);
	void renderPlayer(sf::RenderWindow *renderWindow, Player *player[], int nbJoueur);



	void changeModeTopo();
	void changeModeRessource();
	void changeModeUnite();
	bool getUniteMode();

};
