#pragma once
#include<iostream>
#include<cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////

template<typename Ty> // ���� �켱������ �� ���´�.
class WarpList;

template<typename Ty> // �����ݷ� ����� ������ ����
class WarpNode {
private:
	friend class WarpList<Ty>;

	WarpNode* m_pNext{ nullptr };
	WarpNode* m_pPrev{ nullptr }; // �ʱⰪ�� nullptr �� �߰�ȣ �ʱ�ȭ
public:
	Ty m_Elem; // Ty�� Ŭ����

			   //������
	WarpNode() = default;
	WarpNode(Ty& elem) : m_Elem(elem) {};
	WarpNode(Ty&& elem) : m_Elem(move(elem)) {};

	WarpNode* prev() { return m_pPrev; }
	WarpNode* next() { return m_pNext; }
};

/////////////////////////////////////////////////////////

//�ݺ��ڸ� ���巯����;
template<typename Ty>
class WarpIterator {
public:

	friend class WarpList<Ty>;
	using Node = WarpNode<Ty>;

private:

	explicit WarpIterator(Node* p) : m_pNode(p) {	}
	Node* m_pNode = nullptr;

public:

	Ty& operator*() { return m_pNode->m_Elem; }
	Ty* operator->() { return &(m_pNode->m_Elem); }
	WarpIterator operator=(WarpIterator& other) { m_pNode = other.m_pNode; return *this; }

	bool operator==(WarpIterator& other) const { return (m_pNode == other.m_pNode); }
	bool operator!=(WarpIterator& other) const { return (m_pNode != other.m_pNode); }

	WarpIterator& operator++() { m_pNode = m_pNode->next(); return *this; }
	WarpIterator operator++(int)
	{
		auto p = *this;
		//m_pNode = m_pNode->next();
		++(*this);
		return p;
	}

	WarpIterator& operator--() { m_pNode = m_pNode->prev(); return *this; }
	WarpIterator operator--(int)
	{
		auto p = *this;
		//m_pNode = m_pNode->next();
		--(*this);
		return p;
	}

};

template<typename Ty> // !! �ٷ� ���⿡
class WarpList {
public:
	using type = Ty; // WarpList �ȿ� Ty��� �ڷ����� �ִ�.
	using Node = WarpNode<Ty>; // using �� ����.
	using iterator = WarpIterator<Ty>;
private:
	Node m_wnHead;
	Node m_wnTail; // �̰� �����Ͱ� �ƴϴ�. �׻� ��� ������ �����ִ�.

public:


	//WarpNode m_wnhead -> �׳� �̷��� �ϸ� ��������
	//WarpNode<Ty> m_wnhead; -> �ص� ������ ���ϱ� !!�κп� (���� 11����) ���ø� �ѹ� �� ����
	//������
	WarpList()
	{
		m_wnHead.m_pNext = &m_wnTail;
		m_wnTail.m_pPrev = &m_wnHead; // ���� ������ ��Ų��. 
	}


	void push_front(Ty elem) // �ڷ� �о�ֱ�
	{
		Node *newNode = new Node(elem);
		Node *& oldFirst = m_wnHead.m_pNext; // ����� ������

		oldFirst->m_pPrev = newNode;
		newNode->m_pNext = oldFirst;

		newNode->m_pPrev = &m_wnHead;
		m_wnHead.m_pNext = newNode;
	}

	void push_back(Ty elem) // �ڷ� �о�ֱ�
	{
		Node *newNode = new Node(elem);
		Node *& oldLast = m_wnTail.m_pPrev; //������ ������

		oldLast->m_pNext = newNode;
		newNode->m_pPrev = oldLast;

		newNode->m_pNext = &m_wnTail;
		m_wnTail.m_pPrev = newNode;
	}

