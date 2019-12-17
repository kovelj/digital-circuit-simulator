#ifndef CITANJE_H_
#define CITANJE_H_
#include"Element.h"
#include<fstream>
#include<iostream>
#include<string>
using namespace std;
using namespace std;
class Citanje {
public:
	Citanje(fstream&, vector<Element*>& dig_kolo_,float&,int&,vector<float>&);

	void poveziKolo(fstream&,vector<Element*>&,int);
	
};
#endif// ! CITANJE_H_