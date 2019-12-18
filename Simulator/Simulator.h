#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Citanje.h"
#include"Element.h"
#include"Ispis.h"

class Simulator {

public:

	Simulator();
	~Simulator();

	void loadCircuit(const string&);
	void simulate(const string& );
	void nadjiUlaze();
	void otkucajVreme(float );
	void srediVreme();
	void resetujKolo();
	void resetujGeneratore();
	
private:

	vector<Element*> dig_kolo_;
	vector<Element*>izlazi_;
	vector<float> vreme_;

	int broj_elem_;
	float vreme_trajanja_;
};
#endif//