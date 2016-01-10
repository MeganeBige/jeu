#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Unite.h"
using namespace std;


Unite::Unite(int _x, int _y, string _nom, string _desc, int _ressMax, int _deplacementMax, int _champVision, TypeUnite _type) : Entite(_x, _y, _nom, _desc)
{
	estUnite = true;
	estArmee = false;
	stockResssourceMax = _ressMax;
	deplacementMax = _deplacementMax;
	stockRessourceActuel = stockResssourceMax;
	champVision = _champVision;
	resistance = 0;
	type = _type;
	aAgi = false;
}

int Unite::getStockMaxRess() const
{
	return stockResssourceMax;
}

int Unite::getDeplacementMax()const
{
	if (stockRessourceActuel < deplacementMax) {
		return stockRessourceActuel+1;
	}
	return deplacementMax+1;
}

int Unite::getChampVision()const
{
	return champVision+1;
}

int Unite::getResistance()
{
	return resistance;
}

void Unite::setResistance(int _res) 
{
	resistance = _res;
}


int Unite::getStockRessActuel()
{
	return stockRessourceActuel;
}

bool Unite::peutSeDeplacer(int distance)
{
	return (!aAgi && stockRessourceActuel-distance > 0);
}

bool Unite::peutAgir()
{
	return !aAgi;
}

void Unite::update()
{
	aAgi = false;
}

void Unite::soin() {
	setPvRestant(getPvRestant() + 2);
}

bool Unite::estDetruit() {
	return getPvRestant() <= 0;
}

void Unite::reaprovisionnement()
{
	stockRessourceActuel = stockResssourceMax;
}

void Unite::prendDegat(int degat)
{
	setPvRestant(getPvRestant() - (degat - getResistance()));
}

void Unite::seDeplace(int x, int y, sf::RenderWindow *renderWindow, sf::Color color, SpriteManager *manager)
{
	
	int temp = std::abs(getCoordX() - x);
	temp += std::abs(getCoordY() - y);
	
	if (peutSeDeplacer(temp)) {
		stockRessourceActuel = stockRessourceActuel - temp;
		//animation(x,y, renderWindow, color, manager);
		aAgi = true;
		setCoord(x, y);
	}
	
}
/*
void Unite::animation(int x, int y, sf::RenderWindow *renderWindow, sf::Color color, SpriteManager *manager) {
	int i = getCoordX()*SPRITE;
	int j = getCoordY()*SPRITE;

	while (i != x*SPRITE || j != y*SPRITE) {
		sf::Sprite fond = getFond(manager);
		fond.setPosition(sf::Vector2f(i, j));
		fond.setColor(color);
		renderWindow->draw(fond);
		//Draw unite icon
		sf::Sprite icon = getIcon(manager);
		icon.setPosition(sf::Vector2f(i, j));
		icon.setColor(color);
		renderWindow->draw(icon);
		
		if (i > x*SPRITE) { i --; }
		else if (i < x*SPRITE) { i ++; }
		if (j > y*SPRITE){ j --; }
		else if (j < y*SPRITE){ j ++; }
		int t = 0;
		while (t != 10000) {
			t++;
		}
	}
}*/

bool Unite::isAerienne() {
	return type == TypeUnite::AERIENNE;
}

bool Unite::isMotorise() {
	return type == TypeUnite::MOTORISE;
}

bool Unite::isInfanterie() {
	return type == TypeUnite::INFANTERIE;
}

bool Unite::isMaritime() {
	return type == TypeUnite::MARITIME;
}

