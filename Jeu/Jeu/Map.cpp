#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"

Map::Map(int width, int heigth)
{
	m_width = width;
	m_heigth = heigth;
	m_tiles = new Tile* [m_width];
	for (int i = 0; i < m_width; i++) {
		m_tiles[i] = new Tile[m_heigth];
	}
	srand((unsigned int) time(NULL));
	std::cout << "Creation de la map" << std::endl;
    std::vector<int> tab;
    for (int i = 0; i < m_width; ++i) {
        for (int j = 0; j < m_heigth; ++j) {
            tab.push_back(i + j);
        }
    }
    std::random_shuffle(tab.begin(), tab.end());

    for (int i = 0; i < m_width; ++i) {
        for (int j = 0; j < m_heigth; ++j) {
            permutation[i+j] = (unsigned int)(tab.at((unsigned long)(i + j)));
        }
    }
	mapGenerator();
	std::cout << "Creation de la map terminee" << std::endl;
}

void Map::mapGenerator()
{
    for (int i = 0; i < m_width; ++i) {
        for (int j = 0; j < m_heigth; ++j) {
            m_tiles[i][j] = Tile(whichType(bruitPerlin(i+0.5f,j+0.5f,10)));
        }
    }
}

float Map::bruitPerlin(float x, float y, float res)
{
    float tempX, tempY;
    int x0, y0, ii, jj, gi0, gi1, gi2, gi3;
    float unit = (float)(1.0f / sqrt(2));
    float tmp, s, t, u, v, Cx, Cy, Li1, Li2;
    float gradient2[8][2] = {{unit,unit},{-unit,unit},{unit,-unit},{-unit,-unit},
                             {1,0},{-1,0},{0,1},{0,-1}};

    x /= res;
    y /= res;

    x0 = (int)(x);
    y0 = (int)(y);

    ii = x0 & 255;
    jj = y0 & 255;

    gi0 = permutation[ii + permutation[jj]] % 8;
    gi1 = permutation[ii + 1 + permutation[jj]] % 8;
    gi2 = permutation[ii + permutation[jj + 1]] % 8;
    gi3 = permutation[ii + 1 + permutation[jj + 1]] % 8;

    tempX = x - x0;
    tempY = y - y0;
    s = gradient2[gi0][0] * tempX + gradient2[gi0][1] * tempY;

    tempX = x - (x0 + 1);
    tempY = y - y0;
    t = gradient2[gi1][0] * tempX + gradient2[gi1][1] * tempY;

    tempX = x - x0;
    tempY = y - (y0 + 1);
    u = gradient2[gi2][0] * tempX + gradient2[gi2][1] * tempY;

    tempX = x - (x0 + 1);
    tempY = y - (y0 + 1);
    v = gradient2[gi3][0] * tempX + gradient2[gi3][1] * tempY;

    tmp = x - x0;
    Cx = 3 * tmp * tmp - 2 * tmp * tmp * tmp;

    Li1 = s + Cx * (t - s);
    Li2 = u + Cx * (v - u);

    tmp = y - y0;
    Cy = 3 * tmp * tmp - 2 * tmp * tmp * tmp;

    return Li1 + Cy * (Li2 - Li1);
}

TypeCase Map::whichType(float hauteur)
{
    if (hauteur <= -0.3f) return TypeCase::MER;
    else if (hauteur <= -0.25f) return TypeCase::PLAGE;
	else if (hauteur <= -0.1f) return TypeCase::PLAINE;
	else if (hauteur <= -0.05f) return TypeCase::MARAIS;
    else if (hauteur <= 0.15f) return TypeCase::PLAINE;
	else if (hauteur <= 0.20f) return TypeCase::FORET;
	else if (hauteur <= 0.35f) return TypeCase::PLAINE;
    else if (hauteur <= 0.4f) return TypeCase::COLINE;
    else return TypeCase::MONTAGNE;
}

Tile Map::getTile(int x, int y)
{
	return m_tiles[x][y];
}

void Map::render(sf::RenderWindow *renderWindow, SpriteManager *manager, sf::Vector2i nbCase, sf::Vector2i caseCentrale)
{
	for (int i = caseCentrale.x - ((nbCase.x / 2) + 1); i < caseCentrale.x + ((nbCase.x / 2) + 1); ++i)
	{
		if (i >= 0 && i < m_width) {
			for (int j = caseCentrale.y - ((nbCase.y / 2) + 2); j < caseCentrale.y + ((nbCase.y / 2) + 1); ++j)
			{
				if (j >= 0 && j < m_heigth) {
					sf::Sprite terrain, ressource;
					switch (m_tiles[i][j].getTypeCase())
					{
					case TypeCase::PLAINE:
						terrain = manager->getRef("plaine");
						break;
					case TypeCase::PLAGE:
						terrain = manager->getRef("plage");
						break;
					case TypeCase::MONTAGNE:
						terrain = manager->getRef("montagne");
						break;
					case TypeCase::MER:
						terrain = manager->getRef("mer");
						break;
					case TypeCase::FORET:
						terrain = manager->getRef("foret");
						break;
					case TypeCase::MARAIS:
						terrain = manager->getRef("marais");
						break;
					case TypeCase::COLINE:
						terrain = manager->getRef("coline");
						break;
					case TypeCase::VILLE:
						terrain = manager->getRef("ville");
						break;
					case TypeCase::RUINE:
						terrain = manager->getRef("ruine");
						break;
					}
					switch (m_tiles[i][j].getRessource()) {
					case Ressource::VIVRES:
						ressource = manager->getRef("vivre");
						break;
					case Ressource::METAL:
						ressource = manager->getRef("metal");
						break;
					case Ressource::PETROLE:
						ressource = manager->getRef("petrole");
						break;
					default:
						break;
					}

					terrain.setPosition(sf::Vector2f(i*SPRITE, j*SPRITE));
					ressource.setPosition(sf::Vector2f(i*SPRITE, j*SPRITE));
					renderWindow->draw(terrain);
					renderWindow->draw(ressource);
				}
			}
		}
	}
}

