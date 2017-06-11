#pragma once


#include <iostream>
#include <string>
#include <map>
#include <list>
#include <functional>
#include "AbstractPlayer.h"

using namespace std;

class Algo {
public:
	virtual ~Algo() {}
	virtual int foo() = 0;
};

class Registration {
public:
	Registration(const string& id, std::function<AbstractPlayer*(void)> func) {
		algoFactory[id] = func;
	}
	static map<string, std::function<AbstractPlayer*(void)>> algoFactory;
};


class Algo_1 : public Algo {
public:
	virtual int foo() override {
		return 7;
	}
};

//// in the cpp of Algo_1
//Registration algo_1("algo_1",
//	[] {return new Algo_1(); }
//);
//
//class Algo_2 : public Algo {
//public:
//	virtual int foo() override {
//		return 9;
//	}
//};
//
//// in the cpp of Algo_2
//Registration algo_2("algo_2",
//	[] {return new Algo_2(); }
//);

//int main() {
//	list<Algo*> algorithms;
//	for (auto& p_id_func : Registration::algoFactory) {
//		auto& func = p_id_func.second;
//		algorithms.push_back(func());
//	}
//
//	for (auto algo : algorithms) {
//		cout << algo->foo() << endl;
//		delete algo;
//	}
//
//}
