#include <string>
#include <iostream>
#include <sstream>

using namespace std;

typedef unsigned long ul;

//字符串乘以数字 
string strImult_c(string s, char c){
	string :: size_type index;
	int overflow = 0;
	for(index = s.size(); index != 0; index--){
		int tmp = (s[index - 1] - '0') * (c - '0') + overflow;
		if(tmp >= 10){
			overflow = tmp /10;
			s[index -1] = tmp %10 + '0';
		}else{
			overflow = 0;
			s[index -1] = tmp + '0';
		}
	}
	if(overflow){
		s.insert(s.begin(), overflow + '0');
	}
	return s;
}
//字符串相加 
void strAdd(string &s, string s1){
	//补齐较短字符串
	string :: size_type sz, sz1;
	sz = s.size();
	sz1 = s1.size();
	if(sz > sz1){
		auto i = sz - sz1;
		for(int j = 0; j != i; j++){
			s1.insert(s1.begin(), '0');
		}
	} 
	//相加
    int overflow = 0;
	for(string :: size_type index = sz; index != 0; index--){
		int tmp = s[index - 1] - '0' + s1[index - 1] - '0' + overflow;
		if(tmp >= 10){
			overflow = 1;
			s[index - 1] = tmp %10 + '0';
		}else{
			overflow = 0;
			s[index - 1] = tmp + '0';
		}
	} 
	if(overflow){
		s.insert(s.begin(), '1');
	}
}
//字符串相乘 
string strImult(string sreslt, string sstep){
	string istr;
	string :: size_type index = 0;
	istr = strImult_c(sreslt, sstep[index]);
	for(index = 1; index != sstep.size(); index++){
		istr.push_back('0');
		string tmp = strImult_c(sreslt, sstep[index]);
		strAdd(istr, tmp); 
	}
	return istr;
}
//字符串比较大小, 第一个大于第二个 
bool strCmp(string s1, string s2){
	if(s1.size() > s2.size()){
		return true;
	}else if(s1.size() == s2.size() && s1 >= s2){
		return true;
	}else{
		return false;
	}
} 
//求两字符串之差，第一个大于第二个 
string strSub(string s1, string s2){
	if(s1.size() > s2.size()){
		auto len = s1.size() - s2.size();
		for(int i = 0; i != len; i++){
			s2.insert(s2.begin(), '0');
		}
	}
	int borrow = 0;
	for(string :: size_type index = s1.size(); index != 0; index--){
		int tmp = s1[index -1] - borrow - s2[index -1];
		if(tmp < 0){
			tmp += 10;
			s1[index -1] = tmp + '0';
			borrow = 1;
		}else{
			s1[index -1] = tmp + '0';
			borrow = 0;
		}
	}
	//去掉前导0
	auto pos = s1.find_first_not_of("0");
	if(pos == string :: npos){
		string s;
		return s;
	}
	return s1.substr(pos);
} 
//求两个小字符串相除的余数, 第一个大于第二个 
string strMod_t(string s, string pattern){
	char c = '1';
	char prev;
	string tmp = pattern;
	while(strCmp(s, tmp)){
		prev = c;
		c++;
		strAdd(tmp, pattern);
	}
	string slast = strImult_c(pattern, prev);
	string result = strSub(s, slast);
	return result;
}
//大字符串取模 
int strMod(string s, string pattern){
	istringstream istr(s);
	string tmp;                     //除法运算保存每一步被除数 
	char c;                         //读取被除字符串的每一个字符 
	auto sz = pattern.size();       //第一步读入必要的字符 
	for(int i = 0; i != sz -1; i++){
		istr >> c;
		tmp.push_back(c); 
	}
	while(istr >> c){
		tmp.push_back(c); 
		if(strCmp(tmp, pattern)){
			tmp = strMod_t(tmp, pattern);
		}
	}
	//最后一次除法运算
	if(strCmp(tmp, pattern)){
		tmp = strMod_t(tmp, pattern);
	} 
	return stoi(tmp);
}
//字符串的次幂运算,生成公钥私钥的函数保证传递来的int为正整数
//算法原理: 把int 数据看成二进制数据，每个二进制位为0的不做操作
//为1 的位，以1所在的位置(从右到左)为总数a，执行a次如下运算:
//对s执行2次方运算并把结果赋给s,得到的是该位上s的“权”
//依次乘以所有的“权”，得到结果 
string strPower(string s, int pw){
	string result = "1";             //保存最终结果 
	if(pw % 2){                      //最低位的“权” 
		result = strImult(result, s);
	} 
	int step = 0;                    //记录每个二进制位上的运算次数 
	while(pw){
		pw >>= 1;                    //从右到左遍历每个位 
		step++;                      //该位的运算次数 
		if(pw % 2){
			string tmp = s;
			for(int i = 0; i != step; i++){
				tmp = strImult(tmp, tmp);  //得到该位上的“权” 
			}
			result = strImult(result, tmp);
		}
	}
	return result;
}
