#include "Citanje.h"
#include"Izuzeci.h"
Citanje::Citanje(std::fstream& inputFile, std::vector<Element*>& dig_kolo_, float&vreme_trajanja_, int& broj_elem_, std::vector<float>& vreme_, std::vector<Element*>& izlazi)
{
	//Ako mi dig_kolo_ nije prazno, a nisam stigao do kraja programa pa nisam zvao destruktor, shodno tome ja ih ovde praznim ako vec nisu 
	if (!dig_kolo_.empty()) {
		int velicina = dig_kolo_.size();
		for (int i=0;i<velicina;i++) {
			delete dig_kolo_[velicina-i-1];
			dig_kolo_.pop_back();
		}
	}

	if (!vreme_.empty()) {
		int velicina = vreme_.size();
		for (int i = 0; i < velicina; i++)  {
			vreme_.pop_back();
		}
	}

	if (!izlazi.empty()) {
		int velicina = izlazi.size();
		for (int i = 0; i < velicina; i++) {
			izlazi[velicina - i - 1] = nullptr;
			delete izlazi[velicina - i - 1];
			izlazi.pop_back();
		}
	}

	//Ovo radim zato sto mi je potrebno da ispitam u nultoom trenutku svakako,a moze se desiti da nijedan od generatora nema ovo kao kriticni trenutak
	vreme_.push_back(0);

	//Kao dobro praksa onda ja cu vratiti staticka polja kao u destruktoru vratiti na pocetnu vrednost

	vreme_trajanja_ = 0;
	broj_elem_ = 0;
	
	try {
		inputFile.peek();
		inputFile >> vreme_trajanja_;
		if (vreme_trajanja_ <= 0) {
			throw std::invalid_argument("Simulation duration has to be greater than 0.");
		}

		inputFile.peek();
		inputFile >> broj_elem_;

		if (broj_elem_ <= 0) {
			throw std::invalid_argument("Number of components in circuit has to be greater than 0.");
		}
	}
	catch (const std::invalid_argument& e) {
		std::cout<<e.what();
	}

	//Ova petlja cita drugi deo fajla koji sadrzi elemente sa njihovom tehnickom specifikacijom ako je, takodje uociti polimorfizam jer se posao iscitavanja delegira odgovarajucem elementu
	int i = 0;
	while (i < broj_elem_) {
		int id; int tip;
		try	{
			inputFile >> id;
			inputFile >> tip;
			if (id < 0) {
				throw std::invalid_argument("Component ID has to be greater than 0.");
			}
			if (tip != 0 && tip != 1 && tip != 2 && tip != 3 && tip != 4 && tip != 5) {
				throw std::invalid_argument("Component not supported in simulator.");
			}
		}
		
		catch (const std::invalid_argument& e) {
			std::cout<<e.what();
		}

		switch (tip) {
		case 0:dig_kolo_.push_back(new Sonda(id, tip)); break;
		case 1:dig_kolo_.push_back(new TaktGen(inputFile,vreme_,vreme_trajanja_,id, tip)); break;
		case 2:dig_kolo_.push_back(new RucniGen(inputFile,vreme_,vreme_trajanja_,id, tip)); break;
		case 3:dig_kolo_.push_back(new NeKolo(inputFile, id, tip)); break;
		case 4:dig_kolo_.push_back(new IKolo(inputFile, id, tip)); break;
		case 5:dig_kolo_.push_back(new IliKolo(inputFile, id, tip)); break;
		}
		i++;
	}

	//Metoda koja povezuje kolo, nakon sto se ono ucita
	poveziKolo(inputFile,dig_kolo_,broj_elem_);
}

void Citanje::poveziKolo(std::fstream& inputFile, std::vector<Element*>& dig_kolo_, int broj_elem_)
{
	//Metoda koja povezuje stablo,tako sto prolazi kroz niz elemenata
	while (inputFile.peek()!=EOF) {
		Element* prvi = nullptr;
		Element* drugi = nullptr;

		int id1 = 0; int id2 = 0; int pin = 0;

		try {
			inputFile >> id1;
			inputFile >> id2;
			inputFile >> pin;

			if (id1 < 0 || id2 < 0 || pin < 0) {
				throw std::runtime_error("ID or PIN number must be positive.");
			}

			if (id1 == id2) {
				throw std::logic_error("Feedback loop are not allowed in simulator.");
			}

			int i = 0;

			while ((!prvi || !drugi) && i < broj_elem_) {
				if (dig_kolo_[i]->vratiId() == id1) {
					prvi = dig_kolo_[i];
				}
				if (dig_kolo_[i]->vratiId() == id2) {
					drugi = dig_kolo_[i];
				}
				i++;
			}

			if (prvi == nullptr || drugi == nullptr) {
				throw std::logic_error("You did not define elements for connection.");
			}

			drugi->povezi(pin, prvi);
		}

		catch (const std::exception& e) {
			std::cout << e.what();
		}

		prvi = nullptr;
		drugi = nullptr;
	}
}
