// OOPLab5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <vector>
#include <forward_list>
#include "List.h"
#include <algorithm>
#include <chrono>
using namespace std; 

template<typename Iter>
void print(Iter begin, Iter last)
{
	for (; begin != last; ++begin)
	{
		cout << *begin << " ";
	}
}

int main()
{
	setlocale(LC_ALL, "rus"); 

	cout << "�������� ����� ������ �� 15 ���������\n";
	List<int> lst({2,6,9,1,45,2,6,2,7,8,0,2,2,12,4});
	print(lst.begin(), lst.end()); 

	cout << "\n\n������� �������� ������������������ �� ��� (������� ��������)\n"; 
	stable_partition(lst.begin(), lst.end(), [](int x)
	{
		return x % 2 == 1;
	});
	print(lst.begin(), lst.end());
	
	cout << "\n\n����������� ������\n";
	stable_sort(lst.begin(), lst.end());
	print(lst.begin(), lst.end());

	cout << "\n\n������� �� ������ �������� � ������ � �����\n";
	lst.push_front(-10);
	lst.push_back(100);
	print(lst.begin(), lst.end());

	cout << "\n\n������ ���������� ���������, ������ 2\n";
	cout << count(lst.begin(), lst.end(), 2);
	

	cout << "\n\n������� ������������������\n";
	reverse(lst.begin(), lst.end());
	print(lst.begin(), lst.end());
	
	cout << endl << endl;

	cout << "�������� ����� ������ � ������ �� 100� ��������� ������\n";
	List<int> new_lst(100000);
	vector<int> vec(100000);

	cout << "\n����� ������� � 1-�� �������� �� �������:\n";

	int value = 0;

	auto begin = std::chrono::steady_clock::now();
	value = vec[0];
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	cout << "vector: " << elapsed_ns.count() << endl; 

	begin = std::chrono::steady_clock::now();
	value = new_lst[0];
	end = std::chrono::steady_clock::now();
	elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	cout << "list: " << elapsed_ns.count() << endl;

	cout << "\n\n����� ������� � 10000-�� �������� �� �������:\n";

	begin = std::chrono::steady_clock::now();
	value = vec[9999];
	end = std::chrono::steady_clock::now();
	elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	cout << "vector: " << elapsed_ns.count() << endl;

	begin = std::chrono::steady_clock::now();
	value = new_lst[9999];
	end = std::chrono::steady_clock::now();
	elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	cout << "list: " << elapsed_ns.count() << endl;

	cout << "\n\n����� ������� � 100000-�� �������� �� �������:\n";

	begin = std::chrono::steady_clock::now();
	value = vec[99999];
	end = std::chrono::steady_clock::now();
	elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	cout << "vector: " << elapsed_ns.count() << endl;

	begin = std::chrono::steady_clock::now();
	value = new_lst[99999];
	end = std::chrono::steady_clock::now();
	elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	cout << "list: " << elapsed_ns.count() << endl;
}
