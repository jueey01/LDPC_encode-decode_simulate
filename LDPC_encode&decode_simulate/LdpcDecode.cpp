#include "LdpcDecode.h"
/*************信息节点和校验节点的构造函数************/
NodeData::parentnode::parentnode(int maxc,int length) :
	size(maxc), code_length(length)
{	
	cmessage.reserve(code_length);
	for(size_t i = 0; i != code_length; ++i)
		cmessage.push_back(0.0);
}

NodeData::childnode::childnode(int maxr, int length) :
	size(maxr),code_length(length)
{
	rmessage.reserve(code_length);
	for (size_t i = 0; i != code_length; ++i)
		rmessage.push_back(0.0);
}

/******************更改最大迭代次数*******************/
void ldpcdecoder::SetMaxIter(int iter)                
{
	max_iter = iter;
}
/*****************返回本次迭代的次数******************/
int ldpcdecoder::GetTheIter() const
{
	return iter;
}
/*********************获得输入信号********************/
void ldpcdecoder::IitialLdpcDecoder(int clength)
{
	code_length = clength;
	max_iter = 50;
	LLR.reserve(code_length);
	result.reserve(code_length);
	for (size_t i = 0; i != code_length; ++i)
	{
		LLR.push_back(0.0);
	}
	for (size_t i = 0; i != code_length; ++i) 
	{
		result.push_back(0);
	}
}

/*************获取来自编码部分的H矩阵信息*************/
void ldpcdecoder::GetHMatrix(int N, int R)
{                                                  
											       
	NN = N;
	RR = R;
	ifstream inc("column_weight_distribution.txt");
	if (!inc)
	{
		cout << "Failed to open column_weight_distribution.txt!" << endl;
		exit(0);
	}
	ifstream inr("row_weight_distribution.txt");
	if (!inr)
	{
		cout << "Failed to open row_weight_distribution.txt!" << endl;
		exit(0);
	}
	string r;
	message_node.reserve(N);
	check_node.reserve(R);
	for (size_t i = 0; i != NN; ++i)
	{
		string number;
		getline(inc, r);
		istringstream stream(r);
		stream >> number;
		message_node.push_back(CreateParentNode(stoi(number)));
		for (int j = 0; j < message_node[i].size; ++j)
		{
			stream >> number;
			message_node[i].cindex.push_back(stoi(number));
		}
	}

	for (size_t i = 0; i != RR; ++i)
	{
		string number;
		getline(inr, r);
		istringstream stream(r);
		stream >> number;
		check_node.push_back(CreateChildNode(stoi(number)));
		for (int j = 0; j < check_node[i].size; ++j)
		{
			stream >> number;
			check_node[i].rindex.push_back(stoi(number));
		}
	}
	inc.close();
	inr.close();
}
/******************添加信息和校验节点*****************/
NodeData::parentnode ldpcdecoder::CreateParentNode(int cw)
{
	return parentnode(cw, code_length);
}

NodeData::childnode ldpcdecoder::CreateChildNode(int rw)
{
	return childnode(rw, code_length);
}
/*********************译码迭代部分********************/
int ldpcdecoder::StartDecode(vector<double>channel_out, const double n0,vector<int>&origsignal)
{
	int aux, auy;
	double multipl, sum;
	double *q_result = new double[channel_out.size()];
	int onetime_error_bit;
	/**************************初始化***************************/
	for (size_t i = 0; i != NN; ++i)
	{
		LLR[i] = 4.0*channel_out[i] / n0;
		for (size_t j = 0; j != message_node[i].size; ++j)
		{
			aux = message_node[i].cindex[j];
			message_node[i].cmessage[aux] = LLR[i];
		}
	}
	/**************************开始迭代*************************/
	for (iter = 0; iter < max_iter; ++iter)
	{
	/************************校验节点更新***********************/
		for (size_t i = 0; i != RR; ++i)
		{
			for (size_t j = 0; j != check_node[i].size; ++j)
			{
				multipl = 1.0;
				auy = check_node[i].rindex[j];
				for (size_t k = 0; k != check_node[i].size; ++k)
				{
					double t = 0.0;
					if (k != j)
					{
						aux = check_node[i].rindex[k];
						t = message_node[aux].cmessage[i];
						multipl *= tanh(t / 2);
					}
				}
				check_node[i].rmessage[auy] = 2 * atanh(multipl);
			}
		}


    /************************信息节点更新***********************/
		for (size_t i = 0; i != NN; ++i)
		{
			for (size_t j = 0; j != message_node[i].size; ++j)
			{
				sum = 0.0;
				auy = message_node[i].cindex[j];
				for (size_t k = 0; k != message_node[i].size; ++k)
				{
					if (k != j)
					{
						aux = message_node[i].cindex[k];
						sum += check_node[aux].rmessage[i];
					}
				}
				message_node[i].cmessage[auy] = LLR[i] + sum;
			}
		}

    /************************译码判决部分***********************/
		for (size_t i = 0; i != NN; ++i)
		{
			q_result[i] = 0;
			for (size_t j = 0; j != message_node[i].size; ++j)
			{
				aux = message_node[i].cindex[j];
				q_result[i] += check_node[aux].rmessage[i];
			}
			q_result[i] += LLR[i];
			if (q_result[i] < 0.0)
				result[i] = 1;
			else
				result[i] = 0;
		}
    /************************z*H=0?*************************/
		int error = 0;
		for (size_t i = 0; i != RR; ++i)   
		{
			int num = 0;
			for (size_t j = 0; j != check_node[i].size; ++j)
			{
				if (result[check_node[i].rindex[j]] == 1)
					++num;
			}
			if (num % 2 == 1) ++error;
		}
		if (error == 0)	break;

	}
    /******************计算译码错误的比特数*****************/
	onetime_error_bit = 0;
	for (size_t i = RR; i != NN; ++i)
	{
		if (result[i] != origsignal[i - RR])
			++onetime_error_bit;
	}
	delete[] q_result;
	return onetime_error_bit;
}
/***********************显示结果**********************/
void ldpcdecoder::PrintResult() const
{
	for (size_t i = code_length/2; i != code_length;++i)
		cout << result[i] << ends;
}
/***********************清除函数**********************/
void ldpcdecoder::Clear()
{
	result.clear();
	LLR.clear();
}
