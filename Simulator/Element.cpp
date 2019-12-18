#include "Element.h"
const int Period = 2;


RucniGen::RucniGen(fstream& inputFile, vector<float>& vreme, float trajanje, int id, int tip) :Element(id, tip, 0,0,0)
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

	//Izlazi se iz petlje ako je nadjena odgovarajuca vrednost promene  u suprotnom ide do kraja
	while (!nasao && i<vremenski_tren_.size()) 
	{
		if (vremenski_tren_[i] == promena)
		{
			vrednost_ = !vrednost_;
			nasao = true;
		}
		i++;
	}
	
}

TaktGen::TaktGen(fstream& inputFile,vector<float>& vreme,float trajanje ,int id,int tip) :Element(id,tip,0,0,0)
{
	inputFile >>frekvencija_;
	float korak = 1/ (frekvencija_ * Period);
	float promena = korak;

	//Ovo mi je za sad najelegantnije resenje koje imam, i zasniva se na tome da ako je niz vreme prazan ja ga onda samo napunim sa vrednostima promene
	if (vreme.size()==1) 
	{
		//Bez trenutka koji je jedank vremenu zavrsetka simulacije
		while (promena <trajanje) 
		{
			vremenski_tren_.push_back(promena);
			vreme.push_back(promena);
			promena+= korak;
		}
	}
	//Usuprotnom ako vreme nije prazno onda se upisuju ne ponovljene vrednosti
	else 
	{
		//While petlja koja mi prolazi kroz sve trenutke promena ne ukljucujuci vreme kada se zavrsava
		while (promena < trajanje) 
		{
			vremenski_tren_.push_back(promena);
			//for petlja koja trazi da li ima vec isti trenutak ucitan
			bool nasao = false;
			for (int i = 0; i < vreme.size(); i++) 
			{
				if (vreme[i] == promena) 
				{
					nasao = true;
				}
			}

			//Ako nije nadjen duplikat onda se ubaci vrednost na kraj
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
			vrednost_=!vrednost_;
			nasao = true;
			
		}
		else 
		{
			i++;
		}
	}


}


IliKolo::IliKolo(fstream& inputFile, int id,int tip) :Element(id, tip,2,0,0)
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


IKolo::IKolo(fstream& inputFile, int id,int tip) :Element(id, tip,2,0,0)
{
	inputFile >> broj_pinova_;
	for (int i = 0; i < broj_pinova_; i++)
	{
		sinovi_.push_back(nullptr);
	}
}



NeKolo::NeKolo(fstream& inputFile, int id,int tip) :Element(id, tip,1,0,0)
{
	for (int i = 0; i < broj_pinova_; i++)
	{
		sinovi_.push_back(nullptr);
	}

}



Sonda::Sonda(int id, int tip) :Element(id, tip, 1,0,0) 
{
	//Inicijalizuje se niz pinova sa nullptr
	for (int i = 0; i < broj_pinova_; i++)
	{
		sinovi_.push_back(nullptr);
	}
	
}


Element::Element(int id, int tip,int podrazumevano,int neispitan,int broj_prolazaka=0):id_(id),broj_pinova_(podrazumevano),vrednost_(0),frekvencija_(0),broj_prolazaka_(broj_prolazaka)
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
		sinovi_[velicina-1-i] = nullptr;
		delete sinovi_[velicina-1-i];
		sinovi_.pop_back();
	}
}



int Element::brojPinova()
{
	return broj_pinova_;
}

bool Element::vecObidjen()
{
	//Ispituje da li je jedan cvor iscitan do kraja
	if (broj_prolazaka_ == sinovi_.size())
	{
		return true;
	}
	else 
	{
		return false;
	}
}

int Element::vratiId()
{
	return id_;
}

void Element::resetujElemente()
{
	if(tip_!=RUCNI && tip_ != TAKT)
	vrednost_ = 0;
	broj_prolazaka_ = 0;
}

void Element::resetujGenratore()
{
	if (tip_ == RUCNI || tip_ == TAKT) 
	{
		vrednost_ = 0;
	}
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
	vrednost_ = !vrednost_;;
}

Element* Element::vratiNeispitanUlaz()
{
	if (sinovi_.size()!=broj_prolazaka_)

	{
		return sinovi_[broj_prolazaka_++];
	}
}