	bool insert(Ty elem, iterator Where) /*   // Node* �� �ϳ��ϱ� �ߺ��� �� �� ����*/
	{ // where�� �տ� ����, ���а��ɼ� ������ bool �� ��ȯ
		iterator p = begin();

		while (p.m_pNode != nullptr)
		{
			if (p == Where)
			{
				Node *FindNode = p.m_pNode->m_pPrev;
				Node * WhereNode = FindNode->m_pNext;
				Node *newNode = new Node(elem);

				FindNode->m_pNext = newNode;
				newNode->m_pPrev = FindNode;

				newNode->m_pNext = WhereNode;
				WhereNode->m_pPrev = newNode;


				return true; // ���������� true;
			}
			++p;
		}
		return false;
	}

	bool remove(Ty elem, bool AllRemove = true)
	{//elem ���� �Ȱ��� ��쿡�� �ڸ���
		Node*p = m_wnHead.m_pNext;
		size_t szDeleteCount = 0;
		while (p->m_pNext != nullptr)
		{
			if (p->m_Elem == elem)
			{
				Node* oldNext = p->m_pNext;
				Node* oldPrev = p->m_pPrev;
				// Node*& �ϸ� oldprev �̷��ű��� �� �ٲ�� ������ ������ �ٸſ�
				oldNext->m_pPrev = oldPrev;
				oldPrev->m_pNext = oldNext;

				delete p;

				if (AllRemove == true)
				{
					p = oldNext;
					szDeleteCount++;
					continue;
				}
				else return true;

			}
			p = p->m_pNext;
		}
		return (szDeleteCount > 0); // ��ȣ�� ���� --> bool
	}

	template<typename Fn>
	bool remove_if(Fn& fn)//bool �Լ������Ͱ� �ִٰ� ��������
	{//elem ���� �Ȱ��� ��쿡�� �ڸ���
		Node*p = m_wnHead.m_pNext;
		size_t szDeleteCount = 0;

		while (p->m_pNext != nullptr)
		{
			if (fn(p->m_Elem))
			{
				Node* oldNext = p->m_pNext;
				Node* oldPrev = p->m_pPrev;

				oldNext->m_pPrev = oldPrev;
				oldPrev->m_pNext = oldNext;

				delete p;
				szDeleteCount++;
				p = oldNext;
				continue;
			}
			p = p->m_pNext;
		}
		return (szDeleteCount > 0);
	}

	iterator find(Ty elem)
	{
		for (iterator p = begin(); p != end(); p = ++p)
		{
			if (elem == *p) return p;
		}
		return (end());
	}

	iterator begin()
	{
		return iterator(m_wnHead.m_pNext);
		// ��嵵 �����Ҵ�� �ʵ��̱� ������
		// -> �� �ƴ� . ���� �����Ѵ�.
	} // ��Ƽ�� ��� ���� :: ���� ��� 

	  // const Node* end() �� ���� ���������� ���õ����� (���� �̰� �Ⱦ��� ��������)
	  // �ٸ� �̿��� �Ѱ��ٶ� �� �Լ����� �����Ǹ� �ȵȴٴ� ����� ��� �� �� �ִ�.
	iterator end() // const �� ���ȭ �Ͽ� ���� �� �ٲٰ� �Ѵ�.
	{
		return iterator(&m_wnTail);
		// ������ �����Ҵ�� �ʵ��̱� ������
		// End�� Delete�ҷ��� �ϸ� ������ ����.
	}

	// Ty���� �̵���ȯ����
	Ty pop_front()
	{
		Ty retval = move(m_wnHead.next()->m_Elem);

		Node* oldBegin = m_wnHead.next();
		Node* oldNext = oldBegin->m_pNext;
		Node* oldPrev = &m_wnHead;

		oldNext->m_pPrev = oldPrev;
		oldPrev->m_pNext = oldNext;

		delete oldBegin;


		return move(retval);
	}

	Ty pop_back()
	{
		//Ty retval = move(*(end()--));
		Ty retval = move(m_wnTail.m_pPrev->m_Elem);

		Node* oldEnd = m_wnTail.m_pPrev;
		Node* oldNext = &m_wnTail;
		Node* oldPrev = oldEnd->m_pPrev;

		oldNext->m_pPrev = oldPrev;
		oldPrev->m_pNext = oldNext;

		delete oldEnd;

		return move(retval);
	}
};