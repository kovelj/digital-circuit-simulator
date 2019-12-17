#include "Element.h"
const int Period = 2;


RucniGen::RucniGen(fstream& inputFile, vector<float>& vreme, float trajanje, int id, int tip) :Element(id, tip, 0,0)
{
	float promena = 0;
	if (!vremenski_tren_.empty())
	{
		for (int i = 0; i < vremenski_tren_.size(); i++)
		{
			vremenski_tren_.pop_back();
		}
	}
	//Ovo puni niz vremenski trenuci pormenama 
	int velicina = vreme.size();
		while(inputFile.peek()!='\n')
		{
			float korak;
			inputFile >> korak;
			promena += korak;
			if (korak > trajanje || korak <= 0) throw;
			
			else if(promena<trajanje)
			{
				vremenski_tren_.push_back(promena);
			}
			else if(velicina == 0) 
			{
				vreme.push_back(promena);
			}
		}
		
	//Ovaj deo prolazi kroz vremenske trenutke promena i ako neki trenutk promene nije obradjen da ga ubaci u vreme na kraj pa se kasnije sortira
		if (velicina != 0) 
		{
			for (int i = 0; i < vremenski_tren_.size(); i++)
			{
				promena = vremenski_tren_[i];
				bool nasao = false;
				int j = 0;
				while (!nasao && j < vreme.size())
				{
					if (promena == vreme[j])
					{
						nasao = true;
					}
					j++;
				}
				if (!nasao)
				{
					vreme.push_back(promena);
				}
			}
		}

	


}

RucniGen::~RucniGen()
{
	int velicina = vremenski_tren_.size();
	for (int i = 0; i < velicina; i++) 
	{
		vremenski_tren_.pop_back();
	}
}



//Ova metoda sluzi da promeni vrednost generatora u zahtevanom vremenskom trenutku
void RucniGen::promeniVrednost(float promena)
{
	
	bool nasao = false;
	int i = 0;
	while (!nasao && i<vremenski_tren_.size()) 
	{
		if (vremenski_tren_[i] == promena)
		{
			nasao = true;
		}
		i++;
	}
	if (nasao)
	{
		!vrednost_;
	}
}

TaktGen::TaktGen(fstream& inputFile,vector<float>& vreme,float trajanje ,int id,int tip) :Element(id,tip,0,0)
{
	inputFile >>frekvencija_;
	float korak = 1/ (frekvencija_ * Period);
	float promena = korak;
	float proizvod = korak * frekvencija_ *  Period;
	//Ovo mi je za sad najelegantnije resenje koje imam
	if (vreme.empty()) 
	{
		while (promena <= (float)trajanje) 
		{
			vremenski_tren_.push_back(promena);
			vreme.push_back(promena);
			promena+= korak;
		}
	}
	else 
	{

		while (promena <= trajanje) 
		{
			bool nasao = false;
			for (int i = 0; i < vreme.size(); i++) 
			{
				if (vreme[i] == promena) 
				{
					nasao = true;
				}
			}
			if (!nasao) 
			{
				vreme.push_back(promena);
			}
			promena += korak;
		}
	}
}

float TaktGen::vratiFrekv()
{
	return frekvencija_;
}


//Ova metoda takodje menja vrednost signala na generatoru 
void TaktGen::promeniVrednost(float promena)
{
	bool nasao = false;
	int i = 0;
	while (!nasao && i < vremenski_tren_.size()) 
	{
		if (vremenski_tren_[i] == promena) 
		{
			nasao = true;
		}
		if (nasao) 
		{
			!vrednost_;
		}
	}


}


IliKolo::IliKolo(fstream& inputFile, int id,int tip) :Element(id, tip,2,0)
{
	inputFile >> broj_pinova_;
	for (int i = 0; i < broj_pinova_; i++)
	{
		sinovi_.push_back(nullptr);
	}
}

void Element::povezi(int pin, Element* ulaz)
{//ovde je greska jer je ulsov los cak ni sam ne znam sta radi

	if (pin<broj_pinova_) 
	{
		if (sinovi_[pin] == nullptr) 
		{
			sinovi_[pin] = ulaz;
		}
	}

}


IKolo::IKolo(fstream& inputFile, int id,int tip) :Element(id, tip,2,0)
{
	inputFile >> broj_pinova_;
	for (int i = 0; i < broj_pinova_; i++)
	{
		sinovi_.push_back(nullptr);
	}
}



NeKolo::NeKolo(fstream& inputFile, int id,int tip) :Element(id, tip,1,0)
{
	for (int i = 0; i < broj_pinova_; i++)
	{
		sinovi_.push_back(nullptr);
	}

}



Sonda::Sonda(int id, int tip) :Element(id, tip, 1,0) 
{
	for (int i = 0; i < broj_pinova_; i++)
	{
		sinovi_.push_back(nullptr);
	}
	
}


Element::Element(int id, int tip,int podrazumevano,int neispitan):id_(id),broj_pinova_(podrazumevano),vrednost_(0),frekvencija_(0),neispitan_ulaz_(0)
{
	
	switch (tip) 
	{
	case 0:tip_=SONDA; break;
	case 1:tip_ = TAKT; break;
	case 2:tip_ = RUCNI; break;
	case 3:tip_ = NE; break;
	case 4:tip_ =I; break;
	case 5:tip_ =ILI ; break;
	}
}

Element::~Element()
{
	int velicina = sinovi_.size();
	for (int i = 0; i <velicina; i++)
	{
		sinovi_.pop_back();
	}
}

int Element::brojPinova()
{
	return broj_pinova_;
}

bool Element::vecObidjen()
{
	return broj_pinova_==sinovi_.size()-1;
}

int Element::vratiId()
{
	return id_;
}




int Element::vratiVrednost()
{
	return vrednost_;
}



Tip Element::vratiTip()
{
	return tip_;
}

float Element::vratiFrekv()
{
	return frekvencija_;
}

void Element::promeniVrednost(float)
{
	!vrednost_;
}

Element* Element::vratiNeispitanUlaz()
{
	if (sinovi_[neispitan_ulaz_] != nullptr)
	{
		
		return sinovi_[neispitan_ulaz_++];
	}
	else throw;
}

