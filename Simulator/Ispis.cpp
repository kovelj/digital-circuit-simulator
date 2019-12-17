#include "Ispis.h"



void Ispis::isprazniVektore()
{
	if (!vreme_promene_.empty() )
	{
		int velicina = vreme_promene_.size();

		for (int i = 0; i < velicina; i++) 
		{
			vreme_promene_.pop_back();
		}

	}

	if (!promena_.empty()) 
	{
		int velicina = promena_.size();

		for (int i = 0; i < velicina; i++)
		{
			vreme_promene_.pop_back();
		}
	}
}

void Ispis::izracunajMedjurezultat(Element * element)
{
	Tip tip = element->vratiTip();
	
	if (tip == I) 
	{
		int velicina = element->brojPinova();
		int rezultat = 1;
		for (int i = 0; i < velicina; i++)
		{
			rezultat &= stek_vrednosti_.top();
			stek_vrednosti_.pop();
			stek_vrednosti_.push(rezultat);

		}

	}

	if (tip == ILI) 
	{
		int velicina = element->brojPinova();
		int rezultat = 0;
		for (int i = 0; i < velicina; i++) 
		{
			rezultat |= stek_vrednosti_.top();
			stek_vrednosti_.pop();
			stek_vrednosti_.push(rezultat);

		}
	}
	
	if (tip == NE) 
	{
		int vrednost = stek_vrednosti_.top();
		stek_vrednosti_.pop();
		!vrednost;
		stek_vrednosti_.push(vrednost);
	}
}

void Ispis::vrednostNaIzlazu(Element* koren,float vreme_promene)
{
	Element* cvor = koren, * poslednjiPoseceni = nullptr;
	

	if (koren == nullptr) 
	{
		throw;
	}

	while (!stek_cvorova_.empty() || cvor != nullptr) 
	{
		//Pitati ADRIANA STA DA SE RADI U SLUCAJU DA CITAVO KOLO NIJE POVEZANO
		
		//U slucaju da je cvor nije generator desice se prolazak kroz sinove ne obradjene
		if (cvor != nullptr && cvor->vecObidjen() && cvor->vratiTip()!=RUCNI && cvor->vratiTip() != TAKT/* && cvor->vratiTip()!=NOVITIP*/)
		{
			//Na stack se stavlja ne obradjen cvor i uzima njegov prvi ne obradjeni sin
			stek_cvorova_.push(cvor);
			cvor = cvor->vratiNeispitanUlaz();
		}

		else
		{
			//Ako sam dosao do generatora onda stavljam njegovu vrednost na stack vrednosti 
			
			stek_vrednosti_.push(cvor->vratiVrednost());

			//Sada se vracam na poslednji uneti cvor na stacku i ulazim u prvog neobrajenog sina

			Element* poslednjiUneti = stek_cvorova_.top()->vratiNeispitanUlaz();
			
			//Ako taj sin nije obradjen i ako postoji i nije generator onda se on dodaje na stack cvorova

			if (poslednjiUneti!= nullptr && poslednjiUneti->vratiTip() != RUCNI && poslednjiUneti->vratiTip() != RUCNI && !poslednjiUneti->vecObidjen() ) 
			{
				cvor = poslednjiUneti;
			}

			//Ako je 
			else if(poslednjiUneti->vratiTip() != RUCNI && poslednjiUneti->vratiTip() != TAKT)
			{
				stek_vrednosti_.push(poslednjiPoseceni->vratiVrednost());
			}
			else if (poslednjiUneti->vecObidjen()) 
			{
				izracunajMedjurezultat(poslednjiUneti);
				stek_vrednosti_.pop();
			}
			else 
			{
				throw;
			}
		}
	}

	//Sada je potrebno da se vrednost dobijena u sondi upise u vector rezultata kao i vreme promene ako je do nje uopste doslo

	upisiPirkupljeniRezultat(vreme_promene);
  
}

void Ispis::kreirajNoviFajl(const string& filepath,int id)
{
	//Kreiranje modifikovanog imena za izlazni fajl
	string novo_ime = filepath;
	
	int pozicija = filepath.length() - 4;
	string idSonde = to_string(id);
	novo_ime.insert(pozicija,+"_"+ id);

	fstream izlazni_fajl(novo_ime,ios::out);
	
	int i = 0;
	bool nasao = false;
	while (i<promena_.size() && promena_[i]!=1)
	{
		i++;
	}

	for (i; i < vreme_promene_.size(); i++) 
	{
		if (promena_[i]== 1) 
		{
			izlazni_fajl << "0 -> 1: " << vreme_promene_[i] << " [us] " << endl;
		}
		else 
		{
			izlazni_fajl << "1 -> 0: " << vreme_promene_[i] << " [us] " << endl;
		}
	}
	
	izlazni_fajl.close();
}

void Ispis::upisiPirkupljeniRezultat(float  vreme )
{
	int stanje = stek_vrednosti_.top();
	stek_vrednosti_.pop();
	
	if (!promena_.empty() ) 
	{
		if (promena_[promena_.size() - 1] != stanje) 
		{
			promena_.push_back(stanje);
		}
	}

	//
	else 
	{
		promena_.push_back(stanje);
		vreme_promene_.push_back(vreme);
	}
}



