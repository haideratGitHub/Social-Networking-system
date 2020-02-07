#pragma once
#include "SLL.h"

template <class T>
class stack
{
private:
	Node<T>* head;
	int size;
public:
	stack()
	{
		head = nullptr;
		size = 0;
	}
	stack(Node<T>*h, int s)
	{
		head = h;
		size = s;
	}
	~stack()
	{
		Node<T>* temp = head;
		if (head != nullptr)
		{
			for (; temp != nullptr; head = temp)
			{
				temp = temp->next;
				if (head != nullptr)
				{
					delete head;
				}


			}
		}
	}
	int get_size()
	{
		if (head != nullptr)
		{
			return size;
		}
		else
		{
			return 0;
		}
	}
	bool isEmpty()
	{
		if (head == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool top(T& element)
	{
		if (head == nullptr)
		{
			//stack is empty
			return false;
		}
		else
		{
			element = head->get_data();
			return true;
		}
	}
	void push(T const& element) //insert at start
	{
		if (head != nullptr)
		{
			Node<T>* temp = new Node<T>();
			temp->next = head;
			head = temp;
			temp->data = element;
		}
		if (head == nullptr) //stack is empty
		{
			Node<T>* temp = new Node<T>();
			temp->next = nullptr;
			temp->data = element;
			head = temp;
		}
		size++;
	}
	void pop() //delete from start
	{
		if (head == nullptr)
		{
			cout << "Stack is empty " << endl;
		}
		else
		{
			if (head != nullptr)
			{
				Node<T>* temp = head;
				head = temp->next;
				delete temp;
				temp = nullptr;
			}
			if (size == 1)
			{
				delete head;
				head = nullptr;
			}
			size--;
		}

	}
	//bool isFull() - when size of stack is fixed
};
