#pragma once
#ifndef BPSK_MODULATE
#define BPSK_MODULATE
#include <vector>

using namespace std;
/********************BPSK调制器*******************/
class bpskmodulator
{
public:
	bpskmodulator() = default;                             //默认构造函数
	bpskmodulator(const vector<int> &signal);              //构造函数（可选）
	void GenerateBpsk(const vector<int> &signal);          //产生一个bpsk信号    
	vector<double> GetBpskSignal() const;                  //获得bpsk调制之后的信号
	void PrintResult() const;                              //打印信号
	void Clear();                                          //清除函数
private:
	vector<double> bpsksignal;                             //存放bpsk信号
	void bpsk(const vector<int> &signal);                  //对信号进行bpsk调制
	int length;                                            //信号长度
};



#endif BPSK_MODULATE
