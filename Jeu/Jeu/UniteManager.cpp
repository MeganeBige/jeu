#include "UniteManager.h"
UniteManager::UniteManager() {
	m_unites["Soldat"] =  new UniteArmee(0,0,"Soldat","Unite de corps à corps basique." ,50, 5, 4, TypeUnite::INFANTERIE, 100, 0, 0, manager.getRef("ScieHache"), manager.getRef("null"), true);
	m_unites["SoldatArmee"] =  new UniteArmee(0, 0, "Soldat arme", "Unite de combat à distance.", 50, 5, 4, TypeUnite::INFANTERIE,20, 3, 0, manager.getRef("Balle"), manager.getRef("null"), true);
	m_unites["Demolisseur"] = new UniteArmee(0, 0, "Demolisseur", "Unite anti-vehicule.", 50, 4, 4, TypeUnite::INFANTERIE, 15, 4, 1, manager.getRef("Roquette"), manager.getRef("Balle"), true);
	m_unites["Chasseur"] = new UniteArmee(0, 0, "Chasseur", "Unite aerienne anti-aerienne.", 30, 12, 9, TypeUnite::AERIENNE, 10, 3, 0, manager.getRef("Missile"), manager.getRef("null"), true);
	m_unites["Bombardier"] = new UniteArmee(0, 0, "Bombardier", "Unite aerienne tres puissante. Ne peut pas attaquer les unites aeriennes.", 30, 10, 8, TypeUnite::AERIENNE, 5, 0, 0, manager.getRef("Bombe"), manager.getRef("null"), true);
	m_unites["Helicoptere"] = new UniteArmee(0, 0, "Helicoptere", "Unite aerienne polyvalente.", 35, 7, 5, TypeUnite::AERIENNE, 15, 3, 0, manager.getRef("Roquette"), manager.getRef("Balle"), true);
	m_unites["Jeep"] = new UniteArmee(0, 0, "Jeep", "Unite motorisee de reconnaissance", 60, 7, 9, TypeUnite::MOTORISE, 15, 2, 0, manager.getRef("Balle"), manager.getRef("null"), true);
	m_unites["Char"] = new UniteArmee(0, 0, "Char", "Unite motorisee puissante", 60, 6, 5, TypeUnite::MOTORISE, 10, 3, 0, manager.getRef("Canon"), manager.getRef("Balle"), true);
	m_unites["Artillerie"] = new UniteArmee(0, 0, "Artillerie", "Unite motorisee de longue distance", 60, 4, 6, TypeUnite::MOTORISE, 5, 5, 0, manager.getRef("Canon"), manager.getRef("null"), false);
	m_unites["DCA"] = new UniteArmee(0, 0, "DCA", "Unite motorisee anti-aerienne", 60, 7, 6, TypeUnite::MOTORISE, 15, 2, 1, manager.getRef("Missile"), manager.getRef("null"), true);
	m_unites["Cuirasse"] = new UniteArmee(0, 0, "Cuirasse", "Unite maritime de longue distance", 30, 8, 6, TypeUnite::MARITIME, 5, 8, 3, manager.getRef("Canon"), manager.getRef("null"), false);
	m_unites["Torpilleur"] = new UniteArmee(0, 0, "Torpilleur", "Unite maritime anti-martime", 30, 10, 8, TypeUnite::MARITIME, 10, 3, 0, manager.getRef("Torpille"), manager.getRef("null"), true);
	m_unites["Corvette"] = new UniteArmee(0, 0, "Corvette", "Unite maritime anti-aerienne", 30, 10, 8, TypeUnite::MARITIME, 10, 3, 0, manager.getRef("Missile"), manager.getRef("null"), true);
}

void UniteManager::addUnite(const std::string &name, Unite unite)
{
	m_unites[name] = &unite;
}

Unite* UniteManager::getRef(const std::string &unite)
{
	return m_unites.at(unite);
}

Unite* UniteManager::creerUnite(const std::string &unite, int x, int y)
{
	Unite* nouvelleUnite;
	if (getRef(unite)->isArmee()) {
		nouvelleUnite = new UniteArmee(*(UniteArmee*)getRef(unite));
	}
	else {
		nouvelleUnite = new Unite(*getRef(unite));
	}
	
	nouvelleUnite->setCoord(x, y);
	return nouvelleUnite;
}