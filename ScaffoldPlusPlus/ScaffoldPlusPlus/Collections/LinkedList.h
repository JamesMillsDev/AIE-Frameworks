#pragma once

#include <initializer_list>
#include <iostream>

using std::initializer_list;

template<class T>
class LinkedList
{
public:
    struct Node
    {
        T value;
        Node* next = nullptr;
        Node* prev = nullptr;

        Node(const T& _value): value(_value) {}
    };

    struct Iterator
    {
        Node* node = nullptr;

        Iterator() : node(nullptr) {}
        Iterator(Node* _node) : node(_node) {}

        //Increment Operators
        Iterator& operator++() { return Next(); }
        Iterator& operator++(int) { return Next(); }

        //Decrement Operators
        Iterator& operator--() { return Prev(); }
        Iterator& operator--(int) { return Prev(); }

        //Equality Check Operator
        bool operator==(const Iterator& _rhs) { return node == _rhs.node; }
        bool operator!=(const Iterator& _rhs) { return node != _rhs.node; }

        //Iterator Getter
        Iterator& operator+(const int _shiftAmount)
        {
            Iterator iter = *this;
            for(size_t i = 0; i < _shiftAmount; i++)
            {
                iter = iter.Next();
                //Check if ended
            }

            return iter;

        } 

        Iterator& operator-(const int _shiftAmount)
        {
            Iterator iter = *this;
            for(size_t i = _shiftAmount; i > 0; i--)
            {
                iter = iter.Prev();
            }

            return iter;

        }

        //Dereference Operator
        T& operator*() { return node->value; }
        T* operator->() { return &node->value; }

        Iterator& Next()
        {
            if (node != nullptr) node = node->next;

            return *this;
        }

        Iterator& Prev()
        {
            if (node != nullptr) node = node->prev;

            return *this;
        }
    };

    LinkedList()
    {
    }

    LinkedList(initializer_list<T> _list)
    {
        for (auto iter = _list.begin(); iter != _list.end(); iter++) PushBack(*iter);
    }

    ~LinkedList()
    {
    }
    
    void PushBack(const T& _value)
    {
        Node* newNode = new Node(_value);
        m_count++;

        if (IsEmpty())
        {
            m_first = newNode;
            m_last = newNode;
        }
        else
        {
            m_last->next = newNode;
            newNode->prev = m_last;
            m_last = newNode;
        }
    }
    
    void PopBack()
    {
        if (IsEmpty()) return;

        Node* last = m_last;
        m_last = m_last->prev;
        if(m_last != nullptr) m_last->next = nullptr;
        if (m_last == nullptr) m_first = nullptr;

        delete last;
        m_count--;
    }
    
    void PushFront(const T& _value)
    {

        Node* newNode = new Node(_value);
        m_count++;

        if (IsEmpty())
        {
            m_first = newNode;
            m_last = newNode;
        }
        else
        {
            m_first->prev = newNode;
            newNode->next = m_first;
            m_first = newNode;
        }

    }
    
    void PopFront()
    {
        if (IsEmpty()) return;

        Node* first = m_first;
        m_first = m_first->next;
        m_first->prev = nullptr;

        if (m_first == nullptr) m_last = nullptr;

        delete first;
        m_count--;
    }
    
    void Clear()
    {
        if (IsEmpty()) return;

        while (m_count > 0)
        {
            PopBack();
        }
        
    }

    Iterator Remove(Iterator _iter)
    {
        Node* nodeToRemove = _iter.node;
        if (nodeToRemove == nullptr) return _iter;

        if (nodeToRemove == m_first)
        {
            PopFront();
            return Iterator(m_first);
        }
        else if (nodeToRemove == m_last)
        {
            PopBack();
            return Iterator(m_last);
        }
        else
        {
            nodeToRemove->prev->next = nodeToRemove->next;
            nodeToRemove->next->prev = nodeToRemove->prev;
            m_count--;
            return Iterator(nodeToRemove->next);
        }
    }

	void Add(Iterator _iter, const T& _value)
	{
		Node* newNode = new Node(_value);
		m_count++;

		if (IsEmpty())
		{
			m_first = newNode;
			m_last = newNode;
		}
		else
		{
			Node* nodeToInsertAfter = _iter.node;
			if (nodeToInsertAfter == nullptr)
			{
				PushBack(_value);
				return;
			}
			else if (nodeToInsertAfter == m_last)
			{
				PushBack(_value);
				return;
			}
			else
			{
				newNode->prev = nodeToInsertAfter;
				newNode->next = nodeToInsertAfter->next;
				nodeToInsertAfter->next->prev = newNode;
				nodeToInsertAfter->next = newNode;
			}
		}
	}

	Iterator RemoveAt(const size_t _index)
	{
		if (_index >= m_count) return Iterator(nullptr);

		Iterator iter = begin();
		for (size_t i = 0; i < _index; i++)
		{
			iter = iter.Next();
		}

		return Remove(iter);
	}

	
	T& At(const size_t _index)
	{
		if (_index >= m_count) return m_first->value;

		Iterator iter = begin();
		for (size_t i = 0; i < _index; i++)
		{
			iter = iter.Next();
		}

		return iter.node->value;
	}

    Iterator Insert(Iterator _iter, const T& _value)
    {
        Node* currentNode = _iter.node;

        Node* newNode = new Node(_value);

        //TODO: create a new Node
        
        //Adjust the next and previous as appropriate so that the new Node is inserted "Before" the currentNode
        if (currentNode == m_first)
        {
            m_first = newNode;
            newNode->next = currentNode;
            currentNode->prev = newNode;
        }
        else
        {
            currentNode->prev->next = newNode;
            newNode->prev = currentNode->prev;
            newNode->next = currentNode;
            currentNode->prev = newNode;
        }

        //Return an iterator to the newly created node
        m_count++;
        return Iterator(newNode);
    }

    bool Contains(const T& _value)
    {
        Node* currentNode = m_first;

        Node* newNode = new Node(_value);
        
        while (currentNode != NULL)
        {
            if (currentNode->value == newNode->value)
            {
                return true;
            }
            currentNode = currentNode->next;
        }

        return false;
    }

    
	int IndexOf(const T& _value)
	{
		Node* currentNode = m_first;
		int index = 0;

		while (currentNode != NULL)
		{
			if (currentNode->value == _value)
			{
				return index;
			}
			currentNode = currentNode->next;
			index++;
		}

		return -1;
	}
	
	void Sort()
	{
		if (IsEmpty()) return;

		Node* currentNode = m_first;
		Node* nextNode = m_first->next;

		while (currentNode != NULL)
		{
			while (nextNode != NULL)
			{
				if (currentNode->value > nextNode->value)
				{
				    //use swap helper
                    Swap(currentNode, nextNode);
				}
				nextNode = nextNode->next;
			}
			if (currentNode->next == nullptr) break;
			currentNode = currentNode->next;
			nextNode = currentNode->next;
		}
	}
	
    //Swap Helper
	void Swap(Node* _node1, Node* _node2)
	{
		T temp = _node1->value;
		_node1->value = _node2->value;
		_node2->value = temp;
	}

    bool IsEmpty()
    {
        return m_first == nullptr && m_last == nullptr;
    }

    unsigned int Count()
    {
        return m_count;
    }

    Node* FirstNode() { return m_first; }
    Node* LastNode() { return m_last; }

    Iterator begin() { return Iterator(m_first); }
    Iterator last() { return Iterator(m_last); }
    Iterator end() { return Iterator(nullptr); }

protected:
private:
    unsigned int m_count = 0;
    Node* m_first = nullptr;
    Node* m_last = nullptr;
};