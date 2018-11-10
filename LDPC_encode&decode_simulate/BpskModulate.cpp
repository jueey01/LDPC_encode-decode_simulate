#include "BpskModulate.h"
#include <iostream>
/************************构造函数***********************/
bpskmodulator::bpskmodulator(const vector<int> &signal)
{
	bpsksignal.reserve(signal.size());
	for (size_t i = 0; i != signal.size(); ++i)
		bpsksignal.push_back(0.0);
	bpsk(signal);
}
/************************调制信号***********************/
void bpskmodulator::GenerateBpsk(const vector<int> &signal)
{
	bpsk(signal);
}
/************************调制信号***********************/
void bpskmodulator::bpsk(const vector<int> &signal)
{
	length = signal.size();
	for (size_t i = 0; i != length; ++i)
	{
		if (signal[i] == 1)
			bpsksignal[i] = -1;
		else
			bpsksignal[i] = 1;
	}
}
/************************获得信号***********************/
vector<double> bpskmodulator::GetBpskSignal() const
{
	return bpsksignal;
}
/************************打印信号***********************/
void bpskmodulator::PrintResult() const
{
	for (size_t i = 0; i != length; ++i)
		cout << bpsksignal[i] << ends;
}
/************************清除函数***********************/
void bpskmodulator::Clear()
{
	bpsksignal.clear();
}