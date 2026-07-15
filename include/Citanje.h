#pragma once

#include"Element.h"

class Citanje {
public:

	Citanje(std::fstream&, std::vector<Element*>& dig_kolo_, float&, int&, std::vector<float>&, std::vector<Element*>&);

	//Zabranjuje se kopiranje jer mi je potrebna samo jedna instanca klase
	Citanje(const Citanje&)=delete;
	
	//Ova metoda pravi N-arno stablo
	void poveziKolo(std::fstream&, std::vector<Element*>&,int);
};