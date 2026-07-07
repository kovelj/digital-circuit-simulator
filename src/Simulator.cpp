#include "Simulator.h"


Simulator::Simulator():vreme_trajanja_(0),broj_elem_(0) {}

Simulator::~Simulator()
{
	int velicina = dig_kolo_.size();
		if (!velicina) 
		{
			for(int i=0;i<velicina;i++)
			{
				dig_kolo_.pop_back();
			}
		}

		velicina = vreme_.size();
		if (!velicina)
		{
			for (int i = 0; i < velicina; i++)
			{
				vreme_.pop_back();
			}
		}

}

void Simulator::loadCircuit(const string& filepath)
{
	fstream inputFile(filepath, ios::in);

	//Ovaj posao se delegira novoj klasi jer simulator ne treba da iscitava fajl ili povezuje elemente, jer njega zanima samo ulaz izlaz i kako protice vreme
	
	Citanje* citaj = new Citanje(inputFile, dig_kolo_, vreme_trajanja_, broj_elem_, vreme_,izlazi_);
	
	inputFile.close();

	delete citaj;

	nadjiUlaze();
	srediVreme();

}

void Simulator::simulate(const string& filepath)
{	
	//Ovde se stvara novi objekat klase koja ce vrsiti upisivanje u fajl jer je to opet posao koji ne treba da obavlja simulator
	Ispis* ispis=new Ispis();
	

	//Ova petlja za svaki izlaz koji postoji pravi izlazni fajl u koji upisuje kad i kakva se promena desila vise o tome sta je potrebno ispisati naci u specifikaciji zadataka
	for (Element* izlaz : izlazi_) 
	{   
	
		resetujGeneratore();
		//U svakoj iteraciji kroz vremenske trenutke se menja ako je potrebno vrednost generatora pocev od 0[us] 

		for (int i = 0; i < vreme_.size(); i++)
		{
			otkucajVreme(vreme_[i]);
			ispis->vrednostNaIzlazu(izlaz,vreme_[i]);
			resetujKolo();
		}

		//Upis prikupljenih rezultata u fajl
		ispis->kreirajNoviFajl(filepath,izlaz->vratiId(),vreme_trajanja_);

		//Mora se isprazniti vector ako nije prazan
		ispis->isprazniVektore();

		
	}
	

}

void Simulator::otkucajVreme(float trenutak)
{
	//Ova  metoda u kriticnim trenucima prolazi kroz sve generatore i ako je potrebno menja vrednost izlaznog signala

	for (int i=0;i<dig_kolo_.size();i++) 
	{   
		//Ispituje se da li je element generator, a onda mu i promeni vrednost, TREBA DODATI USLOV AKO SE DODA NOVI GENERATOR
		
		if (dig_kolo_[i]->vratiTip() == TAKT || dig_kolo_[i]->vratiTip() == RUCNI /*||dig_kolo_[i]->vratiTip == NOVITIP */) 
		{   
		    //Za dalju implementaciju metode promeni vrednost uci u Element.h
			dig_kolo_[i]->promeniVrednost(trenutak);
		}
	}
}

void Simulator::srediVreme()
{
	//Ova petlja se koristi da bi se vreme sortiralo,inace je klasican sort slozenosti O(n^2)

	for (int i = 0; i < vreme_.size() - 1; i++) 
	{
		for (int j = i + 1; j < vreme_.size(); j++)
		{
			if (vreme_[i] > vreme_[j])
			{
				float t = vreme_[i];
				vreme_[i] = vreme_[j];
				vreme_[j] = t;
			}

		}

    }
}

//Mozda je ime malo traljavo ali sluzi tome da se logicka kola resetuju nakon svakog novog prolaska, to jest za svaki novi trenutak!
void Simulator::resetujKolo()
{
	for (Element* element : dig_kolo_) 
	{
		element->resetujElemente();
	}
}

//Sluzi tome da se genratori resetuju na nulu pri vrsenju merenja za svaku novu sondu 
void Simulator::resetujGeneratore()
{
	for (Element* element : dig_kolo_)
	{
		element->resetujGenratore();
	}
}

void Simulator::nadjiUlaze() 
{
	//Ova petlja prolazi kroz sve elemente u digitalnom kolu i nalazi izlaze(SONDE), a zatim ih stavlja u vector  
	
	for (Element* element:dig_kolo_) 
	{
		if (element->vratiTip() == SONDA) 
		{
			izlazi_.push_back(element);
		}
	}
	if (izlazi_.empty()) 
	{
		throw NepravilnaVeza("Ova sema ne sadrzi sonde koje bi prikupljle izlazne signale!!!");
	}
}