#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "Batiment.h"
#include "ProductionsRessource.h"
#include "ProductionsUnite.h"

class BatimentManager {
private:
	std::map<std::string, Batiment*> m_batiments;

public:
	BatimentManager();

	void addBatiment(const std::string& name, Batiment unite);

	Batiment* getRef(const std::string& unite);
	Batiment* creerBatiment(const std::string &unite, int x, int y);
};