#ifndef DLLIST_H
#define DLLIST_H

#include <iterator>
template <class T>
class DList
{
	struct Node
	{
	    Node(){prev = this; next = this;}
		Node(const T& val, Node* p = NULL, Node* n = NULL):value(val),prev(p), next(n){}
		T value;
		Node* prev;
		Node* next;
	};

	Node* header;
public:

	class iterator
	{
		Node* m_rep;
	public:
		friend class DList;

		inline iterator(Node* x=NULL):m_rep(x){}
		inline iterator(const iterator& x):m_rep(x.m_rep) {}
		inline iterator& operator=(const iterator& r)
		{
			m_rep = r.m_rep;
			return *this;
		}
		inline iterator& operator++()
		{
			m_rep = m_rep->next;
			return *this;
		}
		inline iterator operator++(int)
		{
			iterator tmp(*this);
            m_rep = m_rep->next;
            return tmp;
		}
		inline T& operator*(){ return m_rep->value; }
		inline Node* operator->() const { return m_rep; }
		inline bool operator==(const iterator& r) const
		{
			return m_rep == r.m_rep;
		}
		inline bool operator!=(const iterator& r) const
		{
			return m_rep != r.m_rep;
		}

            inline iterator& operator--()
		{
			m_rep = m_rep->prev;
			return *this;
		}
		inline iterator operator--(int)
		{
			iterator tmp(*this);
            m_rep = m_rep->prev;
            return tmp;
		}

	};

    DList(){header = new Node();}
    DList(const T& val){
        header = new Node();
        Node* newNode = new Node(val, header, header);
        header->next = newNode;
        header->prev = newNode;
        }
	~DList() { clear(); }
	void clear() { while (!empty()) pop_front(); }

	inline void push_front(const T&x)
	{
		Node* temp = new Node(x, header, header->next);
		header->next->prev = temp;
		header->next = temp;
	}
	inline void pop_front()
	{
		if (header->next!=header)
		{
			Node* temp = header->next;
			header->next = temp->next;
			temp->next->prev = header;
			delete temp;
		}
	}
	inline bool empty() { return header->next==header; }

	inline T& front() { return *begin(); }
	inline const T& front() const { return *begin(); }

	inline iterator begin() { return iterator(header->next); }
	inline iterator end() { return iterator(header); }

	// insert y before x. Intended to parallel vector operation
	void insert (iterator& x, const T& y) {
		Node *temp = new Node(y, x.m_rep->prev, x.m_rep);		// new node's next will be x's node
		if (x.m_rep==header->next)
        {
            header->next->prev = temp;
            header->next = temp;
        }
		else {
            x.m_rep->prev->next = temp;
            x.m_rep->prev = temp;
		}
	}

	// push back. Intended to parallel vector operation
	void push_back (const T& y) {
		Node *newNode = new Node(y, header->prev, header);
		header->prev->next = newNode;
		header->prev = newNode;
	}

};

#endif // DLLIST_H
