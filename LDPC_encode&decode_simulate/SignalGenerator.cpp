#include "SignalGenerator.h"
#include <iostream>
/*****************随机*****************/
void signalgenerator::GenerateRandomeSignal(int n)
{
	length = n;
	signal.reserve(n);
	uniform_int_distribution<unsigned> u(0, 1);
	for (size_t i = 0; i != n; ++i)
		signal.push_back(u(e_rsignal));
}
/*****************全1*****************/
void signalgenerator::Generate_1_Signal(int n)
{
	length = n;
	signal.reserve(n);
	for (size_t i = 0; i != n; ++i)
		signal.push_back(1);
}
/*****************全0*****************/
void signalgenerator::Generate_0_Signal(int n)
{
	length = n;
	signal.reserve(n);
	for (size_t i = 0; i != n; ++i)
		signal.push_back(0);
}
/*****************打印结果*****************/
void signalgenerator::PrintResult() const
{
	for (size_t i = 0; i != length; ++i)
		cout << signal[i] << ends;
}
/*****************获取信号*****************/
vector<int> signalgenerator::GetSignal() const
{
	return signal;
}
/******************清除函数******************/
void signalgenerator::Clear()
{
	signal.clear();
}