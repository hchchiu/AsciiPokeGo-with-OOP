#ifndef VEC_ITERATOR_H
#define VEC_ITERATOR_H

// VecIterator class template definition
template< typename T >
class VecIterator
{
	template< typename T > friend class vector;
public:
	VecIterator(T* p = nullptr) // default constructor
		: ptr(p)
	{
	}

	VecIterator(const VecIterator& iteratorToCopy) // copy constructor
		: ptr(iteratorToCopy.ptr)
	{
	}

	~VecIterator() // destructor
	{
	}

	// const return avoids: ( a1 = a2 ) = a3
	const VecIterator& operator=(const VecIterator& right)
	{
		if (&right != this) // avoid self-assignment
			ptr = right.ptr;
		return *this; // enables x = y = z, for example
	}

	bool operator==(const VecIterator & right) const // equal to
	{
		return ptr == right.ptr;
	}

	bool operator!=(const VecIterator & right) const // not equal to
	{
		return ptr != right.ptr;
	}

	T& operator*() const // dereferencing operator
	{
		return *ptr;
	}

	VecIterator& operator++() // prefix increment operator
	{
		++ptr;
		return *this;
	}

	VecIterator& operator--() // predecrement an iterator
	{
		--ptr;
		return *this;
	}
	VecIterator& operator+(int number) // prefix increment operator
	{
		ptr += number;
		return *this;
	}

private:
	T* ptr; // keep a pointer to vector
}; // end class template VecIterator

#endif


#ifndef REVERSE_VEC_ITERATOR_H
#define REVERSE_VEC_ITERATOR_H

// ReverseVecIterator class template definition
template< typename T >
class ReverseVecIterator
{
public:
	ReverseVecIterator(T* p = nullptr) // default constructor
		: ptr(p)
	{
	}

	ReverseVecIterator(const ReverseVecIterator& iteratorToCopy) // copy constructor
		: ptr(iteratorToCopy.ptr)
	{
	}

	~ReverseVecIterator() // destructor
	{
	}

	// const return avoids: ( a1 = a2 ) = a3
	const ReverseVecIterator& operator=(const ReverseVecIterator& right)
	{
		if (&right != this) // avoid self-assignment
			ptr = right.ptr;
		return *this; // enables x = y = z, for example
	}

	bool operator==(const ReverseVecIterator & right) const // equal to
	{
		return ptr == right.ptr;
	}

	bool operator!=(const ReverseVecIterator & right) const // not equal to
	{
		return ptr != right.ptr;
	}

	T& operator*() const // dereferencing operator
	{
		return *ptr;
	}

	ReverseVecIterator& operator++() // prefix increment operator
	{
		--ptr;
		return *this;
	}

	ReverseVecIterator& operator--() // predecrement an iterator
	{
		++ptr;
		return *this;
	}

private:
	T* ptr; // keep a pointer to vector
}; // end class template ReverseVecIterator

#endif


#ifndef VECTOR_H
#define VECTOR_H

// vector class template definition
template< typename T >
class vector
{
	template< typename T >
	friend bool operator==(const vector< T >& lhs, const vector< T >& rhs);

	template< typename T >
	friend bool operator!=(const vector< T >& lhs, const vector< T >& rhs);

public:
	using iterator = VecIterator< T >;
	using reverse_iterator = ReverseVecIterator< T >;

	vector(unsigned int n = 0); // Constructor; Constructs a zero vector with size n

	// Copy constructor; Constructs a vector with a copy of each of the elements in vectorToCopy.
	vector(const vector& x);

	~vector(); // Destroys the vector.

	const vector& operator=(const vector& x); // assignment operator

	// Returns a pointer pointing to the first element in the vector.
	// If the vector is empty, the returned pointer shall not be dereferenced.
	iterator begin() const;

	// Returns an pointer pointing to the past-the-end element in the vector.
	// The past-the-end element is the theoretical element that would follow the last element in the vector.
	// It does not point to any element, and thus shall not be dereferenced.
	iterator end() const;

	reverse_iterator rbegin() const; // Returns a iterator pointing to the last element in the vector.

	// Returns a iterator pointing to the theoretical element preceding the first element in the vector.
	reverse_iterator rend() const;

	// Returns the number of elements in the vector.
	// This is the number of actual objects held in the vector,
	// which is not necessarily equal to its storage capacity.
	unsigned int size() const;

	// Returns the size of the storage space currently allocated for the vector,
	// expressed in terms of elements.
	unsigned int capacity() const;

	// Resizes the vector so that it contains n elements.
	// If n is smaller than the current vector size,
	// the content is reduced to its first n elements, removing those beyond.
	// If n is greater than the current vector size,
	// the content is expanded by inserting at the end as many elements as needed to reach a size of n.
	// The new elements are initialized as 0.
	// If n is also greater than the current vector capacity,
	// an automatic reallocation of the allocated storage space takes place.
	void resize(unsigned int n);

	// The vector is extended by inserting a new element before the element at position,   
	// effectively increasing the container size by one.   
	// This causes an automatic reallocation of the allocated storage space.   
	// Relocates all the elements that were after position to their new positions.
	iterator insert(iterator position, const T& val);

	// Removes from the vector a single element.   
	// This effectively reduces the container size by one.   
	// Relocates all the elements after the element erased to their new positions.
	iterator erase(iterator position);

	void push_back(const T val);

	void pop_back();

	void clear();

	T& operator[](unsigned int);

	T operator[](unsigned int) const;
private:
	T* myFirst;
	T* myLast;
	T* myEnd;
}; // end class template vector

#endif


