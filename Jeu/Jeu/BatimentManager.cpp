#include "BatimentManager.h"

BatimentManager::BatimentManager()
{
	m_batiments["PuitPetrole"] = new ProductionRessource(0, 0, "Puit à pétrole", "Batiment qui produit du pétrole", Ressource::PETROLE, 100, Ressource::PETROLE, 5);
}


void BatimentManager::addBatiment(const std::string& name, Batiment batiment)
{
	m_batiments[name] = &batiment;
}

Batiment* BatimentManager::getRef(const std::string& batiment)
{
	return m_batiments.at(batiment);
}

Batiment* BatimentManager::creerBatiment(const std::string &unite, int x, int y)
{
	Batiment* nouveauBatiment;
	if (getRef(unite)->isProductionRessource()) {
		nouveauBatiment = new ProductionRessource(*(ProductionRessource*)getRef(unite));
	}
	else if (getRef(unite)->isProductionUnite())
	{
		nouveauBatiment = new ProductionsUnite(*(ProductionsUnite*)getRef(unite));
	}
	else {
		nouveauBatiment = new Batiment(*getRef(unite));
	}

	nouveauBatiment->setCoord(x, y);
	return nouveauBatiment;
}