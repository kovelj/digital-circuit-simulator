#ifndef CITANJE_H_
#define CITANJE_H_

#include"Element.h"



using namespace std;

class Citanje {

public:

	Citanje(fstream&, vector<Element*>& dig_kolo_,float&,int&,vector<float>&,vector<Element*>&);

	//Zabranjuje se kopiranje jer mi je potrebna samo jedna instanca klase
	Citanje(const Citanje&)=delete;
	
	//Ova metoda pravi N-arno stablo
	void poveziKolo(fstream&,vector<Element*>&,int);
	
};
#endif// ! CITANJE_H_