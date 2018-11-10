/***************************************************************************************************************************************************************************/
/**************************************************************************************************   Made By 李首贤       *************************************************/
/**************************************************************************************************       2015年10月22日   *************************************************/
/***************************************************************************************************************************************************************************/
#include "AwgnChannel.h"
#include "SignalGenerator.h"
#include "LdpcDecode.h"
#include "BpskModulate.h"
#include "LdpcEncode.h"
#include "Test.h"

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	ldpcencoder encoder;
	encoder.GenerateHMatrix(1024, 512);
	encoder.TransHMatrix();	
	ldpcdecoder decoder;
	decoder.IitialLdpcDecoder(1024);
	decoder.GetHMatrix(1024, 512);
	//signalgenerator signal;
	//signal.GenerateRandomeSignal(252);
	//encoder.StartEncode(signal.GetSignal());
	//bpskmodulator bpsk(encoder.GetEncodeResult());
	//awgnchannel guass(2, 0, bpsk.GetBpskSignal());
	//decoder.StartDecode(guass.GetSignalWithNoise(), guass.GetN0(), signal.GetSignal());
	test_Ldpc(encoder, decoder, 1.8, 4, 0.2, 512);   //第三个参数是仿真开始的信噪比，第四个参数是仿真结束的信噪比，第五个参数是信噪比间隔
	system("pause");
	return 0;
}






















