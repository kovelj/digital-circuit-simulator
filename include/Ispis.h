#ifndef ISPIS_H
#define ISPIS_H

#include"Element.h"

#include<stack>


using namespace std;

class Ispis {

public:

	~Ispis();

	//Za ispis mi nije potrebna kopija jer je dovoljna samo jedna njena instanca

	void isprazniVektore();
	void izracunajMedjurezultat(Element *);
	void vrednostNaIzlazu(Element*,float );
	void kreirajNoviFajl(const string&,int,float);
	void upisiPirkupljeniRezultat(float);
	
private:
	//Koristim vektor iako realno znam koliko ce ih biti ali je lakse raditi sa njima 
	//Koristim ponovo vreme_promena_ zbog slucaja da se za neki od trenutaka ne desi, jer pa ko kaze da mora 

	stack<int> stek_vrednosti_;
	stack<Element*> stek_cvorova_;

	vector<float> promena_;
	vector<float> vreme_promene_;
};
#endif// ! ISPIS_H