// Render avec brouillard de guerre
void Map::render(sf::RenderWindow *renderWindow, SpriteManager *manager, Player *player, sf::Vector2i nbCase, sf::Vector2i caseCentrale)
{
	for (int i = caseCentrale.x - ((nbCase.x / 2) + 1); i < caseCentrale.x + ((nbCase.x / 2) + 1); ++i)
	{
		if (i >= 0 && i < m_width) {
			for (int j = caseCentrale.y - ((nbCase.y / 2) + 2); j < caseCentrale.y + ((nbCase.y / 2) + 1); ++j)
			{
				if (j >= 0 && j < m_heigth && player->aDecouvertLaCase(i, j)) {
					sf::Sprite terrain, ressource;
					switch (m_tiles[i][j].getTypeCase())
					{
					case TypeCase::PLAINE:
						terrain = manager->getRef("plaine");
						break;
					case TypeCase::PLAGE:
						terrain = manager->getRef("plage");
						break;
					case TypeCase::MONTAGNE:
						terrain = manager->getRef("montagne");
						break;
					case TypeCase::MER:
						terrain = manager->getRef("mer");
						break;
					case TypeCase::FORET:
						terrain = manager->getRef("foret");
						break;
					case TypeCase::MARAIS:
						terrain = manager->getRef("marais");
						break;
					case TypeCase::COLINE:
						terrain = manager->getRef("coline");
						break;
					case TypeCase::VILLE:
						terrain = manager->getRef("ville");
						break;
					case TypeCase::RUINE:
						terrain = manager->getRef("ruine");
						break;
					}
					switch (m_tiles[i][j].getRessource()) {
					case Ressource::VIVRES:
						ressource = manager->getRef("vivre");
						break;
					case Ressource::METAL:
						ressource = manager->getRef("metal");
						break;
					case Ressource::PETROLE:
						ressource = manager->getRef("petrole");
						break;
					default:
						break;
					}

					terrain.setPosition(sf::Vector2f(i*SPRITE, j*SPRITE));
					ressource.setPosition(sf::Vector2f(i*SPRITE, j*SPRITE));
					renderWindow->draw(terrain);
					renderWindow->draw(ressource);
				}
			}
		}
	}
}

int Map::getWidth() {
	return m_width;
}

int Map::getHeigth() {
	return m_heigth;
}

void Map::loadMap(std::string name)
{
	sf::Image topo;
	topo.loadFromFile("media/map/" + name + ".png");
	m_width = topo.getSize().x;
	m_heigth = topo.getSize().y;

	m_tiles = new Tile*[m_width];
	for (int i = 0; i < m_width; i++) {
		m_tiles[i] = new Tile[m_heigth];
	}
	srand((unsigned int)time(NULL));
	std::cout << "Chargement de la map" << std::endl;

	for (unsigned int i = 0; i < m_width; i++) {
		for (unsigned int j = 0; j < m_heigth; j++) {
			sf::Color color = topo.getPixel(i, j);

			if (color == sf::Color(0,255,0)) {
				m_tiles[i][j] = Tile(TypeCase::PLAINE);
			}
			else if (color == sf::Color(0,176,0)) {
				m_tiles[i][j] = Tile(TypeCase::FORET);
			}
			else if (color == sf::Color(131,193,42)) {
				m_tiles[i][j] = Tile(TypeCase::MARAIS);
			}
			else if (color == sf::Color(0,0,255)) {
				m_tiles[i][j] = Tile(TypeCase::MER);
			}
			else if (color == sf::Color(159,128,5)) {
				m_tiles[i][j] = Tile(TypeCase::MONTAGNE);
			}
			else if (color == sf::Color(193,163,42)) {
				m_tiles[i][j] = Tile(TypeCase::COLINE);
			}
			else if (color == sf::Color(112,112,112)) {
				m_tiles[i][j] = Tile(TypeCase::RUINE);
			}
			else if (color == sf::Color(0,0,0)) {
				m_tiles[i][j] = Tile(TypeCase::VILLE);
			}
			else if (color == sf::Color(255,255,0)) {
				m_tiles[i][j] = Tile(TypeCase::PLAGE);
			}
			else {
				std::cerr << "Pixel (" <<i<<','<<j<<") de couleur inconnue"<< std::endl;
				std::string str = "Couleur (" + to_string(color.r) + ',' + to_string(color.g) + ',' + to_string(color.b) + ',' + to_string(color.a) + ')';
				std::cerr << str << std::endl;
				sf::Clock clock;
				clock.restart();
				while (clock.getElapsedTime().asSeconds() < 5) {

				}
				exit(EXIT_FAILURE);
			}
		}
	}
	std::cout << L"Chargement terminé" << std::endl;
}