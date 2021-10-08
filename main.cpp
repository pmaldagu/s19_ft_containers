/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:10:14 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/10/01 17:02:32 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/stack.hpp"
#include <vector>
#include "./include/vector.hpp"
//#include <stack>

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs)
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main()
{
	/*
	std::cout << "==================STACK==================" << std::endl;
	std::vector<int> vec;
	ft::stack<int, std::vector<int> > test;
	ft::stack<int> test2;
	ft::stack<int> test3;
	//MutantStack<int> ms;

	std::cout << "empty = " << test.empty() << std::endl;
	test.push(5);
	test.push(7);
	std::cout << "size = " << test.size() << std::endl;
	test.pop();
	std::cout << "size after pop = " << test.size() << std::endl;
	std::cout << "top = " << test.top() << std::endl;
	
	test2.push(7);
	test2.push(6);

	test3.push(3);
	std::cout << "== " << (test3 == test2) << std::endl;
	std::cout << "!= " << (test3 == test2) << std::endl;
	std::cout << "> " << (test3 > test2) << std::endl;
	std::cout << ">= " << (test3 >= test2) << std::endl;
	std::cout << "< " << (test3 < test2) << std::endl;
	std::cout << "<= " << (test3 <= test2) << std::endl;

	vec.push_back(3);
	vec.push_back(7);
	vec.push_back(19);

	ft::stack<int> test4(test3);

	std::cout << "size = " << test4.size() << std::endl;
	*/

	std::cout << "==================VECTOR==================" << std::endl;
	std::vector<int> vec;
	ft::vector<int> myvec;

	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	myvec.push_back(0);
	myvec.push_back(1);
	myvec.push_back(2);
	myvec.push_back(3);
	myvec.push_back(4);


	vec.reserve(10);
	std::cout << "Size = " << vec.size() << std::endl;
	std::cout << "Capacity = " << vec.capacity() << std::endl;

	myvec.reserve(10);
	std::cout << "Size = " << myvec.size() << std::endl;
	std::cout << "Capacity = " << myvec.capacity() << std::endl;


	vec.resize(3);
	std::cout << "Size = " << vec.size() << std::endl;
	std::cout << "Capacity = " << vec.capacity() << std::endl;

	myvec.resize(3);
	std::cout << "Size = " << myvec.size() << std::endl;
	std::cout << "Capacity = " << myvec.capacity() << std::endl;

	myvec.push_back(3);
	vec.push_back(3);
	std::cout << myvec[2] << std::endl;
	std::cout << vec[2] << std::endl;
	std::cout << "Size = " << myvec.size() << std::endl;
	std::cout << "Capacity = " << myvec.capacity() << std::endl;

	vec.pop_back();
	myvec.pop_back();
	std::cout << "Size = " << vec.size() << std::endl;
	std::cout << "Capacity = " << vec.capacity() << std::endl;
	std::cout << "Size = " << myvec.size() << std::endl;
	std::cout << "Capacity = " << myvec.capacity() << std::endl;

	myvec.resize(15);
	std::cout << "Size = " << myvec.size() << std::endl;
	std::cout << "Capacity = " << myvec.capacity() << std::endl;
	std::cout << myvec[3] << std::endl;

	return (0);
}
