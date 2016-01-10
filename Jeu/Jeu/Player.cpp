#include "Player.h"
#include <iostream>

Player::Player(sf::Color color) {
	couleur = color;
}

void Player::creerUnite(Unite *unite, int x, int y,int resistance) {
	unite->setResistance(resistance);
	unite->setCoord(x, y);
	listUnite.push_back(unite);
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGTH; j++) {
			caseDecouverte[i][j] = false;
		}
	}
}

void Player::detruireUnite(int index) {
	listUnite.erase(listUnite.begin() + index );
}

void Player::creerBatiment(Batiment* batiment) {
	listBatiment.push_back(batiment);
}

void Player::detruireBatiment(int index) {
	listBatiment.erase(listBatiment.begin() + index );
}


int Player::getNombreUnite() {
	return listUnite.size();
}

Unite* Player::getUnite(int index) {
	return listUnite[index];
}

int Player::getNombreBatiment() {
	return listBatiment.size();
}

Batiment* Player::getBatiment(int index) {
	return listBatiment[index];
}

sf::Color Player::getColor() {
	return couleur;
}
void Player::initTechnologies() {

	Technologie recherche("Recherche", 0, 0, 0, 0);
	Technologie exploration("Exploration", 0, 0, 0, 0);
	Technologie vivres("Vivres", 0, 0, 0, 0);
	Technologie petrole("Pétrole", 0, 0, 0, 0);
	Technologie caserne("Caserne", 0, 0, 0, 0);
	Technologie avantPoste("Avant poste", 0, 0, 0, 0);
	Technologie recrutement("Recrutement", 0, 0, 0, 0);
	Technologie metal("Métal", 0, 0, 0, 0);
	Technologie soldat("Soldat", 0, 0, 0, 0);
	Technologie demolisseur("Démolisseur", 0, 0, 0, 0);
	Technologie usine("Usine", 0, 0, 0, 0);
	Technologie aeroport("Aéroport", 0, 0, 0, 0);
	Technologie port("Port", 0, 0, 0, 0);
	Technologie jeep("Jeep", 0, 0, 0, 0);
	Technologie charAssault("Char", 0, 0, 0, 0);
	Technologie artillerie("Artillerie", 0, 0, 0, 0);
	Technologie dca("DCA", 0, 0, 0, 0);
	Technologie chasseur("Chasseur", 0, 0, 0, 0);
	Technologie bombardier("Bombardier", 0, 0, 0, 0);
	Technologie helicoptere("Hélicoptère", 0, 0, 0, 0);
	Technologie cuirasse("Cuirasse", 0, 0, 0, 0);
	Technologie torpilleur("Torpilleur", 0, 0, 0, 0);
	Technologie corvette("Corvette", 0, 0, 0, 0);
	Technologie vivresStock("Stockage de vivres", 0, 0, 0, 0);
	Technologie petroleStock("Stockage de pétrole", 0, 0, 0, 0);
	Technologie metalStock("Stockage de métaux", 0, 0, 0, 0);
	Technologie transportTerrestre("Transport Terrestre", 0, 0, 0, 0);
	Technologie transportMarin("Transport Marin", 0, 0, 0, 0);
	Technologie transportAerien("Transport Aérien", 0, 0, 0, 0);

	recherche.setTechSuivante(exploration);
	recherche.setTechSuivante(vivres);
	exploration.setTechSuivante(avantPoste);
	exploration.setTechSuivante(recrutement);
	vivres.setTechSuivante(vivresStock);
	vivres.setTechSuivante(caserne);
	vivres.setTechSuivante(petrole);
	vivres.setTechSuivante(metal);
	caserne.setTechSuivante(soldat);
	caserne.setTechSuivante(demolisseur);
	petrole.setTechSuivante(petroleStock);
	petrole.setTechSuivante(usine);
	metal.setTechSuivante(petroleStock);
	metal.setTechSuivante(metalStock);
	usine.setTechSuivante(aeroport);
	usine.setTechSuivante(port);
	usine.setTechSuivante(jeep);
	usine.setTechSuivante(charAssault);
	usine.setTechSuivante(artillerie);
	usine.setTechSuivante(dca);
	usine.setTechSuivante(transportTerrestre);
	aeroport.setTechSuivante(chasseur);
	aeroport.setTechSuivante(bombardier);
	aeroport.setTechSuivante(helicoptere);
	aeroport.setTechSuivante(transportAerien);
	port.setTechSuivante(cuirasse);
	port.setTechSuivante(torpilleur);
	port.setTechSuivante(corvette);
	port.setTechSuivante(transportMarin);


	demolisseur.setTechPrecedente(caserne);
	soldat.setTechPrecedente(caserne);
	caserne.setTechPrecedente(vivres);
	vivresStock.setTechPrecedente(vivres);
	petrole.setTechPrecedente(vivres);
	metal.setTechPrecedente(vivres);
	metalStock.setTechPrecedente(metal);
	petroleStock.setTechPrecedente(petrole);
	usine.setTechPrecedente(petrole);
	usine.setTechPrecedente(metal);
	aeroport.setTechPrecedente(usine);
	port.setTechPrecedente(usine);
	jeep.setTechPrecedente(usine);
	charAssault.setTechPrecedente(usine);
	artillerie.setTechPrecedente(usine);
	dca.setTechPrecedente(usine);
	transportTerrestre.setTechPrecedente(usine);
	chasseur.setTechPrecedente(aeroport);
	bombardier.setTechPrecedente(aeroport);
	helicoptere.setTechPrecedente(aeroport);
	transportAerien.setTechPrecedente(aeroport);
	cuirasse.setTechPrecedente(port);
	torpilleur.setTechPrecedente(port);
	corvette.setTechPrecedente(port);
	transportMarin.setTechPrecedente(port);
	vivres.setTechPrecedente(recherche);
	exploration.setTechPrecedente(recherche);
	avantPoste.setTechPrecedente(exploration);
	recrutement.setTechPrecedente(exploration);
}

