#pragma once

#include"Izuzeci.h"
#include<fstream>
#include<iostream>
#include<string>
#include<vector>


enum Tip { SONDA, TAKT, RUCNI, NE, I, ILI };

class Element {

public:

	Element(int id, int tip, int podrazumevano, int neispitan, int broj_prolazaka_);
	//Element(const Element&);
	//Element( Element&&);
	virtual ~Element();

	int brojPinova();
	bool vecObidjen();
	int vratiId();
	void resetujElemente();
	void resetujGenratore();
	void povezi(int pin,Element*);
	int vratiVrednost();
	Tip vratiTip();
	virtual float vratiFrekv();
	virtual void promeniVrednost(float=0);
	Element* vratiNeispitanUlaz();

protected:

	Tip tip_;
	int id_;
	int vrednost_;
	std::vector<Element*> sinovi_;
	float frekvencija_;
	int broj_pinova_;
	int broj_prolazaka_;
};

class TaktGen :public Element {
public:
	TaktGen(std::fstream& inputFile, std::vector<float>& , float, int, int);
	~TaktGen();

	float vratiFrekv();
	virtual void promeniVrednost(float=0) override;

private:
	std::vector<float> vremenski_tren_;
};

class RucniGen :public Element {
public:
	RucniGen(std::fstream& inputFile, std::vector<float>&, float, int, int);
	~RucniGen();

	virtual void promeniVrednost(float=0) override;
private:
	std::vector<float> vremenski_tren_;
};

class IliKolo :public Element {
public:
	IliKolo(std::fstream& inputfile, int,int);
};

class IKolo :public Element {
public:
	IKolo(std::fstream& inputFile, int,int);
};

class NeKolo :public Element {
public:
	NeKolo(std::fstream& inputFile, int, int);
};

class Sonda :public Element {
public:
	Sonda(int id, int tip);
};