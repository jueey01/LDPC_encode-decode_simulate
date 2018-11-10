#pragma once
#ifndef LDPC_DECODER
#define LDPC_DECODER

#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <cmath>
#include <sstream>
#include <string>

using namespace std;

/************这个译码器使用的是LLR-BP译码器*************/

/****************定义信息节点与校验节点*****************/
class NodeData {
public:
	class parentnode
	{
	public:
		parentnode(int maxc, int length);
		~parentnode() { };
		int code_length;
		int size;			                                    //该列为1个数
		vector<int> cindex;			                            //存储1位置的索引
		vector<double> cmessage;	                            //存储列节点信息     
	};
	class childnode
	{
	public:
		childnode(int maxr, int length);
		~childnode() { };
		int code_length;
		int size;                                               //该行为1个数
		vector<int> rindex;			                            //存储1位置的索引
		vector<double> rmessage;                                //存储行节点信息
	};
};
/***************基于LLR-BP的LDPC码译码器****************/
class ldpcdecoder:public NodeData
{
public:
	ldpcdecoder()=default;                                      //默认构造函数
	void IitialLdpcDecoder(int length);                         //初始化迭代器
	void GetHMatrix(int nn, int rr);                            //获取H矩阵密度信息 
	void SetMaxIter(int iter);                                  //设定最大迭代次数
	int StartDecode(vector<double>channel_out,const double n0,vector<int>&orisignal); 
																//开始迭代译码
	int GetTheIter() const;                                     //本次译码迭代次数      
	void PrintResult() const;                                   //显示本次译码的结果
	void Clear();                                               //清除函数
	~ldpcdecoder() {};                                          //编码器析构函数
private:
	parentnode CreateParentNode(int cw);                        //创造信息节点
	childnode CreateChildNode(int rw);                          //创造校验节点
	vector<parentnode> message_node;                            //信息节点
	vector<childnode>  check_node;				                //校验节点
	vector<int> result;					                        //存储解码之后的结果	
	int NN;                                                     //信息位个数
	int RR;                                                     //校验位个数
	int code_length;                                            //码的长度
	int max_iter;	 			                                //最大迭代次数（默认为50次）
	int iter;                                                   //实际迭代次数
	vector<double> LLR;					                        //信道输出似然比的值
};


#endif LDPC_DECODER
