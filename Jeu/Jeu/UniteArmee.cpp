#include "UniteArmee.h"

UniteArmee::UniteArmee(int _x, int _y, std::string _nom, std::string _desc, int _ressMax, int _deplacementMax, int _champVision, TypeUnite _type,
	int _munMax, int _rangeMax, int _rangeMin,Arme* principale, Arme* secondaire, bool bougeEtAttaque) : Unite(_x,_y,_nom, _desc, _ressMax, _deplacementMax, _champVision, _type) 
{
	estArmee = true;
	rangeMin = _rangeMin;
	rangeMax = _rangeMax;
	munMax = _munMax;
	munRestante = munMax;
	armePrincipale = principale;
	armeSecondaire = secondaire;
	peutBougerEtAttaquer = bougeEtAttaque;
}

int UniteArmee::getRangeMin()const
{
	return rangeMin+1;
}

int UniteArmee::getRangeMax()const
{
	return rangeMax+1;
}

int UniteArmee::getStockMunActuel()
{
	return munRestante;
}

int UniteArmee::getStockMaxMun()const
{
	return munMax;
}

void UniteArmee::attaque(Entite *ennemi)
{
	if (ennemi->isUnite()) {
		attaqueUnite((Unite*) ennemi);
	}
	else if (ennemi->isBatiment()) {
		//attaqueBatiment();
	}
	aAgi = true;
}

void UniteArmee::attaqueUnite(Unite *ennemi)
{
	if (ennemi->isAerienne()) {
		if (munRestante > 0) {
			ennemi->prendDegat(armePrincipale->getDegatAerien());
			munRestante--;
		}
		else if (munRestante <= 0 && armeSecondaire->getType() != "null"){
			ennemi->prendDegat(armeSecondaire->getDegatAerien());
		}
	}

	else if (ennemi->isInfanterie()) {
		if (munRestante > 0) {
			ennemi->prendDegat(armePrincipale->getDegatInfanterie());
			munRestante--;
		}
		else if (munRestante <= 0 && armeSecondaire->getType() != "null") {
			ennemi->prendDegat(armeSecondaire->getDegatInfanterie());
		}
	}

	else if (ennemi->isMaritime()) {
		if (munRestante > 0) {
			ennemi->prendDegat(armePrincipale->getDegatMarin());
			munRestante--;
		}
		else if (munRestante <= 0 && armeSecondaire->getType() != "null") {
			ennemi->prendDegat(armeSecondaire->getDegatMarin());
		}
	}

	else if (ennemi->isMotorise()) {
		if (munRestante > 0) {
			ennemi->prendDegat(armePrincipale->getDegatMotorise());
			munRestante--;
		}
		else if (munRestante <= 0 && armeSecondaire->getType() != "null") {
			ennemi->prendDegat(armeSecondaire->getDegatMotorise());
		}
	}
}

bool UniteArmee::getPeutBougerEtAttaquer() {
	return peutBougerEtAttaquer;
}

bool UniteArmee::peutAttaquer() {
	if (munRestante > 0) {
		return true;
	}
	else if (armeSecondaire->getType() != "null") {
		return true;
	}
	return false;
}
