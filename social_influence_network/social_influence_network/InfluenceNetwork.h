#pragma once
#include "Stack.h"
#include <iostream>
#include "SLL.h"
using namespace std;

class InfluenceNetwork
{
private:
	list<int>* arr;
	int influence(int id , int number_of_direct_influences , int option); //return number of influences - direct + indirect
public:
	InfluenceNetwork();
	InfluenceNetwork(list<int>* a);
	~InfluenceNetwork();
	void input(int&); // A function to input the network from a file into the array of SLLs
	void Calculate_Influence();
	friend ostream& operator<<(ostream& out, InfluenceNetwork& i);
	list<int>* get_arr();
};