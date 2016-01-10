#pragma once
#include <vector>
#include <string>

class Technologie {

private:
	std::string nom;
	int coutEnergie;
	int coutVivre;
	int coutMetal;
	int coutPetrole;
	std::vector<Technologie> techSuivante;
	std::vector<Technologie> techPrecedente;
	bool estRecherche;

public:
	Technologie(std::string nom, int coutEnergie, int coutVivre, int coutMetal, int coutPetrole);
	bool verifierCoutTechnologie(int energie, int essence, int metaux, int vivre);
	bool verifierSiRecherchable();

	bool getEstRecherche();
	void setEstRecherche(bool status);
	void setTechSuivante(Technologie suivante);
	void setTechPrecedente(Technologie precedente);
};
