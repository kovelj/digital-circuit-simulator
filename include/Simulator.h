#pragma once

#include "Citanje.h"
#include"Element.h"
#include"Ispis.h"

class Simulator {
public:

	Simulator();
	~Simulator();

	void loadCircuit(const std::string&);
	void simulate(const std::string&);
	void nadjiUlaze();
	void otkucajVreme(float);
	void srediVreme();
	void resetujKolo();
	void resetujGeneratore();
	
private:

	std::vector<Element*> dig_kolo_;
	std::vector<Element*> izlazi_;
	std::vector<float>    vreme_;

	int broj_elem_;
	float vreme_trajanja_;
};