void Player::rechercheTechnologie(Technologie *tech) {
	if (tech->verifierCoutTechnologie(energie, essence, metaux, vivre) && tech->verifierSiRecherchable()) {
		tech->setEstRecherche(true);
	}
}

void Player::render(sf::RenderWindow *renderWindow, SpriteManager *manager) {

	for (unsigned int i = 0; i < listUnite.size(); i++) {
		listUnite[i]->render(renderWindow, couleur, manager);
	}
	for (unsigned int i = 0; i < listBatiment.size(); i++) {
		listBatiment[i]->render(renderWindow, couleur, manager);
	}
}

void Player::render(sf::RenderWindow *renderWindow, SpriteManager *manager, Player *player) {

	for (unsigned int i = 0; i < listUnite.size(); i++) {
		if(player->aDecouvertLaCase(listUnite[i]->getCoordX(), listUnite[i]->getCoordY()))
			listUnite[i]->render(renderWindow, couleur, manager);
	}
	for (unsigned int i = 0; i < listBatiment.size(); i++) {
		if (player->aDecouvertLaCase(listBatiment[i]->getCoordX(), listBatiment[i]->getCoordY()))
			listBatiment[i]->render(renderWindow, couleur, manager);
	}
}

void Player::update() {
	for (unsigned int i = 0; i < listUnite.size(); i++) {
		listUnite[i]->update();
	}
}

bool Player::aDecouvertLaCase(int x, int y) {
	return caseDecouverte[x][y];
}

void Player::decouvre() {
	for (unsigned int i = 0; i < listUnite.size(); i++) {
		Unite* unite = listUnite[i];
		for (int j = unite->getCoordY() - unite->getChampVision(); j < unite->getCoordY() + unite->getChampVision(); j++) {
			if (j >= 0 && j < MAP_HEIGTH) {
				for (int k = 1 + unite->getCoordX() - (unite->getChampVision() - abs(j - unite->getCoordY())); k < unite->getCoordX() + (unite->getChampVision() - abs(j - unite->getCoordY()));k++) {
					if (k >= 0 && k < MAP_WIDTH) {
						caseDecouverte[k][j] = true;
					}
				}
			}
		}
	}
}