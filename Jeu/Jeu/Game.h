#pragma once

#include <stack>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "SpriteManager.h"
#include "Map.h"
#include "Minimap.h"
#include "Player.h"
#include "UniteArmee.h"
#include "Interface.h"

class Game
{
private:

	bool brouillardDeGuerre;
    void loadTextures();
	void loadSprites();	

	void definitionCase();
	void definitionCaseUnite(int xOrig, int yOrig, int nbCase);
	void definitionCaseUniteArmee(int xOrig, int yOrig, int nbCase, int nbCaseAttaque);
	void definitionCaseUniteDistance(int xOrig, int yOrig, int nbCase, int rangeMin, int rangeMax);

	sf::Vector2i definitionCaseClique(int x, int y);
	void surbrillanceCaseDeplacement();
	void deplacementAutoPourAttaque(int ecartX, int ecartY, int distance, UniteArmee* unite, int posXEnnemi, int posYEnnemi);

	bool testClicZoneJeu(int x, int y);
	bool testUniteAlliee(int x, int y);
	bool testEntiteEnnemie(int x, int y);
	bool testUniteSelectionneTypeCase(int x, int y);

public:
    Game();

    sf::RenderWindow m_window;
    sf::View m_view, m_viewMinimap, m_viewInterface;
    double c_view[2], m_tour, m_nbJoueur, m_numJoueurActif;
	sf::Vector2i centreImage;
    TextureManager m_textureManager;
	SpriteManager m_spriteManager;

	std::vector<sf::Vector2f> m_deplacement, m_attaque;

    Map m_map = Map();
	Minimap m_minimap;

	Player *m_players[NB_JOUEUR_MAX], *m_playerActif;

    void render();
	Player* getPlayerActif();

	Unite* m_uniteSelectionne;
	Batiment* m_batimentSelectionne;

	Interface m_interface;

	void actionUnite(sf::Vector2i caseClique);

	void clic(int x, int y);
	void clicInterface(int x, int y);
	void clicZoneJeu(int x, int y);
	void clicUnite(int x, int y, Unite *unite);
	void clicBatiment(int x, int y);

	void joueurSuivant();
	void finTour();
	void selection(sf::Vector2i caseClique, int x, int y);
	void deselection();
};