#pragma once

template<typename My_list>
class List_const_iterator 
{
public:
	using iterator_category = std::bidirectional_iterator_tag;

	using Nodeptr = typename My_list::Nodeptr; 
	using value_type = typename My_list::value_type;
	using difference_type = typename My_list::difference_type;
	using pointer = typename My_list::const_pointer;
	using reference = const value_type&;

	List_const_iterator(Nodeptr _Pnode = nullptr)
		: _Ptr(_Pnode)
	{	
	}

	reference operator*() const
	{	
		return _Ptr->value;
	}

	pointer operator->() const
	{	
		return (std::pointer_traits<pointer>::pointer_to(**this));   
	}

	List_const_iterator& operator++()
	{	
		_Ptr = _Ptr->next;
		return *this;
	}

	List_const_iterator operator++(int)
	{	
		List_const_iterator tmp = *this;
		++(*this); 
		return tmp;
	}

	List_const_iterator& operator--()
	{	
		_Ptr = _Ptr->prev;
		return *this;
	}

	List_const_iterator operator--(int)
	{
		List_const_iterator tmp = *this;
		--(*this);
		return tmp;
	}

	bool operator== (const List_const_iterator& _Right) const
	{	
		return _Ptr == _Right._Ptr;
	}

	bool operator!= (const List_const_iterator& _Right) const
	{	
		return !(*this == _Right);
	}

	Nodeptr _Ptr;	
};

template<typename My_list>
class List_iterator : public List_const_iterator<My_list>
{
public:
	using My_base = List_const_iterator<My_list>;
	using iterator_category = std::bidirectional_iterator_tag;

	using Nodeptr = typename My_list::Nodeptr;
	using value_type = typename My_list::value_type;
	using difference_type = typename My_list::difference_type;
	using pointer = typename My_list::pointer;
	using reference = value_type&;

	List_iterator(Nodeptr _Pnode = nullptr)
		: My_base(_Pnode)
	{	
	}

	reference operator*() const
	{	
		return ((reference)**(My_base*)this); 
	}

	pointer operator->() const
	{
		return (std::pointer_traits<pointer>::pointer_to(**this));
	}

	List_iterator& operator++()
	{
		++(*(My_base*)this);
		return *this;
	}

	List_iterator operator++(int)
	{
		List_iterator tmp = *this;
		++(*this);
		return tmp;
	}

	List_iterator& operator--()
	{
		--(*(My_base*)this);
		return *this;
	}

	List_iterator operator--(int)
	{
		List_iterator tmp = *this;
		--(*this);
		return tmp;
	}
};

template<typename Val_ty>
struct List_node 
{
	using Nodeptr = List_node*; 

	Nodeptr prev;
	Nodeptr next;
	Val_ty value; 

	List_node& operator= (const List_node&) = delete; 
	List_node(const List_node&) = delete; 

	List_node(Val_ty val = Val_ty(), Nodeptr prev = nullptr, Nodeptr next = nullptr)
	{
		this->value = val;
		this->prev = prev;
 		this->next = next;
	}
};

template<typename Ty>
class List
{
public:
	using Node = List_node<Ty>;
	using Nodeptr = typename List_node<Ty>::Nodeptr;     

	using value_type = Ty; 
	using size_type = size_t;
	using difference_type = ptrdiff_t; 
	using pointer = Ty*; 
	using const_pointer = const Ty*; 
	using reference = value_type&;
	using const_reference = const value_type&;

	using iterator = List_iterator<List>; 
	using const_iterator = List_const_iterator<List>; 

	/*using reverse_iterator = _STD reverse_iterator<iterator>;
	using const_reverse_iterator = _STD reverse_iterator<const_iterator>;*/

	List();
	List(std::initializer_list<Ty> _Init_list);
	List(size_type _Count);
	List(size_type _Count, const Ty& _Val);
	template<typename Iter>
	List(Iter _First, Iter _Last);
	List(const List& _Right); 
	~List();

	List& operator= (const List& _Right);
	size_type size() const;
	Ty& operator[] (const size_type _Ind);
	const Ty& operator[] (const size_type _Ind) const;
	void push_front(const Ty& _Val);
	void push_back(const Ty& _Val);
	void pop_front();
	void pop_back();
	iterator insert(const_iterator _Where, const Ty& _Val);
	iterator insert(const_iterator _Where, size_type _Count, const Ty& _Val);
	template<typename Iter>
	iterator insert(const_iterator _Where, Iter _First, Iter _Last);
	iterator erase(const_iterator _Where); 
	void splice(const List& _Right);
	void clear();
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;

private:
	size_type _Size; 
	Nodeptr _Head;  
};

template<typename Ty>
inline List<Ty>::List() 
	: _Size(0)
{
	_Head = new Node();
	_Head->prev = _Head;
	_Head->next = _Head;
}

template<typename Ty>
inline List<Ty>::List(std::initializer_list<Ty> _Init_list)
	: List<Ty>::List() 
{
	insert(cbegin(), _Init_list.begin(), _Init_list.end());
}

