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
			promena_.pop_back();
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

	while (!stek_cvorova_.empty() || (cvor!=nullptr)/* && cvor->vratiTip()!=NOVITIP*/)
	{
		//Pitati ADRIANA STA DA SE RADI U SLUCAJU DA CITAVO KOLO NIJE POVEZANO
		
		//U slucaju da je cvor nije generator desice se prolazak kroz sinove ne obradjene
		if (cvor!=nullptr &&( cvor->vratiTip()!=RUCNI && cvor->vratiTip() != TAKT)/* && cvor->vratiTip()!=NOVITIP*/)
		{
			//Na stack se stavlja ne obradjen cvor i uzima njegov prvi ne obradjeni sin
			stek_cvorova_.push(cvor);
			cvor = cvor->vratiNeispitanUlaz();
		}

		//Ovde se ulzai ako je elemen generator koji to problem izaziva
		else
		{
			//Ako sam dosao do generatora onda stavljam njegovu vrednost na stack vrednosti
			if (cvor != nullptr)
			{
				stek_vrednosti_.push(cvor->vratiVrednost());
			}
			//Sada se vracam na poslednji uneti cvor na stacku i ulazim u prvog neobradjenog sina

			Element* poslednjiUneti = stek_cvorova_.top();
			
			//Ako taj sin nije obradjen i ako postoji i nije generator onda se on dodaje na stack cvorova

			if (!poslednjiUneti->vecObidjen() )
			{
				cvor = poslednjiUneti->vratiNeispitanUlaz();
			}

			//Ako su svi sinovi obidjeni
			
			else if (poslednjiUneti->vecObidjen()) 
			{
				izracunajMedjurezultat(poslednjiUneti);
				stek_cvorova_.pop();
				cvor = nullptr;
				
			}
		}

		//Mislim da mora da se ocisti sva polja koja ucestvuju u prolasku kroz stablo jer inace necu moci da prolazim kad se napune
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

	//Ovde se sada ubacuje novi deo imena izlaznog stringa
	novo_ime.insert(pozicija,+"_"+ idSonde);


	fstream izlazni_fajl(novo_ime,ios::out);
	
	int i = 0;
	bool nasao = false;
	
	//Sada zelim da nadjem indeks prvog elementa kada se desila promena na jedinicu i da onda od tog indeksa unosim 
	while (!nasao && i < promena_.size()) 
	{
		if (promena_[i] == 1) 
		{
			nasao = true;
		}
		else
		{
			i++;
		}
	}

	for (i; i < vreme_promene_.size(); i++) 
	{
		if (promena_[i]== 1) 
		{
			izlazni_fajl << "0 -> 1: " << vreme_promene_[i] <<"us"<<endl;
		}
		else 
		{
			izlazni_fajl << "1 -> 0: " << vreme_promene_[i] << "us" << endl;
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
			vreme_promene_.push_back(vreme);
		}
	}

	else 
	{
		promena_.push_back(stanje);
		vreme_promene_.push_back(vreme);
	}
}



