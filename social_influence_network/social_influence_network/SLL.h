#pragma once
#include <cassert>

template <class T> class list;
template <class T> class stack;
template <class T>
class Node
{
private:
	T data;
	Node<T>* next;
	friend class list<T>;
	friend class stack<T>;
public:

	Node()
	{
		data = 0;
		next = nullptr;
	}
	Node(T val, Node<T>* n)
	{
		data = val;
		next = n;
	}
	Node(const Node& n)
	{
		data = n.data;
		next = n.next;
	}
	Node<T>* get_next()
	{
		return this->next;
	}
	T get_data()
	{
		return data;
	}
	~Node()
	{
		next = nullptr;
	}
};

template <class T>
class list
{
private:
	Node<T>* head;
	Node<T>* tail;
	int size;
	class ListIterator
	{
	private:
		Node<T>* iptr;
		friend class list<T>;
	public:
		ListIterator(Node<T>* t)
		{
			iptr = t;
		}
		ListIterator()
		{
			iptr = nullptr;
		}
		ListIterator(ListIterator& l)
		{
			this->iptr = l.iptr;
		}
		T& operator*()
		{
			assert(this->iptr != nullptr);
			return this->iptr->data;
		}
		ListIterator& operator++()
		{
			if (this->iptr != nullptr)
			{
				this->iptr = iptr->next;
			}
			return (*this);
		}
		ListIterator& operator--()
		{
			if (iptr != nullptr)
			{
				iptr = iptr->prev;
			}
			return (*this);
		}
		bool operator ==(ListIterator& I)
		{
			if (iptr != nullptr)
			{
				return (iptr->data == I.iptr->data);
			}
			return false;

		}
		bool operator !=(ListIterator& I)
		{
			return (iptr->data != I.iptr->data);
		}
	};
public:
	typedef ListIterator Iterator;
	list()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	list(Node<T>*h, Node<T>*t, int s)
	{
		head = h;
		tail = t;
		size = s;
	}
	~list()
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
			tail = nullptr;
		}

	}
	void insertAtEnd(T const element)
	{
		if (head != nullptr)
		{
			Node<T>* temp = new Node<T>();
			temp->next = nullptr;
			tail->next = temp;
			tail = temp;
			temp->data = element;

		}
		if (head == nullptr) //list is empty
		{
			Node<T>* temp = new Node<T>();
			temp->next = nullptr;
			temp->data = element;
			head = temp;
			tail = temp;
		}
		size++;
	}
	void print() const
	{
		Node<T>* temp = head;
		if (temp != nullptr)
		{
			for (; temp != nullptr; temp = temp->next)
			{
				cout << temp->data << " ";
			}
			cout << endl;
		}
		else
		{
			cout << " List is empty " << endl;
		}
	}
	bool check_repetition(T const& element)
	{
		bool repetition = false;
		Node<T>* temp = head;
		for (int i = 0; i < size && !repetition; i++)
		{
			if (temp->data == element)
			{
				//element already in linked list
				repetition = true;
			}
			else
			{
				temp = temp->next;
			}
		}
		return repetition;
	}
	int get_size();
	int get_data(Node<T>* n);
	ListIterator begin();
};

template <typename T>
typename list<T>::ListIterator list<T>::begin()
{
	list<T>::ListIterator it(this->head);
	return it;
}

template<class T>
inline int list<T>::get_size()
{
	return size;
}

template<class T>
inline int list<T>::get_data(Node<T>* n)
{
	return n->data;
}
