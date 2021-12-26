#ifndef PTR_H_
#define PTR_H_

#include <iostream>
#include <string>

template <typename T>
struct Ptr
{
	Ptr(const T n = T()) : ptr_(new T(n)) { /*print("ctor");*/ }
	Ptr(const Ptr& p) : ptr_(new T(*p.ptr_)) { /*print("copy_ctor");*/ }
	~Ptr() { /*print("dtor");*/ delete ptr_; }

	Ptr& operator=(const Ptr& p)
	{
		if (this != &p) {
			delete ptr_;
			ptr_ = new T(*p.ptr_);
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Ptr& p)
	{
		return os << *p.ptr_;
	}

	void print(const std::string& str) { std::cout << "Ptr::" << str << '[' << (void*)ptr_ << "][" << *ptr_ << "]\n"; }

	T* ptr_;
};

#endif	//PTR_H_
