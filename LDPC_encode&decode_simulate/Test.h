#pragma once
#ifndef TEST_H
#define TEST_H
#include <iostream>
#include <vector>
#include <fstream>
#include "AwgnChannel.h"
#include "SignalGenerator.h"
#include "LdpcDecode.h"
#include "BpskModulate.h"
#include "LdpcEncode.h"
using namespace std;
/**********************************LDPC仿真入口************************************/
void test_Ldpc(ldpcencoder &encoder, ldpcdecoder &decoder, double SNRdown, double SNRup, double dista, int codelength)
{
	ofstream out("Result.txt", ofstream::binary);
	if (!out)
	{
		cout << "Failed to create Result.txt!" << endl;
		exit(0);
	}

	for (double snr = SNRdown; snr < SNRup; snr += dista)
	{
		double wer = 0.0;
		double ber = 0.0;
		double aver_iter = 0.0;
		int sum_iter = 0;
		int success = 0;
		int wrong = 0;
		int errorbits = 0;
		int c = 0;
		int times = 0;
		while(1)
		{
			++times;
			signalgenerator signal;
			signal.GenerateRandomeSignal(codelength);
			encoder.StartEncode(signal.GetSignal());
			bpskmodulator bpsk(encoder.GetEncodeResult());
			awgnchannel guass(snr, 0, bpsk.GetBpskSignal());
			c = decoder.StartDecode(guass.GetSignalWithNoise(), guass.GetN0(),signal.GetSignal());
			if (c == 0) ++success;
			else ++wrong;
			errorbits += c;
			wer = static_cast<double>(wrong) / static_cast<double>(times);
			ber = static_cast<double>(errorbits) / static_cast<double>(times*codelength);
			sum_iter += decoder.GetTheIter();
			aver_iter = static_cast<double>(sum_iter) / static_cast<double>(times);
				cout <<"snr=" << snr << "   " << "success=" << success << "   " << "wrong=" << wrong << "   "
					<< "wer=" << wer << "   " << "ber=" << ber << "   " << "aver_iter=" << aver_iter << "   " << endl;
				out << "snr=" << snr << "   " << "success=" << success << "   " << "wrong=" << wrong << "   "
					<< "wer=" << wer << "   " << "ber=" << ber << "   " << "aver_iter=" << aver_iter << "   " << endl;
			signal.Clear();
			guass.Clear();
			bpsk.Clear();
			encoder.Clear();
			decoder.Clear();
			if (wrong == 100) break;
		}
	}
}



#endif TEST_H