void Unite::render(sf::RenderWindow *renderWindow, sf::Color color, SpriteManager *manager) {
	sf::Sprite fond = getFond(manager);
	fond.setPosition(sf::Vector2f(getCoordX()*SPRITE, getCoordY()*SPRITE));
	fond.setColor(color);
	renderWindow->draw(fond);
	//Draw unite icon
	sf::Sprite icon = getIcon(manager);
	icon.setPosition(sf::Vector2f(getCoordX()*SPRITE, getCoordY()*SPRITE));
	icon.setColor(color);
	renderWindow->draw(icon);
	if (aAgi) {
		sf::Sprite filtreAgi = manager->getRef("filtre agi");
		filtreAgi.setPosition(sf::Vector2f(getCoordX()*SPRITE, getCoordY()*SPRITE));
		filtreAgi.setColor(color);
		renderWindow->draw(filtreAgi);
	}
}

sf::Sprite Unite::getFond(SpriteManager *manager) {
	sf::Sprite sprite;
	if (type == TypeUnite::AERIENNE) {
		sprite = manager->getRef("aerien");
	}
	else if (type == TypeUnite::INFANTERIE) {
		sprite = manager->getRef("infanterie");
	}
	else if (type == TypeUnite::MOTORISE) {
		sprite = manager->getRef("motorise");
	}
	else if (type == TypeUnite::MARITIME) {
		sprite = manager->getRef("maritime");
	}
	return sprite;
}

sf::Sprite Unite::getIcon(SpriteManager *manager) {
	sf::Sprite sprite;
	if (type == TypeUnite::AERIENNE) {
		sprite = getIconAerienne(manager);
	}
	else if (type == TypeUnite::INFANTERIE) {
		sprite = getIconInfanterie(manager);
	}
	else if (type == TypeUnite::MOTORISE) {
		sprite = getIconMotorise(manager);
	}
	else if (type == TypeUnite::MARITIME) {
		sprite = getIconMaritime(manager);
	}
	return sprite;
}

sf::Sprite Unite::getIconInfanterie(SpriteManager *manager) {
	sf::Sprite sprite;
	if (getNom() == "Soldat") {
		sprite = manager->getRef("soldat");
	}
	else if (getNom() == "Soldat arme") {
		sprite = manager->getRef("soldat_arme");
	}
	else if (getNom() == "Demolisseur") {
		sprite = manager->getRef("demolisseur");
	}
	else if (getNom() == "Explorateur") {
		sprite = manager->getRef("explorateur");
	}
	else if (getNom() == "Recruteur") {
		sprite = manager->getRef("recruteur");
	}
	return sprite;
}

sf::Sprite Unite::getIconAerienne(SpriteManager *manager) {
	sf::Sprite sprite;
	if (getNom() == "Chasseur") {
		sprite = manager->getRef("chasseur");
	}
	else if (getNom() == "Bombardier") {
		sprite = manager->getRef("bombardier");
	}
	else if (getNom() == "Helicoptere") {
		sprite = manager->getRef("helicoptere");
	}
	else if (getNom() == "Helicoptere de transport") {
		sprite = manager->getRef("helico_transport");
	}
	return sprite;
}

sf::Sprite Unite::getIconMotorise(SpriteManager *manager) {
	sf::Sprite sprite;
	if (getNom() == "Jeep") {
		sprite = manager->getRef("jeep");
	}
	else if (getNom() == "Char") {
		sprite = manager->getRef("char");
	}
	else if (getNom() == "Artillerie") {
		sprite = manager->getRef("artillerie");
	}
	else if (getNom() == "DCA") {
		sprite = manager->getRef("dca");
	}
	else if (getNom() == "Transporteur") {
		sprite = manager->getRef("transporteur");
	}
	return sprite;
}

sf::Sprite Unite::getIconMaritime(SpriteManager *manager) {
	sf::Sprite sprite;
	if (getNom() == "Cuirasse") {
		sprite = manager->getRef("cuirasse");
	}
	else if (getNom() == "Torpilleur") {
		sprite = manager->getRef("torpilleur");
	}
	else if (getNom() == "Corvette") {
		sprite = manager->getRef("corvette");
	}
	else if (getNom() == "Barge") {
		sprite = manager->getRef("barge");
	}
	return sprite;
}