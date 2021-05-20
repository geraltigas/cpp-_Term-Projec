#pragma once


//----------- 类型
enum class Type
{
	King,
	Knight,
	Rook,
	Elephant,
	Advisor,
	Conon,
	Soldier,
	vague,
	Null
};

//-----------  阵营
enum class Camp
{
	jiang,
	shuai,
	null
};

//----------- 变换
enum class Trans
{
	selected,
	dis_selected,
	appear,
	dis_appear,
	move_to,
	move_from
};

//-----------  链表容器
template<typename T>
class Node
{
public:
	Node<T>* pre;
	Node<T>* succ;
	T data;
	Node(Node<T>* pres, Node<T>* succs, T& data) :pre(pres), succ(succs), data(data)
	{
	};
	Node(T& datas) :data(datas), pre(nullptr), succ(nullptr)
	{
	};
};


template<typename T>
class Linked_list
{
public:
	unsigned int scale;
	Node<T>* begin;
	Node<T>* end;
	Node<T>* now_at;
	int now_rank;
	Linked_list() :scale(0), begin(nullptr), end(nullptr), now_at(nullptr), now_rank(-1)
	{
	};
	void add(T& data)
	{
		if (scale)
		{
			end->succ = new Node<T>(end, nullptr, data);
			end = end->succ;
			data.~T();
			detect();
		}
		else
		{
			begin = new Node<T>(nullptr, nullptr, data);
			end = begin;
			now_at = begin;
			now_rank = 0;
			data.~T();
		}
		scale++;
	};
	T& next()
	{
		if (now_at->succ)
		{
			now_at = now_at->succ;
			now_rank++;
			return now_at->data;
		}
	};
	T& ahead()
	{
		if (now_at->pre)
		{
			now_at = now_at->pre;
			now_rank--;
			return now_at->data;
		}
	};
	T& operator[](int rank)
	{
		if (rank >= scale)
		{
			return end->data;
		}
		else
		{
			if (rank == now_rank)
			{
				return now_at->data;
			}
			else if (rank > now_rank)
			{
				while (rank != now_rank)
				{
					next();
				}
				return now_at->data;
			}
			else
			{
				while (rank != now_rank)
				{
					ahead();
				}
				return now_at->data;
			}
		}
	};
	void insert_after(int rank, const T& data)
	{
		(*this)[rank];
		Node<T>* temp = now_at->succ;
		now_at->succ = new Node<T>(const_cast<T&>(data));
		now_at->succ->pre = now_at;
		now_at->succ->succ = temp;
		if (temp != nullptr)
		{
			temp->pre = now_at->succ;
		}
		else
		{
			end = now_at->succ;
		}
		scale++;
	};
	void detect()
	{
		if (now_rank >= scale)
		{
			now_at = end;
			now_rank = scale - 1;
		};
	};
	T& pop()
	{
		T temp = end->data;
		Node<T>* temp_end = end;
		end = end->pre;
		end->succ = nullptr;
		delete temp_end;
		scale--;
		detect();
		return temp;
	};
	void pop_by_rank(int rank)
	{
		(*this)[rank];
		if (now_at->succ == nullptr)
		{
			pop();
		}
		else if (now_at->pre == nullptr)
		{
			begin = begin->succ;
			scale--;
			begin->pre = nullptr;
			now_at = begin;
		}
		else
		{
			Node<T>* temp1 = now_at->pre;
			Node<T>* temp2 = now_at->succ;
			delete now_at;
			temp1->succ = temp2;
			temp2->pre = temp1;
			scale--;
			now_at = temp2;
		}
	};
};
