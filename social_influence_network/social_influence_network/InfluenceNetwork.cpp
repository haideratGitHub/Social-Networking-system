#include "InfluenceNetwork.h"
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

void check_input(int& option,int lower_bound, int upper_bound)
{
	while (cin.fail()) //Handle character input
	{
		cin.clear(); //clear the cin stream
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << "You have entered character! Enter a number " << endl;
		cin >> option;
	}
	while (option < lower_bound || option > upper_bound) //Handle out of bound input
	{
		cout << "You have entered out of bound number! Enter again " << endl;
		cin >> option;
		while (cin.fail()) //Handle character input
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n'); // ignore last input
			cout << "You have entered character! Enter a number " << endl;
			cin >> option;
		}
	}
}

int InfluenceNetwork::influence(int id , int number_of_direct_influences , int option)
{
	int size_of_network = 0;
	this->input(size_of_network);
	bool* influence_record = new bool[size_of_network];
	for (int i = 0; i < size_of_network; i++)
	{
		influence_record[i] = 0; //initialization
	}
	if (arr[id - 1].get_size() != 0)
	{
		stack<int> s; //stack to calculate influence 
		list<int>::Iterator it = arr[id - 1].begin(); //to traverse in linked list at particular index of arr
		for (int i = 0; i < number_of_direct_influences; i++)
		{
			int temp = *it;
			influence_record[temp - 1] = 1;
			s.push(temp); //to find indirect influences
			it.operator++();

		}
		bool flag = true; //stack is not empty
		while (flag)
		{
			int id = 0;
			s.top(id); //gives id's of direct influences
			s.pop();
			if (arr[id - 1].get_size() != 0)
			{
				list<int>::Iterator it1 = arr[id - 1].begin();
				for (int j = 0; j < arr[id - 1].get_size(); j++)
				{
					int temp1 = *it1;
					if (influence_record[temp1 - 1] != 1) // if 1 then means already exist
					{
						influence_record[temp1 - 1] = 1;
						s.push(temp1);
					}
					it1.operator++();
				}
			}
			else
			{
				//no further influence i.e new member in network
				if (influence_record[id - 1] != 1) // if 1 then means already exist
				{
					influence_record[id - 1] = 1;
					s.push(id);
				}
			}
			if (s.get_size() == 0)
			{
				flag = false;
			}
		}
	}
	if (option == 1)
	{
		cout << "The direct influences " << endl;
		cout << id << " ->  ";
		arr[id - 1].print();
		cout << "The indirect + direct influneces" << endl;
		int number_of_influences = 0;
		cout << id << " ->  ";
		for (int i = 0; i < size_of_network; i++)
		{
			if (influence_record[i] == 1)
			{
				number_of_influences++;
				cout << i + 1 << " ";
			}
		}
		return number_of_influences;
	}
	if (option == 2)
	{
		int number_of_influences = 0;
		cout << id << " ->  ";
		for (int i = 0; i < size_of_network; i++)
		{
			if (influence_record[i] == 1)
			{
				number_of_influences++;
				cout << i + 1 << " ";
			}
		}
		cout << endl;
		return number_of_influences;
	}
	if (option == 3)
	{
		int number_of_influences = 0;
		for (int i = 0; i < size_of_network; i++)
		{
			if (influence_record[i] == 1)
			{
				number_of_influences++;
			}
		}
		return number_of_influences;
	}

	
	
}

InfluenceNetwork::InfluenceNetwork()
{
	arr = nullptr;
}

InfluenceNetwork::InfluenceNetwork(list<int>* a)
{
	arr = a;
}

InfluenceNetwork::~InfluenceNetwork()
{
	delete[] arr;
}

void InfluenceNetwork::input(int& SIZE_OF_NETWORK)
{
	ifstream fin("network.txt");
	if (fin.is_open())
	{
		int size_of_network = 0;
		fin >> size_of_network;
		SIZE_OF_NETWORK = size_of_network;
		arr = new list<int>[size_of_network];
		char temp[50];
		while (!fin.eof())
		{
			fin >> temp;
			int id_of_person = atoi(&temp[0]);
			for (int i = 2; i<strlen(temp); i++)
			{
				arr[id_of_person - 1].insertAtEnd(atoi(&temp[i]));
				i++;
			}
		}
	}
	else
	{
		cout << "File failed to open " << endl;
	}
}

void InfluenceNetwork::Calculate_Influence()
{
	int size_of_network = 0;
	this->input(size_of_network);
	bool exit = false;
	while (!exit)
	{
		system("CLS");
		cout << "1. Influence of particular person " << endl;
		cout << "2. Influences in whole network " << endl;
		cout << "3. Person with maximum influences " << endl;
		cout << "4. Exit " << endl;
		cout << endl;
		cout << "Select: ";
		int option = 0;
		cin >> option;
		check_input(option,1,4);
		if (option == 1)
		{
			cout << "Enter the ID of person to find his/her influence (1 - " << size_of_network << " )" << endl;
			int id = 0;
			cin >> id;
			check_input(id, 1, size_of_network);
			int number_of_direct_influences = arr[id - 1].get_size();
			bool no_influence = false;
			if (arr[id - 1].get_size() == 0)
			{
				cout << "Person with ID " << id << " does not influence anyone " << endl;
				no_influence = true;
				system("pause");
			}
			if (!no_influence)
			{
				int number_of_influences = influence(id,number_of_direct_influences,1);
				cout << endl;
				cout << "The total number of influences of ID " << id << " : " << number_of_influences << endl;
				cout << endl;
				system("pause");
			}
		
		}
		if (option == 2)
		{
			for (int i = 0; i < size_of_network; i++)
			{
				int number_of_direct_influences = arr[i].get_size();
				int number_of_influences = influence(i+1, number_of_direct_influences,2);
			}
			cout << endl;
			system("pause");
		}
		if (option == 3)
		{
			int* number_of_influences = new int[size_of_network];
			for (int i = 0; i < size_of_network; i++)
			{
				int number_of_direct_influences = arr[i].get_size();
				number_of_influences[i] = influence(i + 1, number_of_direct_influences, 3);
			}
			int j = 0;
			int index = 0;
			int max = number_of_influences[j];
			j++;
			for (; j < size_of_network; j++)
			{
				if (max < number_of_influences[j])
				{
					max = number_of_influences[j];
					index = j;
				}
			}
			cout << "The most popular influencer ID : " << index + 1 << endl;
			cout << "Total influences : " << max << endl;
			cout << endl;
			system("pause");
		}
		if (option == 4)
		{
			exit = true;
		}

	}
}

list<int>* InfluenceNetwork::get_arr()
{
	return arr;
}

ostream & operator<<(ostream & out, InfluenceNetwork & n)
{
	list<int>* temp = n.get_arr();
	for (int i = 0; i < 9; i++)
	{
		temp[i].print();
	}
	return out;
	// TODO: insert return statement here
}
