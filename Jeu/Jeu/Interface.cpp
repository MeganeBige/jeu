#include "Interface.h"

Interface::Interface() {
	setModeNormal();
}

void Interface::setModeNormal() {
	modeNormal = true;
	modeBatiment = false;
}

bool Interface::getModeNormal() {
	return modeNormal;
}

void Interface::setModeBatiment() {
	modeNormal = false;
	modeBatiment = true;
}

bool Interface::getModeBatiment() {
	return modeBatiment;
}

void Interface::render(sf::RenderWindow *renderWindow, SpriteManager *manager) {
	renderWindow->draw(manager->getRef("interface"));
	renderWindow->draw(manager->getRef("interfaceBarre"));
	return;
}

void Interface::renderInfoUnite(sf::RenderWindow *renderWindow, Unite *unite) {
	std::string nom, vie, reserve,description, deplacement, vision, res;

	nom = "Nom : " + unite->getNom();
	description = "Description : " + unite->getDescription();
	
	reserve = "Réserve : "; 
	reserve = reserve + std::to_string(unite->getStockRessActuel()) + "/"+ std::to_string(unite->getStockMaxRess());
	
	vie = "Vie : ";
	vie = vie + std::to_string(unite->getPvRestant()) + "/10";
	
	deplacement = "Déplacement : ";
	deplacement = deplacement + std::to_string(unite->getDeplacementMax());
	
	vision = "Vision : ";
	vision = vision + std::to_string(unite->getChampVision());
	
	res = "Résistance env. : ";
	res = res + std::to_string(unite->getResistance());

	float posX = 403;
	float posY = 805;

	ecrireMessage(renderWindow,posX,posY,nom,"media/Constantine.ttf",18,sf::Color::Black);
	ecrireMessage(renderWindow, posX, posY+18 , description, "media/Constantine.ttf", 18, sf::Color::Black);
	ecrireMessage(renderWindow, posX, posY + 18*2, vie, "media/Constantine.ttf", 18, sf::Color::Black);
	ecrireMessage(renderWindow, posX, posY + 18*3, reserve, "media/Constantine.ttf", 18, sf::Color::Black);
	ecrireMessage(renderWindow, posX, posY + 18*4, deplacement, "media/Constantine.ttf", 18, sf::Color::Black);
	ecrireMessage(renderWindow, posX, posY + 18*5, vision, "media/Constantine.ttf", 18, sf::Color::Black);
	ecrireMessage(renderWindow, posX, posY + 18*6, res, "media/Constantine.ttf", 18, sf::Color::Black);
	
	if (unite->isArmee()) {
		UniteArmee* armee = (UniteArmee*)unite;
		std::string mun = "Munition : ", port = "Portée : ";
		mun = mun + std::to_string(armee->getStockMunActuel()) + '/' + std::to_string(armee->getStockMaxMun());
		port = port + std::to_string(armee->getRangeMin()) + '/' + std::to_string(armee->getRangeMax());

		ecrireMessage(renderWindow, posX, posY + 18*7, mun, "media/Constantine.ttf", 18, sf::Color::Black);
		ecrireMessage(renderWindow, posX, posY + 18*8, port, "media/Constantine.ttf", 18, sf::Color::Black);
	}
}

void Interface::ecrireMessage(sf::RenderWindow *renderWindow, float posX, float posY, std::string msg, std::string pathToFont,int fontSize, sf::Color color) {
	sf::Font font;
	if (!font.loadFromFile(pathToFont))
	{
		std::cerr << "Font introuvable" << std::endl;
	}
	else {
		sf::Text text;
		text.setString(msg);
		text.setPosition(sf::Vector2f(posX, posY));
		text.setColor(color);
		text.setCharacterSize(fontSize);
		text.setFont(font);
		text.setStyle(sf::Text::Bold);
		renderWindow->draw(text);
	}
	
}