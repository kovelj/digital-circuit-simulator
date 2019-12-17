#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Citanje.h"
#include"Element.h"
#include"Ispis.h"

#include<string>
#include<vector>
#include<iostream>
using namespace std;
using namespace std;
class Simulator {
public:
	Simulator() :broj_elem_(0),vreme_trajanja_(0){}
	~Simulator();
	void loadCircuit(const string&);
	void simulate(const string& );
	void nadjiUlaze();
	void otkucajVreme(float );
	void srediVreme();
	void resetujKolo();
	
private:
	//Pitanje vezano za jednoobraznost koda da li i ovo da drzim kao vector ili kao listu
	vector<Element*> dig_kolo_;
	vector<float> vreme_;
	vector<Element*>izlazi_;
	float vreme_trajanja_;
	int broj_elem_;
};
#endif//