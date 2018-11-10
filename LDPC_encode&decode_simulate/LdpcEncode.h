#pragma once
#ifndef LDPC_ENCODE
#define LDPC_ENCODE 
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <iterator>
#include <numeric>

using namespace std;
/***************基于高斯消元的LDPC编码器****************/
class ldpcencoder
{
public:
	ldpcencoder() = default;                         //默认构造函数
	void GenerateHMatrix(int c, int r);              //根据分布产生H矩阵
	void PrintfMatrix() const;                       //打印H矩阵
	void PrintfGuassMatrix() const;                  //打印高斯消元后的矩阵
	void TransHMatrix();                             //对矩阵进行高斯消元
	void StartEncode(const vector<int> &signal);     //开始编码
	vector<int> GetEncodeResult() const;             //获得编码后的信号
	void PrintResult() const;                        //打印编码后的信号
	void Clear();                                    //清除函数
private:
	vector<vector<int>> HMatrix;                     //存放H矩阵
	vector<vector<int>> GuassHMatrix;                //存放高斯消元后的矩阵
	vector<int> encoderesult;                        //存放编码后的信号
	int row;                                         //矩阵的行
	int column;                                      //矩阵的列
};

#endif LDPC_ENCODE
