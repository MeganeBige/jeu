#include <iostream>

#include "TextureManager.h"
#include "SpriteManager.h"
#include "MenuPrincipal.h"

void MenuPrincipal::loadTexture() {

}

void MenuPrincipal::render() {
	
	
}

MenuPrincipal::MenuPrincipal() {

	std::cout << "Chargement du menu principal" << std::endl;
	std::cout << "Chargement des textures" << std::endl;
	
	nouvellePartie.setString("Nouvelle Partie");
	nouvellePartie.setPosition(100, 400);

	reprendrePartie.setString("Reprendre Partie");
	
	std::cout << "Chargement des sprites" << std::endl;
}

int MenuPrincipal::run() {
	
	return 0;
}

bool MenuPrincipal::isActive() {
	return active;
}