#include "LdpcEncode.h"
/****************************读取分布并生成相应的H矩阵******************************/
void ldpcencoder::GenerateHMatrix(int c, int r)
{
	row = r;
	column = c;
	ifstream in("row_weight_distribution.txt");
	if (!in)
	{
		cout << "Failed to open row_weight_distribution.txt!" << endl;
		exit(0);
	}
	HMatrix.resize(row, vector<int>(column));
	string rline;
	for (size_t i = 0; i != row; ++i)
	{
		string number;
		getline(in, rline);
		istringstream line(rline);
		line >> number;
		while (line >> number)
			HMatrix[i][stoi(number)] = 1;
	}
	in.close();
}
/*******************************打印H矩阵*********************************/
void ldpcencoder::PrintfMatrix() const
{
	ofstream out("H.txt");
	if (!out)
	{
		cout << "Failed to create H.txt!" << endl;
		exit(0);
	}
	for (size_t i = 0; i != row; ++i)
	{
		for (size_t j = 0; j != column; ++j)
		{
			out << HMatrix[i][j]<<" ";
		}
		out << endl;
	}
}
/*******************************打印高斯H矩阵*********************************/
void ldpcencoder::PrintfGuassMatrix() const
{
	ofstream out("GuassH.txt");
	if (!out)
	{
		cout << "Failed to create GuassH.txt!" << endl;
		exit(0);
	}
	for (size_t i = 0; i != row; ++i)
	{
		for (size_t j = 0; j != column; ++j)
		{
			out << GuassHMatrix[i][j];
		}
		out << endl;
	}
}
/****************************将H矩阵进行高斯消元******************************/
void ldpcencoder::TransHMatrix()
{
	GuassHMatrix.reserve(row);
	GuassHMatrix=HMatrix;
	int i = 0, j = 0;
	while (i < row && j < column)
	{
		if (GuassHMatrix[i][j] == 0)
		{
			for (int t = i + 1; t < row; ++t)
			{
				if (GuassHMatrix[t][j] == 1)
				{
					for (int s = 0; s < column; s++)
					{
						int p = GuassHMatrix[i][s];
						GuassHMatrix[i][s] = GuassHMatrix[t][s];
						GuassHMatrix[t][s] = p;
					}
					break;
				}	
			}
		}
		
		if (GuassHMatrix[i][j] == 0)
		{
			++j;
			continue;
		}
		for (int r = i + 1; r<row; ++r)
		{
			if (GuassHMatrix[r][j] == 1)
				for (int s = 0; s<column; s++)
				{
					GuassHMatrix[r][s] += GuassHMatrix[i][s];
					GuassHMatrix[r][s] = GuassHMatrix[r][s] % 2;
				}

		}

		if (i >= 1)
		{
			for (int r = i - 1; r >= 0; --r)
			{
				if (GuassHMatrix[r][j] == 1)
					for (int s = j; s<column; s++)
					{
						GuassHMatrix[r][s] += GuassHMatrix[i][s];
						GuassHMatrix[r][s] = GuassHMatrix[r][s] % 2;
					}
			}
		}
		i++;
		j++;
	}
}
/****************************开始LDPC编码******************************/
void ldpcencoder::StartEncode(const vector<int> &signal)
{
	encoderesult.resize(column);
	for (size_t i = 0; i != row; ++i)
	{
		vector<int> temp;
		temp.reserve(column);
		for (size_t j = row; j != column; ++j)
			temp.push_back(GuassHMatrix[i][j] && signal[j - row]);
		int xor_ = accumulate(temp.cbegin(), temp.cend(), 0);
		encoderesult[i] = (xor_ % 2);
		temp.clear();
	}

	for (size_t i = row; i != column; ++i)
	{
		encoderesult[i] = signal[i - row];
	}
}
/**************************获得编码后的信号****************************/
vector<int> ldpcencoder::GetEncodeResult() const
{
	return encoderesult;
}
/**************************打印编码后的信号****************************/
void ldpcencoder::PrintResult() const
{
	for (size_t i = 0; i != column; ++i)
		cout << encoderesult[i] << ends;
	cout << endl;
}
/**************************清除函数****************************/
void ldpcencoder::Clear()
{
	encoderesult.clear();
}