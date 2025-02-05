#pragma once
#include "Node.h"
#include "Iterator.h"
#include <initializer_list>

template<typename T>
class List
{
private:
	Node<T>* m_head;
	Node<T>* m_tail;
	int m_length;
public:
	List<T>();
	List<T>(std::initializer_list<T> values);
	~List<T>();

	void PushFront(const T& value);
	void PushBack(const T& value);
	T PopFront();
	T PopBack();
	bool Insert(const T& value, int index);
	bool Remove(const T& value);
	void Swap(T& leftSwap, T& rightSwap);
	T First() const;
	T Last() const;
	Iterator<T> begin() const;
	Iterator<T> end() const;
	void Destroy();
	int GetLength() const;
};

template<typename T>
inline List<T>::List() : m_head(nullptr), m_tail(nullptr), m_length(0)
{
}

template<typename T>
inline List<T>::List(std::initializer_list<T> values) : m_length(0), m_head(nullptr), m_tail(nullptr)
{
	if (values.size() <= 0)
		return;

	for (T item : values)
	{
		PushBack(item);
	}
}

template<typename T>
inline List<T>::~List()
{
	Destroy();
	delete m_head;
	m_head = nullptr;
	delete m_tail;
	m_tail = nullptr;
}

template<typename T>
inline void List<T>::PushFront(const T& value)
{
	Node<T>* newNode = new Node<T>(value);
	m_length++;
	if (!m_tail)
	{
		m_head = newNode;
		m_tail = newNode;
		return;
	}
	m_head->previous = newNode;
	newNode->next = m_head;
	m_head = newNode;
}

template<typename T>
inline void List<T>::PushBack(const T& value)
{
	Node<T>* newNode = new Node<T>(value);
	m_length++;
	if (!m_tail)
	{
		m_head = newNode;
		m_tail = newNode;
		return;
	}
	m_tail->next = newNode;
	newNode->previous = m_tail;
	m_tail = newNode;
}

template<typename T>
inline T List<T>::PopFront()
{
	if (!m_tail)
		return T();

	T value = m_head->value;

	if (!m_head->next)
	{
		delete m_head;
		m_head = nullptr;
		m_tail = nullptr;
		m_length = 0;
	}
	else
	{
		m_head = m_head->next;
		delete m_head->previous;
		m_head->previous = nullptr;
		m_length--;
	}
	return value;
}

template<typename T>
inline T List<T>::PopBack()
{
	if (!m_tail)
		return T();

	T value = m_tail->value;

	if (!m_tail->previous)
	{
		delete m_tail;
		m_head = nullptr;
		m_tail = nullptr;
		m_length = 0;
	}
	else
	{
		m_tail = m_tail->previous;
		delete m_tail->next;
		m_tail->next = nullptr;
		m_length--;
	}
	return value;
}

template<typename T>
inline bool List<T>::Insert(const T& value, int index)
{
	// if the index SUCKS and is BAD say SCREW YOU and return FALSE
	if (index < 0 || index > m_length)
		return false;

	// if you're just inserting something at the front just PushFront and return true
	if (!m_tail || index == 0)
	{
		PushFront(value);
		return true;
	}

	// if you're putting it at the back, PushBack
	if (index == m_length)
	{
		PushBack(value);
		return true;
	}

	Node<T>* node = m_head;

	// move node over to the given index
	for (int i = 0; i < index; i++)
	{
		if (node->next == nullptr)
			return false;

		node = node->next;
	}

	Node<T>* newNode = new Node<T>(value);

	// set the newNode's previous to node's previous, newNode's next to node, node's previous to newNode, and newNode's previous's next to newNode
	newNode->previous = node->previous;
	newNode->next = node;
	node->previous = newNode;
	newNode->previous->next = newNode;
	m_length++;
	return true;
}

template<typename T>
inline bool List<T>::Remove(const T& value)
{
	if (!m_tail)
		return false;

	if (m_head->value == value)
	{
		PopFront();
		return true;
	}

	if (!m_head->next)
		return false;

	if (m_tail->value == value)
	{
		PopBack();
		return true;
	}

	if (m_length <= 2)
		return false;

	Node<T>* node = m_head->next;

	while (node != m_tail->previous)
	{
		if (node->value == value)
		{
			node->previous->next = node->next;
			node->next->previous = node->previous;
			m_length--;
			delete node;
			node = nullptr;
			return true;
		}
		node = node->next;
	}
	return false;
}

template<typename T>
inline void List<T>::Swap(T& leftSwap, T& rightSwap)
{
	Node<T>* nodeLeft = m_head;
	Node<T>* nodeRight = m_head;

	bool leftNodeFound = false;
	bool rightNodeFound = false;

	for (int i = 0; i < m_length; i++)
	{
		if (leftSwap == nodeLeft->value)
			leftNodeFound = true;

		if (rightSwap == nodeRight->value)
			rightNodeFound = true;

		if (!leftNodeFound)
			nodeLeft = nodeLeft->next;

		if (!rightNodeFound)
			nodeRight = nodeLeft->next;

		if (leftNodeFound && rightNodeFound)
			break;
	}

	if (!leftNodeFound || !rightNodeFound)
		return;

	// swap the values
	Node<T>* temp = new Node<T>;

	temp->next = nodeLeft->next;
	temp->previous = nodeLeft->previous;
	temp->value = nodeLeft->value;

	nodeLeft->next = nodeRight->next;
	nodeLeft->previous = nodeRight->previous;
	nodeLeft->value = nodeRight->value;

	nodeRight->next = temp->next;
	nodeRight->previous = temp->previous;
	nodeRight->value = temp->value;
}

template<typename T>
inline T List<T>::First() const
{
	if (!m_head)
		return T();

	return m_head->value;
}

template<typename T>
inline T List<T>::Last() const
{
	if (!m_tail)
		return T();

	return m_tail->value;
}

template<typename T>
inline Iterator<T> List<T>::begin() const
{
	if (!m_head)
		return Iterator<T>();

	return Iterator<T>(m_head);
}

template<typename T>
inline Iterator<T> List<T>::end() const
{
	if (!m_tail)
		return Iterator<T>();

	return Iterator<T>(m_tail);
}

template<typename T>
inline void List<T>::Destroy()
{
	if (!m_tail)
		return;

	for (int i = 0; i < m_length; i++)
	{
		PopBack();
	}

	m_head = nullptr;
	m_tail = nullptr;
	m_length = 0;
}

template<typename T>
inline int List<T>::GetLength() const
{
	return m_length;
}
