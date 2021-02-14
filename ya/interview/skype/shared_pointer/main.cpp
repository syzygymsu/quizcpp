#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>

template<class T>
class my_shared_ptr
{
private:
	T * ptr = nullptr;
	int * refCount = nullptr;

public:
	my_shared_ptr() : ptr(nullptr), refCount(new int(0)) // default constructor
	{
	}

	my_shared_ptr(T * ptr) : ptr(ptr), refCount(new int(1)) // constructor
	{
	}

	/*** Copy Semantics ***/
	my_shared_ptr(const my_shared_ptr & obj) // copy constructor
	{
		this->ptr = obj.ptr; // share the underlying pointer
		this->refCount = obj.refCount;
		if (nullptr != obj.ptr)
		{
			(*this->refCount)++; // if the pointer is not null, increment the refCount
		}
	}

	my_shared_ptr& operator=(const my_shared_ptr & obj) // copy assignment
	{
		__cleanup__(); // cleanup any existing data
		
		// Assign incoming object's data to this object
		this->ptr = obj.ptr; // share the underlying pointer
		this->refCount = obj.refCount;
		if (nullptr != obj.ptr)
		{
			(*this->refCount)++; // if the pointer is not null, increment the refCount
		}
	}

	/*** Move Semantics ***/
	my_shared_ptr(my_shared_ptr && dyingObj) // move constructor
	{
		this->ptr = dyingObj.ptr; // share the underlying pointer
		this->refCount = dyingObj.refCount;

		dyingObj.ptr = dyingObj.refCount = nullptr; // clean the dying object
	}

	my_shared_ptr& operator=(my_shared_ptr && dyingObj) // move assignment
	{
		__cleanup__(); // cleanup any existing data
		
		this->ptr = dyingObj.ptr; // share the underlying pointer
		this->refCount = dyingObj.refCount;

		dyingObj.ptr = dyingObj.refCount = nullptr; // clean the dying object
	}

	int get_count() const
	{
		return *refCount; // *this->refCount
	}

	T* get() const
	{
		return this->ptr;
	}

	T* operator->() const
	{
		return this->ptr;
	}

	T& operator*() const
	{
		return this->ptr;
	}

	~my_shared_ptr() // destructor
	{
		__cleanup__();
	}

private:
	void __cleanup__()
	{
		(*refCount)--;
		if (*refCount == 0)
		{
			if (nullptr != ptr)
				delete ptr;
			delete refCount;
		}
	}
};

int main()
{
    my_shared_ptr<int> obj(new int(5));
    assert(obj.get_count() == 1);
    return 0;
}
