#pragma once

class MenuPrincipal {

private:

	sf::Text nouvellePartie;
	sf::Text reprendrePartie;
	sf::Text option;
	sf::Text quitter;

	bool active;

	void loadTexture();
	void render();

public:
	MenuPrincipal();
	int run();
	bool isActive();

};