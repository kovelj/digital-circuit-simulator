#include "Citanje.h"

Citanje::Citanje(fstream& inputFile, vector<Element*>& dig_kolo_,float&vreme_trajanja_,int& broj_elem_,vector<float>& vreme_)
{
	if (!dig_kolo_.empty())
	{
		int velicina=dig_kolo_.size();
		for (int i=0;i<velicina;i++)
		{
			dig_kolo_.pop_back();
		}
	}

	if (!vreme_.empty()) 
	{
		int velicina = vreme_.size();
		for (int i = 0; i < velicina; i++) 
		{
			vreme_.pop_back();
		}
	}
	vreme_trajanja_ = 0;
	broj_elem_ = 0;
	//fstream inputFile(filepath, ios::in);
	inputFile.peek();
	inputFile >> vreme_trajanja_;
	inputFile.peek();
	inputFile >> broj_elem_;

	int i = 0;
	while (i<broj_elem_)
	{
		int id; int tip;

		inputFile >> id;
		inputFile >> tip;

		switch (tip)
		{
		case 0:dig_kolo_.push_back(new Sonda(id, tip)); break;
		case 1:dig_kolo_.push_back(new TaktGen(inputFile,vreme_,vreme_trajanja_,id, tip)); break;
		case 2:dig_kolo_.push_back(new RucniGen(inputFile,vreme_,vreme_trajanja_,id, tip)); break;
		case 3:dig_kolo_.push_back(new NeKolo(inputFile, id, tip)); break;
		case 4:dig_kolo_.push_back(new IKolo(inputFile, id, tip)); break;
		case 5:dig_kolo_.push_back(new IliKolo(inputFile, id, tip)); break;
		}
		i++;
	}

	poveziKolo(inputFile,dig_kolo_,broj_elem_);
	


}

void Citanje::poveziKolo(fstream& inputFile, vector<Element*>& dig_kolo_,int broj_elem_)
{
	//Ova metoda zaravo strvara stablo//At least i hope
	//int i = 0;
	while (inputFile.peek()!=EOF)
	{
		int id1 = 0; int id2 = 0; int pin = 0;

		inputFile >> id1; 
		inputFile >> id2;
		inputFile >> pin;

		Element* prvi = nullptr;
		Element* drugi = nullptr;
		int i = 0;

		while ((!prvi || !drugi) && i < broj_elem_)
		{
			if (dig_kolo_[i]->vratiId() == id1)
			{
				prvi = dig_kolo_[i];
			}
			if (dig_kolo_[i]->vratiId() == id2)
			{
				drugi = dig_kolo_[i];
			}
			i++;
			
		}
		drugi->povezi(pin,prvi);


		prvi = nullptr;
		drugi = nullptr;
	}
}