template<typename Ty>
inline List<Ty>::List(size_type _Count)
	: List<Ty>::List()
{
	insert(cbegin(), _Count, 0);
}

template<typename Ty>
inline List<Ty>::List(size_type _Count, const Ty& _Val)
	: List<Ty>::List()
{
	insert(cbegin(), _Count, _Val); 
}

template<typename Ty>
template<typename Iter>
inline List<Ty>::List(Iter _First, Iter _Last)
	: List<Ty>::List()
{
	insert(cbegin(), _First, _Last); 
}

template<typename Ty>
inline List<Ty>::List(const List& _Right) 
	: List<Ty>::List()
{
	insert(cbegin(), _Right.begin(), _Right.end());
}

template<typename Ty> 
inline List<Ty>::~List()
{ 
	clear();
	delete _Head;
	_Head = nullptr;
}

template<typename Ty>
inline List<Ty>& List<Ty>::operator=(const List<Ty>& _Right)
{
	if (this != &_Right) 
	{     
		clear();
		insert(cbegin(), _Right.begin(), _Right.end());
	}
	return *this; 
}

template<typename Ty>
inline typename List<Ty>::size_type List<Ty>::size() const
{
	return _Size;
}

template<typename Ty>
inline Ty& List<Ty>::operator[](const size_type _Ind)
{
	iterator current = begin();

	for (size_t i = _Ind; 0 < i; --i)
	{
		++current;
	}

	return *current; 
}

template<typename Ty>
inline const Ty& List<Ty>::operator[](const size_type _Ind) const
{
	const_iterator current = begin();

	for (size_t i = _Ind; 0 < i; --i)
	{
		++current;
	}

	return *current;
}

template<typename Ty>
void List<Ty>::push_front(const Ty& _Val) 
{
	insert(cbegin(), _Val);
}

template<typename Ty>
void List<Ty>::pop_front()
{
	erase(cbegin());
}

template<typename Ty>
void List<Ty>::push_back(const Ty& _Val)
{
	insert(cend(), _Val);
}

template<typename Ty>
inline void List<Ty>::pop_back()
{
	erase(--cend());
}

template<typename Ty>
inline typename List<Ty>::iterator List<Ty>::insert(const_iterator _Where, const Ty& _Val) 
{
	const Nodeptr right_node = _Where._Ptr; 
	const Nodeptr left_node = right_node->prev;
	const Nodeptr new_node = new Node(_Val, left_node, right_node);

	++_Size;
	right_node->prev = new_node;
	left_node->next = new_node; 

	return iterator((--_Where)._Ptr);
}

template<typename Ty>
inline typename List<Ty>::iterator List<Ty>::insert(const_iterator _Where, size_type _Count, const Ty& _Val)
{
	for (; 0 < _Count; --_Count)
	{
		insert(_Where, _Val);
	}

	return iterator(_Where._Ptr); 
} 

template<typename Ty>
template<typename Iter>
inline typename List<Ty>::iterator List<Ty>::insert(const_iterator _Where, Iter _First, Iter _Last)
{
	for (; _First != _Last; ++_First)
	{
		insert(_Where, *_First);
	}

	return iterator(_Where._Ptr);
}

template<typename Ty>
inline typename List<Ty>::iterator List<Ty>::erase(const_iterator _Where)
{
	Nodeptr node = _Where._Ptr;
	Nodeptr next = _Where._Ptr->next;
	node->prev->next = node->next; 
	node->next->prev = node->prev;
	--_Size;

	delete node;

	return iterator(next); 
}

template<typename Ty>
void List<Ty>::clear()
{
	while (size())
	{
		pop_front();
	}
}

template<typename Ty>
void List<Ty>::splice(const List<Ty>& _Right)
{
	const_iterator current_it = _Right.begin();

	for ( ; current_it != _Right.end(); ++current_it)
	{
		push_back(*current_it); 
	}
}

template<typename Ty>
inline typename List<Ty>::reference List<Ty>::front()
{
	return *begin();
}

template<typename Ty>
inline typename List<Ty>::const_reference List<Ty>::front() const
{
	return *cbegin();
}

template<typename Ty>
inline typename List<Ty>::reference List<Ty>::back()
{
	return *(--end());
}

template<typename Ty>
inline typename List<Ty>::const_reference List<Ty>::back() const
{
	return *(--cend()); 
}

template<typename Ty>
inline typename List<Ty>::iterator List<Ty>::begin()
{
	return iterator(_Head->next);  
}

template<typename Ty>
inline typename List<Ty>::const_iterator List<Ty>::begin() const
{
	return const_iterator(_Head->next);
}

template<typename Ty>
inline typename List<Ty>::iterator List<Ty>::end()
{
	return iterator(_Head);
}

template<typename Ty> 
inline typename List<Ty>::const_iterator List<Ty>::end() const
{
	return const_iterator(_Head); 
}

template<typename Ty>
inline typename List<Ty>::const_iterator List<Ty>::cbegin() const
{
	return begin();
}

template<typename Ty>
inline typename List<Ty>::const_iterator List<Ty>::cend() const
{
	return end(); 
}