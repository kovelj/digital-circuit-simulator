#pragma once

#include"Element.h"
#include<stack>

class Ispis {
public:

	~Ispis();

	//Za ispis mi nije potrebna kopija jer je dovoljna samo jedna njena instanca

	void isprazniVektore();
	void izracunajMedjurezultat(Element*);
	void vrednostNaIzlazu(Element*, float);
	void kreirajNoviFajl(const std::string&, int, float);
	void upisiPirkupljeniRezultat(float);
	
private:
	//Koristim vektor iako realno znam koliko ce ih biti ali je lakse raditi sa njima 
	//Koristim ponovo vreme_promena_ zbog slucaja da se za neki od trenutaka ne desi, jer pa ko kaze da mora 

	std::stack<int> stek_vrednosti_;
	std::stack<Element*> stek_cvorova_;

	std::vector<float> promena_;
	std::vector<float> vreme_promene_;
};