// constructor; constructs a zero vector with size n
template< typename T >
vector< T >::vector(unsigned int n)
	: myFirst(n == 0 ? nullptr : new T[n]()),
	myLast(n == 0 ? nullptr : myFirst + n),
	myEnd(n == 0 ? nullptr : myLast)
{
} // end vector default constructor

// copy constructor; constructs a vector with a copy of each of the elements in vectorToCopy
template< typename T >
vector< T >::vector(const vector< T >& x)
	: myFirst(new T[x.capacity()]),
	myLast(myFirst + x.size()),
	myEnd(myFirst + x.capacity())
{
	for (int i = 0; i < x.size(); i++)
		myFirst[i] = x.myFirst[i];
} // end vector copy constructor

// destructor; destroys the vector
template< typename T >
vector< T >::~vector()
{
	if (myFirst != nullptr)
		delete[] myFirst;
} // end destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const vector< T >& vector< T >::operator=(const vector< T > & x)
{
	if (&x != this) // avoid self-assignment
	{
		resize(x.size());

		for (int i = 0; i < x.size(); i++)
			myFirst[i] = x.myFirst[i];
	} // end outer if

	return *this; // enables x = y = z, for example
} // end function operator=

template< typename T >
typename vector< T >::iterator vector< T >::begin() const
{
	return iterator(myFirst);
}

template< typename T >
typename vector< T >::iterator vector< T >::end() const
{
	return iterator(myLast);
}

template< typename T >
typename vector< T >::reverse_iterator vector< T >::rbegin() const
{
	return reverse_iterator(myLast - 1);
}

template< typename T >
typename vector< T >::reverse_iterator vector< T >::rend() const
{
	return reverse_iterator(myFirst - 1);
}

template< typename T >
unsigned int vector< T >::size() const
{
	return (myLast - myFirst);
}

template< typename T >
unsigned int vector< T >::capacity() const
{
	return (myEnd - myFirst);
}

// Resizes the vector container so that it contains n elements.
template< typename T >
void vector< T >::resize(unsigned int n)
{
	int cap = capacity(), check_size = size();
	int check = 0;
	int modify = 0;

	if (n <= capacity())
	{
		for (int i = size(); i < n; ++i)
			myFirst[i] = 0;

		myLast = myFirst + n;
	}
	else
	{
		modify = check_size / 2;

		if (check_size == 1)
			modify = 1;

		modify += check_size;

		if (modify < n)
			modify = n;

		iterator tmp;
		tmp.ptr = myFirst;

		myFirst = new T[modify]();

		for (int i = 0; i < modify; i++)
			myFirst[i] = 0;

		for (int i = 0; i < check_size; i++)
			myFirst[i] = tmp.ptr[i];

		myLast = myFirst + n;
		myEnd = myFirst + modify;

		delete[]tmp.ptr;
	}
}

template< typename T >
typename vector< T >::iterator vector< T >::insert(iterator position, const T & val)
{
	int check_pos = position.ptr - begin().ptr;

	if (size() + 1 > capacity())
		resize(size() + 1);
	else
		myLast += 1;

	for (int i = size() - 2; i >= check_pos; i--)
	{
		myFirst[i + 1] = myFirst[i];

		if (i == 0)
			break;
	}

	myFirst[check_pos] = val;
	return myFirst;
}

template< typename T >
typename vector< T >::iterator vector< T >::erase(iterator position)
{
	int erase_pos = position.ptr - begin().ptr;

	for (int i = erase_pos; i + 1 < size(); i++)
		myFirst[i] = myFirst[i + 1];

	myLast -= 1;
	return myFirst;
}

// determine if two Arrays are equal and
// return true, otherwise return false
template< typename T >
bool operator==(const vector< T > & lhs, const vector< T > & rhs)
{
	typename vector< T >::iterator it1 = lhs.begin();
	typename vector< T >::iterator it2 = rhs.begin();
	if (lhs.size() != rhs.size())
		return false;
	else
	{
		int check_size = lhs.size();
		for (; it1 != lhs.end(); ++it1) {
			if (*it1 == *it2)
				continue;
			else
				return false;
		}
		return true;
	}
} // end function operator==

// inequality operator; returns opposite of == operator
template< typename T >
bool operator!=(const vector< T > & lhs, const vector< T > & rhs)
{
	return !(lhs == rhs); // invokes vector::operator==
}

template< typename T >
T& vector< T >::operator[](unsigned int subscript)
{
	return myFirst[subscript];
} // end function operator[]

template< typename T >
T vector< T >::operator[](unsigned int subscript) const
{
	return myFirst[subscript];
} // end function operator[]

template< typename T >
void vector<T>::push_back(const T val)
{
	if (myFirst == nullptr)
	{
		myFirst = new T[1]();
		myFirst[0] = val;
		myLast = myEnd = myFirst + 1;
	}
	else
	{
		int check = 0, cap = 0;
		int	increase_space = 0, check_size = 0;

		check_size = size();

		increase_space = check_size / 2;

		if (check_size == 1)
			increase_space = 1;


		if (myLast == myEnd)
			check++;
		else
			cap = capacity();

		T * tempPtr;
		tempPtr = myFirst;

		if (increase_space + check_size != 0)
			myFirst = new T[increase_space + check_size]();

		for (int i = 0; i < check_size; i++)
			myFirst[i] = *(tempPtr++);

		myLast = myFirst + check_size;
		*myLast = val;
		myLast += 1;

		if (check == 1)
			myEnd = myLast + increase_space - 1;
		else
			myEnd = myFirst + cap;
	}
}

template< typename T >
void vector<T>::pop_back()
{
	if (size() != 0)
		myLast -= 1;
}

template< typename T >
void vector<T>::clear()
{
	int delSize = size();
	for (int i = 0; i < delSize; ++i)
		pop_back();
}