# LDPC_encode-decode_simulate
&emsp;&emsp;LDPC(低密度奇偶校验)码编译码仿真（译码算法采用反向置信传播算法BP）。
## 环境与配置
&emsp;&emsp;推荐轻量级C++编译器clion运行仿真程序，C++语言版本为c++11。
## 编码与解码
### 编码
&emsp;&emsp;首先通过矩阵的行重或列重分布文件(存放于Matrixs中)转化为译码矩阵，然后将高斯消元之后的H矩阵作为编码矩阵M。产生一个待编码的序列(包含校验元的序列和信息元的序列)和M相乘得到序列s1，然后将s1通过bpsk调制成1和-1两个维度得到序列s2。最后对序列s2施加高斯白噪音模拟AWGN信道的环境。
### 译码
&emsp;&emsp;译码算法是基于对数似然比的消息传播算法(LLR-BP),该算法是神经网络算法在LDPC译码中的利用。译码器先通过H矩阵构造一层译码网络，所有的信息节点作为message_node，所有的译码节点作为check_node，译码开始时利用对数似然比(LLR)初始化message_node，然后不停的迭代信息节点和译码节点得到信息位对应的矩阵的所有位的LLR值，最好按列相加LLR进行判决0/1判决。
## 启动
&emsp;&emsp;将Matrixs中文件放在根目录下，并在main文件下设置好所有的参数。
```
test_Ldpc(encoder, decoder, 1.8, 4, 0.2, 512);
```
&emsp;&emsp;main函数中上述代码表示仿真的信噪比从1.8开始，到4结束，每隔0.2的信噪比进行一次仿真，512为序列的长度。
