#include "AwgnChannel.h"
/****************构造函数*****************/
awgnchannel::awgnchannel(double SNR, double mean, const vector<double> &signal) :
	snr(SNR), m(mean)
{
	length = signal.size();
	SignalWithNoise.reserve(length);
	Noise.reserve(length);
	Es = 1.0;
	Rate = 0.5;
	N0 = Es / (pow(10.0, (snr / 10))*Rate);
	sigma = sqrt(N0 / 2);
	AddNoise(signal);
}
/****************设置信号的强度值（默认值为1.0）*****************/
void awgnchannel::SetEs(double E)                        
{
	Es = E;
}
/******************输入码的码率（默认为0.5）*****************/
void awgnchannel::SetRate(double rate)                
{
	Rate = rate;
}
/***********************获取带噪信号************************/
vector<double> awgnchannel::GetSignalWithNoise() const
{
	return SignalWithNoise;
}
/***********************获取噪声信号************************/
vector<double> awgnchannel::GetNoiseVector() const
{
	return Noise;
}
/***********************获取信道N0************************/
double awgnchannel::GetN0() const
{
	return N0;
}
/***********************加噪声************************/
void awgnchannel::AddNoise(const vector<double> &signal)
{
	normal_distribution<double> nd(m, sigma);
	for (size_t i = 0; i != length; ++i)
		Noise.push_back(nd(e_channel));
	for (size_t i = 0; i != length; ++i)
		SignalWithNoise.push_back(signal[i] + Noise[i]);
}
/***********************打印带噪信号************************/
void awgnchannel::PrintResult() const
{
	for (size_t i = 0; i != length; ++i)
		cout << SignalWithNoise[i] << ends;
}

/***********************清除函数************************/
void awgnchannel::Clear()
{
	SignalWithNoise.clear();
	Noise.clear();
}