#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <fstream>
#include "esa_extend.h"

using namespace std;

//大质数生成函数5000-10000
vector<int> iGenerateVec(void){
	vector<int> ivec;
	for(int i = 5000; i != 10000; i++){
		int j;
		for(j = 2; j != i /2 + 1; j++){
			if(i % j == 0){
				break;
			}
		}
		if(j == i /2 + 1){
			ivec.push_back(i); 
		}
	}
	return ivec;
} 
//判断两个数是否互质a > b
bool ifRelative(int a, int b){
	for(int i = 2; i <= b; i++){
		if(b % i == 0 && a % i == 0){
			return false;
		}
	}
	return true;
} 
//生成公钥私钥
pair<pair<int, int>, pair<int, int>> iGenerateKey(vector<int> &ivec){
	auto sz = ivec.size();
	vector<int> :: size_type index1, index2;
	while(1){
		time_t t;
		time(&t);
		index1 = (rand() + t) % sz;
		index2 = (rand() + t) % sz;
		if(index1 != index2){
			break;
		}
	}
	int p = ivec[index1], q = ivec[index2];
	int n_fst = p * q;
	int a = (p - 1) * (q - 1);
	//公钥 
	int e, m;
    e = 2;
    while(!ifRelative(a, e)){
    	e++;
	}
	pair<int, int> pair1(n_fst, e);
	//私钥, 第二个值只取正整数 
	m = 1;
	while((e * m) % a != 1){
		m++;
	} 
	//m + ka 都可以是第二个值 
	pair<int, int> pair2(n_fst, m);
	return make_pair(pair1, pair2);
} 
//加密函数
int iEncrypt(char c, pair<int, int> p){
	string s1 = to_string(c);
	string s = strPower(s1, p.second);
	string s2 = to_string(p.first);
	return strMod(s, s2);
} 
//解密函数
char iDecrypt(int c, pair<int, int> p){
	string s1 = to_string(c);
	string s = strPower(s1, p.second);
	string s2 = to_string(p.first);
	int tmp = strMod(s, s2);
	return static_cast<char>(tmp);
} 
//加密解密文件
void fEncrypt(string src, string dest, pair<pair<int, int>, pair<int, int>> p){
	ifstream ifstrm(src, ios :: in);
	ofstream ofstrm(dest, ios :: out);
	if(ifstrm && ofstrm){
		istream_iterator<char> iter_in(ifstrm), eof_in;
		while(iter_in != eof_in){
			int c = iEncrypt(*iter_in, p.first);
			ofstrm << c << " ";
			iter_in++;
		}
	}else{
		cout << "files error" << endl;
	}
} 
void fDecrypt(string src, string dest, pair<pair<int, int>, pair<int, int>> p){
	ifstream ifstrm(src, ios :: in);
	ofstream ofstrm(dest, ios :: out);
	if(ifstrm && ofstrm){
		istream_iterator<int> iter_in(ifstrm), eof_in;
		while(iter_in != eof_in){
			char c = iDecrypt(*iter_in, p.second);
			ofstrm << c;
			iter_in++;
		}
	}else{
		cout << "files error" << endl;
	}
}


main(){
	cout << strPower("2", 10000);
	/*
	vector<int> ivec = iGenerateVec();
	auto key = iGenerateKey(ivec);
	string s1("./sss.txt");
	string s2("./encrypt.txt");
	string s3("./decrypt.txt");
	fEncrypt(s1, s2, key);
	fDecrypt(s2, s3, key);
    */ 
}
