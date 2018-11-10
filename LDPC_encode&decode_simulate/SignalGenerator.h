#pragma once
#ifndef SIGNAL_GENERATOR_H
#define SIGNAL_GENERATOR_H

#include <random>
#include <vector>
#include <fstream>
#include <ctime>

/*****************信号生成器*****************/
using namespace std;

static default_random_engine e_rsignal(static_cast<unsigned>(time(NULL))); //利用static和时间避免每次运行出现相同的随机数
 
class signalgenerator
{
public:
	signalgenerator() = default;                 //默认构造函数
	void GenerateRandomeSignal(int n);           //产生一个给定比特的随机序列用于信源
	void Generate_1_Signal(int n);               //产生一个给定比特的全1信号
	void Generate_0_Signal(int n);               //产生一个给定比特的全0信号
	void PrintResult() const;                    //打印信号
	vector<int> GetSignal() const;               //获取这个信号
	void Clear();                                //清除函数
	~signalgenerator() { };
private:
	vector<int> signal;                          //存放信号
	int length;                                  //信号的长度
};


#endif SIGNAL_GENERATOR_H
