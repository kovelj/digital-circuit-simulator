#ifndef IZUZECI_H
#define IZUZECI_H
#include<exception>
using namespace std;
class Izuzeci : public exception {

public:
	Izuzeci(const char* poruka_o_gresci_) :exception(poruka_o_gresci_){}
};


class NegativanBroj :public Izuzeci {

public:

	NegativanBroj(const char* poruka_o_gresci_) :Izuzeci(poruka_o_gresci_) {}
};

class NedozvoljenTip :public Izuzeci {

public:

	NedozvoljenTip(const char* poruka_o_gresci_) :Izuzeci(poruka_o_gresci_) {}
};

class NepravilnaVeza :public Izuzeci {

public:

	NepravilnaVeza(const char* poruka_o_gresci_) :Izuzeci(poruka_o_gresci_) {}

};

class Prekoracenje:public Izuzeci {

	public:
		Prekoracenje(const char* poruka_o_gresci) :Izuzeci(poruka_o_gresci) {}
};
#endif //!IZUZECI_H