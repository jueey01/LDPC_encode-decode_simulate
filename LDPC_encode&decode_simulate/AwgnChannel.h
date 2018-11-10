#pragma once
#ifndef GUASS_H
#define GUASS_H

#include <random>
#include <vector>
#include <memory>
#include <iostream>
#include <ctime>
#include <cmath>

/********************高斯白噪声信道产生器*******************/
using namespace std;

static default_random_engine e_channel(static_cast<unsigned>(time(NULL)));            
                                                     //利用static和时间避免每次运行出现相同的随机数 
class awgnchannel
{
public:
	awgnchannel() = delete;                         //禁止编译器进行默认构造函数
	awgnchannel(double SNR, double mean, const vector<double> &signal);
	void SetEs(double E);                           //设置信号的强度值（默认值为1.0）
	void SetRate(double rate);                      //输入码的码率（默认为0.5）
	vector<double> GetSignalWithNoise() const;      //获取带信号的噪声的输出
	vector<double> GetNoiseVector() const;          //获取噪声
	void PrintResult() const;                       //打印带噪信号
	double GetN0() const;                           //获取信道N0的值
	void Clear();                                   //清除函数
private:
	void AddNoise(const vector<double> &signal);    //添加噪声
	double Es;                                      //噪声强度
	double m;                                       //噪声均值
	double sigma;                                   //信号标准差
	double snr;                                     //噪声信号的信噪比
	double N0;                                      //信道的N0值
	double Rate;                                    //码率
	vector<double> SignalWithNoise;                 //带噪声的输出序列
	vector<double> Noise;                           //噪声序列
	int length;                                     //信号长度
};

#endif GUASS_H
